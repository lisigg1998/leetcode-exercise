No.191 Number of 1 Bits
=========
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:
```
Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]
```

## Problem Analysis  

Use counting should work, but it consumes $O(n)$ space. If we can store information in the original array without destroying any original information, we can finish with $O(1)$ space.  

## How To (In C++)
