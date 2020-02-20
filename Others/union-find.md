Union-find problem
=========
The problem is from Algorithm 4th edition, Chapter 1.5.  
  
Given a series of integer pair as input. Each distinct integer represents a distinct object of any kind. 
An integer pair means that the two objects are connected. 
  
The connection between integers has three properties:  
```
1. Integer p is connected to p;
2. If p and q are connected, so do q and p;
3. If p and q are connected, and q and r are connected, then p and r are connected.
```

If two integers are connected, they are said to be in an "equivalent class", or in a "set". The problem is,
given a series of integer pairs, we construct the "sets" of integers. We can know whether any two integers are in the same set.
With a new integer pair, we can union two sets of integers into a single set if the two integers are not connected; if connected, we do nothing. This problem is called **the dynamic connectivity problem**.  

This problem has a broad application. For example, dealing with connection issues of Internet, variable-name equivalence, or just
mathematical sets.

## Problem Analysis  

We need to specify the requirements before anything. For this problem, we can find two core requirements:  
```
1. Define a sort of data structure to store current known connections;
2. Base on the data structure, implement efficient way to judge connectivity and do union operation.
```

The book provides a set of API to deal with the requirements:

|`class UF`||
|---------|------------------------------------------|
|`UF(int n)`| To initialize n sites with integer names (0 to N-1)
|`void union(int p, int q)`| add connection between p and q
|`int find(int p) `| component identifier for p (0 to N-1)
|`bool connected(int p, int q)` | return true if p and q are in the same component
|`int count() `| number of components

Since the node and the component identifier are both represented by an integer, we can store the connection information like this:  
  
Assume we know the domain of integers in the input, and assume it is `[0,n-1]`. We use one node of a component(the "set") as the identifier. Then we can create an array `id` of size n, `id[i]` stores the identifier of node i. To simplify the design, we also assume that we do not need to concern deleting nodes from a component.  

In this case, we have the prototype of `UF` class as follows:  
```C++
class UF
{
protected:
	vector<int> id;	// id[i] stores the identifier of node i
	int Count;	// number of connected components

public:
	virtual ~UF() { cout << "Base destroyed." << endl; }
	virtual void Union(int p, int q) = 0; // do union operation
	virtual int find(int p) = 0;  // return the identifier of p
	bool connected(int p, int q) { return find(p) == find(q); }
	int count() { return Count; }
    
	void printId() // print current connection information, not necessary
        {    
		for (int i = 0; i < id.size(); i++) {
			if (i != id.size() - 1) cout << id[i] << " ";
			else cout << id[i] << endl;
		}
	}

};
```
Now we need to implement the `find()` and `Union()` method. To analyze the complexity, we let **each array access operation as the primary operation.**  

## How To (In C++)
### 1. Quick-find
A primary concern is how to implement identifier. One possible answer is choose one specific element from a component, and for any node `i` in a component with identifier `x`(including `x` itself), `id[i]` is equal to `x`. In this case, `find(p)` only need to return `id[p]`. For union operation, if p and q do not belong to the same component, we can let `id[p] = id[q]` to union p into q's component. Moreover, for any nodes originally belongs to p's component, `Union()` should also change their identifiers too. So now we have the following code:  
```C++
// quick-find algorithm
int quickFindUF::find(int p) {
	return id[p];
}

void quickFindUF::Union(int p, int q) {
	// find the identifiers of p and q
	int pID = find(p);
	int qID = find(q);
	// if p and q belong to the same component, return
	if (pID == qID) return;
	// union the two components p and q belong to
	for (int i = 0; i < id.size(); i++) {
		if (id[i] == pID) id[i] = qID;
	}
	Count--;
}

```

This algorithm is simple, and `find()` takes only $O(1)$ time to execute. However, `Union()` operation will operate n+3 to 2n+1 array access if two components are not equal. So each union operation takes $O(n)$ time. If we process n nodes and m edges, and we obtain only one connected components at the end, we will take $O(mn)$ time to complete. This quadratic efficiency makes quick-find not a good way to handle large amount of data.  

### 2. Quick-union
To improve the efficiency, we may need more sophisticated structure. Notice that if two integers belong to the same component, we will not add additional edges to connect them. As a result, the connecting relationship is like a tree(with no loop or circle). Naturally, we will think if we can represent the connection in a tree or linked structure.  
  
In the `id` array, we do not directly store identifier. Instead, we store a "link-to" node. For example, if `id[i]` equals to `j`, means that `i` is linked to `j`; `id[j]` equals to `k` means `j` is linked to `k`... Eventually, if `id[p]==p`, we reach the root node, namely the identifier of the component. So we have a new definition of "same component":  
  
**Two nodes belong to one component if and only if they link to the same root.**  
  
Under this definition, union operation is very simple. First, find the root of `p` and `q`. Then, re-link root of `p` to root of `q`, or the opposite way. Because when distinguishing components, we only care about root, so we do not need to change every nodes in the component.  
  
Find operation however, need more effort than quick-find algorithm. There is a loop repeatedly trace from the node you're finding all the way to the root. In the best situation, `find()` only takes one array access. But in the worst case, it takes 2n-1 times. If we view the whole component as a tree, we can observe that **the time complexity of `find()` is related to the height `H` of the tree.** When we do nothing to optimize the tree structure, we know that the worst case complexity is still quadratic.  

Quick-union algorithm is as follows:  
```C++
// quick-union algorithm
int quickUnionUF::find(int p) {
	vector<int> mid_node;
	while (p != id[p]) {
		mid_node.push_back(p);
		p = id[p];
	}
	// path compression: each middle node link directly to the root node
	for (int i : mid_node) {
		id[i] = p;
	}
	return p;
}

void quickUnionUF::Union(int p, int q) {
	int pRoot = find(p);
	int qRoot = find(q);
	if (pRoot == qRoot) return;
	id[pRoot] = qRoot;
	Count--;
}
```

### 3.Weighted Quick-union
In quick-union, the time complexity of `Union()` is $O(H)$, where `H` is the height of the highest tree. We can optimize the tree structure(usually we call it "balancing"), so that `H` is significantly reduced compare to `n` or `m`.  
  
The following is weighted quick-union algorithm. We add a new array `sz` to store the size of a component(corresponding to the root node's location), and we always connect the smaller tree to the root of the larger tree when we do union operations.  
```C++

class weightedUF : public UF {
protected:
	vector<int> sz;
public:

	~weightedUF() { cout << "Derived destroyed." << endl; }
	weightedUF(int n);
	void Union(int p, int q);
	int find(int p);
};

weightedUF::weightedUF(int n) {
	Count = n;
	id = vector<int>(n);
	for (int i = 0; i < id.size(); i++) {
		id[i] = i;
	}
	sz = vector<int>(n);
	for (int i = 0; i < id.size(); i++) {
		sz[i] = 1;
	}
}

// weighted quick-union algorithm
int weightedUF::find(int p) {
	vector<int> mid_node;
	while (p != id[p]) {
		mid_node.push_back(p);
		p = id[p];
	}
	// path compression: each middle node link directly to the root node
	for (int i : mid_node) {
		id[i] = p;
	}
	return p;
}

void weightedUF::Union(int p, int q) {
	int pRoot = find(p);
	int qRoot = find(q);
	if (pRoot == qRoot) return;
	if (sz[pRoot] < sz[qRoot]) { id[pRoot] = qRoot; sz[qRoot] += sz[pRoot]; }
	else { id[qRoot] = pRoot; sz[pRoot] += sz[qRoot]; }
	Count--;
}
```
We can prove by strong induction that **in weighted quick-union algorithm, for n nodes, the height of any node in any forest will not exceed log(n).**  
  
Since for any operation of `weightedUF`, it will only access array constant time for each node, the total time complexity for any operation is $O(logn)$.  
  
We can even further reduce the height of trees. Notice that the `find()` method contains a piece of code which does path compression. When finding a root of `p`, it will re-link each node along the path directly to the root. This method will further flatten the resulting component tree.  
  
The amortize analysis diagram of quick-find, quick-union and weighted quick-union in the books shows the difference of their efficiency. Weighted quick-union with path compression can acieve nearly constant time complexity for any single operation.  

## Summary
By analyzing union-find problem, we learn how to convert a problem into specific needs and APIs, which clarify ideas and simplify development processes. Three kinds of algorithm show that how a little change of the code can results in huge difference in efficiency.  


