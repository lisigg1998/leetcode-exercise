The k-sum problem
=========
The k-sum problem is very classic. Basically it is described as follows:  
Given an integer array `nums`, an integer `k` and a target number `target`, find out all `k`-sized subsets of  `nums` such that `sum(subset[::]) == target`.  
There may be other constrains, such as:  
```
1. The original array may have duplicated elements, but your output should not contains duplicated subsets;
2. Each of your output subset should have ascending order inside;
```

## Problem Analysis  

### 1. How to solve 2-sum?
It is useful to reduce the problem to the simplest case at first. We reduce k to 2, and assume that every elements in the array are different, and the elements of a subset can be in any order.  
2-sum can be easily solved by brute force method. Using two `for` loops, we can enumerate each and every subsets of size 2 in `nums`.  
```python
def fourSum(array):
    n = len(array)
    ret = []
    for i in range(n):
        for j in range(i+1, n):
            if array[i] + array[j] == target:
                ret.append([array[i], array[j]])
    return ret
```
Obviously this method has $O(n^2)$ time complexity. In general, it has $O(n^k)$ complexity for k-sum problems.  
Certainly there is space for improvement. To find a subset `{a,b}` that can add up to `target`, we can iterate through all elements `a` of `nums` and find if there is another element `b` such that `target - b == a`. There are two ways:  
#### 1. Hash map


## How To (In C++)
### 1. 2d counting array
