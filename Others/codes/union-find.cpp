
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include<map>
using namespace std;

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

	void printId() {    // print current connection information, not necessary
		for (int i = 0; i < id.size(); i++) {
			if (i != id.size() - 1) cout << id[i] << " ";
			else cout << id[i] << endl;
		}
	}

};

class quickFindUF : public UF
{
public:
	~quickFindUF() { cout << "Derived destroyed." << endl; }
	quickFindUF(int n);
	void Union(int p, int q);
	int find(int p);

};

quickFindUF::quickFindUF(int n) {
	Count = n;
	id = vector<int>(n);
	for (int i = 0; i < id.size(); i++) {
		id[i] = i;
	}
}

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

class quickUnionUF : public UF {
public:
	~quickUnionUF() { cout << "Derived destroyed." << endl; }
	quickUnionUF(int n);
	void Union(int p, int q);
	int find(int p);
};

quickUnionUF::quickUnionUF(int n) {
	Count = n;
	id = vector<int>(n);
	for (int i = 0; i < id.size(); i++) {
		id[i] = i;
	}
}

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


int main()
{
	vector<vector<int>> a;
	a.push_back(vector<int>{9,0});
	a.push_back(vector<int>{3,4});
	a.push_back(vector<int>{5,8});
	a.push_back(vector<int>{7,2});
	a.push_back(vector<int>{2,1});
	a.push_back(vector<int>{5,7});
	a.push_back(vector<int>{0,3});
	a.push_back(vector<int>{4,2});
	//a.push_back(vector<int>{4,3});
	//a.push_back(vector<int>{3,8});
	//a.push_back(vector<int>{6,5});
	//a.push_back(vector<int>{9, 4});
	//a.push_back(vector<int>{2,1});
	//a.push_back(vector<int>{8,9});
	//a.push_back(vector<int>{5, 0});
	//a.push_back(vector<int>{7, 2});
	//a.push_back(vector<int>{6,1});
	//a.push_back(vector<int>{1, 0});
	//a.push_back(vector<int>{6,7});

	UF* uf = new weightedUF(10);
	for (int i = 0; i < a.size(); i++) {
		int p = a[i][0]; int q = a[i][1];
		uf->Union(p, q);
	}
	uf->printId();
	cout << "Count: " << uf->count() << endl;
	delete uf;
	uf = nullptr;

}

