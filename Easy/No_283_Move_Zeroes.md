No.283 Move Zeroes
=========
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:
```
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
```
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations. 

## Problem Analysis  

Multiple ways can solve this question. But **make sure do mod arithmetic to `k` before rotating**, since `k` can be larger than the size of the array.  

## How To (In C++)
