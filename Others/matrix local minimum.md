Matrix Local Minimum Problem
=========
This problem is from problem 1.4.19, Algorithm(4th edition).  
  
Given a matrix `A` with $n^2$ different integers. A local minimum `A[i][j]` is an element that `A[i-1][j] ＞ A[i][j]`,
`A[i+1][j] ＞ A[i][j]`,`A[i][j-1] ＞ A[i][j]`, and `A[i][j+1] ＞ A[i][j]`. In this case, the elements on the boundary of the 
matrix can only compare with their 3 or 2 neighbours.  
  
Design an algorithm that can find a local minimum of the matrix in $O(n)$ time.  

## Problem Analysis  
Like the "local minimum in an array" problem, we can solve this with **divide and conquer**.  
  
Consider the method below:  
  
1. Look at the boundary, the center column and center row of the matrix. The look-up area is like a "window", and we find
a minimum element of the window.  
2. Compare the minimum element with its neighbours. If it's a peak, return. If not, then find its smallest neighbour. Notice
that the smallest neighbour will not be in the window area.  
3. The window will divide the original matrix into 4 submatrices(quadrants). The smallest neighbour must be in one of the quadrants. Use
this quadrant as the new matrix and apply step 1~3 recursively to it. The recursion will end if `matrix.size()<3`.  
  
We need to prove that this dividing method can lead to a quadrant with a local maximum. To prove this, we can observe an invariant:  
`Minimum element of the window never increase as we shrink in recursion.`  
  
Suppose in the first step we find the smallest element in the window `a` and its smallest neighbour `b`. When we enter a quadrant, the new window contains boundary of the quadrant (part of the old window) and the center column/row of the quadrant. Notice that `a` is in the boundary of the quadrant, so `a` is in both the old and the new window. The smallest element of the new window must be less than or equal to `a`. As a result, minimum element of the window never increase.  
  
With this invariant, we can prove that **if entering a quadrant, it must contain a local minimum**:  
  
When we enter a quadrant, we know that `b` is smaller than any elements of the boundary, and the minimum of the quadrant must be less than or equal to `b`:  
  
1. If the minimum of the quadrant is `b`, then `b` is the local minimum, because it's smaller than "interior elements"(elements that within but exclude the boundary), and `b` is smaller than boundary elements.  
2. If the minimum is smaller than 'b', it should be an interior element. Whether it's adjacent to a boundary element or not, it's smaller than any element that is adjacent to it.  

As a result, the dividing method is effective. Assume the time complexity solving a matrix of size $n^2$ is $T(n)$, then we have a recurrence relation:  
$T(n)\=T(n/2)+cn$  
Where $cn$ is the time to find the smallest element in the window, and the smallest neighbour. The time complexity expressed with big-O notation should be $O(n)$, which means it's a linear time solution.  


