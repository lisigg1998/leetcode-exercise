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
given a series of integer pairs, we construct the "sets" of integers. We can know whether any two integers are in the same set,
and we can union two sets of integers into a single set. This problem is called **the dynamic connectivity problem**.  

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
  
Assume we know the domain of integers in the input, and assume it is `[0,n-1]`. We use one node of a component(the "set") as the identifier. Then we can create an array `id` of size n, `id[i]` stores the identifier of node i.  

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




