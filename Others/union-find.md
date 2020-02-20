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

### 1. Define the problem

We need to specify the requirements before anything. For this problem, we can find two core requirements:  
```
1. Define a sort of data structure to store current known connections;
2. Base on the data structure, implement efficient way to judge connectivity and do union operation.
```

The book provides a set of API to deal with the requirements:

|`class UF`||
|---------|------------------------------------------|
|```C++
UF(int n)
```| To initialize n sites with integer names (0 to N-1)
|`void union(int p, int q)`| add connection between p and q
|`int find(int p) `| set identifier for p (0 to N-1)
|`bool connected(int p, int q)` | return true if p and q are in the same component
|`int count() `| number of components


