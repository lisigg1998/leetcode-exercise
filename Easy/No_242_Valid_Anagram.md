No.242 Valid Anagram
=========
Given an array A of 0s and 1s, consider `N_i`: the i-th subarray from `A[0]` to `A[i]` interpreted as a binary number (from most-significant-bit to least-significant-bit.)

Return a list of booleans answer, where `answer[i]` is true if and only if `N_i` is divisible by 5.  

Note:  
1. 1 <= `A.length` <= 30000
2. `A[i]` is 0 or 1

## Problem Analysis  

**The length of `A` indicates that if we simply adding up digits the integer will definitely overflow.** We need to solve this problem with some math knowledge about mod arithmetics.  

## How To (In C++)
