No.103 Binary Tree Zigzag Level Order Traversal
=========
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).  
  
For example:  
Given binary tree` [3,9,20,null,null,15,7]`,  
```
    3
   / \
  9  20
    /  \
   15   7
```
return its zigzag level order traversal as:  
```
[
  [3],
  [20,9],
  [15,7]
]
```   
The tree is represented as:  
```C++
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}	
};
```


## Problem analysis
  
The output has two requirements. First, output the tree layer by layer. Second, the traversal should be a zigzap shape.  
  
The first requirement is very easy to fulfill, just use BFS. As for the second requirement, we use some features of `vector`. This zigzag
requires odd layers (1,3,5,...) traverse from left to right, and even layers (2,4,6,...) from right to left. So we can insert odd layer vectors from left to right, and insert even layer vectors from right to left.  

## How To (In C++)
### 1. BFS with queue
```C++
#include <queue>
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> res;
	if (root == NULL) return res;
	queue<TreeNode*> ql,qr;
	ql.push(root);

	while (!ql.empty() || !qr.empty()) {
		vector<int> temp;
		if (!ql.empty()) {
			while (!ql.empty()) {
				temp.push_back(ql.front()->val);
				if(ql.front()->left != NULL) qr.push(ql.front()->left);
				if (ql.front()->right != NULL)qr.push(ql.front()->right);
				ql.pop();
			}
		}
		else if (!qr.empty()) {
			while (!qr.empty()) {
				temp.insert(temp.begin(),qr.front()->val);
				if (qr.front()->left != NULL)ql.push(qr.front()->left);
				if (qr.front()->right != NULL)ql.push(qr.front()->right);
				qr.pop();
			}
		}
		res.push_back(temp);
	}
	return res;
}
```
Make sure you know how to use `vector`, `queue` and BFS in C++.  
Notice that to distinguish odd and even layers, I use **two queues** to store them alternatively. Also, **remember to deal with boundary conditions that the root/children is/are empty**.  
  
### 2. Alternative BFS
There is another way to use BFS with only one queue. To distinguish layers, just insert a null pointer to queue when a layer has been fully inputed to the queue. That is when you are popping out a null pointer. Also remember the boundary condition that when the last element of the final layer is out, you shouldn't add null pointer anymore. This is judged by whether `q.size()>1`.
```C++
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> res;
	if (root == NULL) return res;
	int level = 1; 
	bool flip = 1; // indicators to decide whether to add a new layer or flip the direction of insertion.
	queue<TreeNode*> q;
	q.push(root);
	q.push(NULL);

	while (!q.empty()) {
		if (level > res.size()) {
			vector<int> layer;
			res.push_back(layer);
		}
		if (q.front() == NULL) {
			level++;
			flip = !flip;
			if(q.size()>1) q.push(NULL);
		}
		else {
			if (flip) { // flip==true, left to right
				res[level - 1].push_back(q.front()->val);
			}
			else {		// flip==false, right to left
				res[level - 1].insert(res[level-1].begin(),q.front()->val);
			}
			if (q.front()->left != NULL) q.push(q.front()->left);
			if (q.front()->right != NULL) q.push(q.front()->right);

		}
		q.pop();
	}
	return res;
}
```
Notice that there is a `level` indicator to decide if it is the time to add a new layer.  

### 3. Using DFS
DFS can solve the problem, too. It is similar to BFS. Using DFS, you do not need to use a queue or a stack, but you need to decide if the current element is the first element of one layer by the `level` indicator. Detailed code is in leetcode.

