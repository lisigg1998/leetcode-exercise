Matrix Local Minimum Problem
=========
This problem is from problem 1.4.19, Algorithm(4th edition).  

Given a matrix `A` with $n^2$ different integers. A local minimum `A[i][j]` is an element that `A[i-1][j] ＞ A[i][j]`,
`A[i+1][j] ＞ A[i][j]`,`A[i][j-1] ＞ A[i][j]`, and `A[i][j+1] ＞ A[i][j]`. In this case, the elements on the boundary of the 
matrix cannot be local minimum.  

Design an algorithm that can find a local minimum of the matrix in $O(n)$ time.  

## Problem Analysis  
