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
def fourSum(array, target):
    n = len(array)
    ret = []
    for i in range(n):
        for j in range(i+1, n):
            if array[i] + array[j] == target:
                ret.append([array[i], array[j]])
    return ret
```
Obviously this method has $O(n^2)$ time complexity. In general, it has $O(n^k)$ complexity for k-sum problems.  
Certainly there is space for improvement. To find a subset `{a,b}` that can add up to `target`, we can iterate through all elements `a` of `nums` and find if there is another element `b` such that `target - a == b`. There are two ways:  
#### A. Hash map
First, we insert elements of `nums` into a hash map `Hmap`. Then for each `a`, we find `target - a` in `Hmap`. Since `find()` operation of a hash map only takes $O(1)$ time, this method (theoretically) takes only $O(n)$ time.  
```python
def twoSum(array, target):
    n = len(array)
    ret = []
    Hmap = dict()
    for i in range(n):
        Hmap[array[i]] = array[i]
    for i in range(n):
    # be careful about duplication
        if target - array[i] in Hmap and [array[i], target - array[i]] not in ret and [target - array[i],array[i]] not in ret:
            ret.append([array[i],target - array[i]])
    return ret
```

#### B. sort, and then find
Method A has a space complexity trade-off, which may be undesirable in some situations. As the book *Algorithm* shows, using sorting and binary search can solve the problem without extra space cost:  
```C++
vector<vector<int>> twoSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    int n = nums.size();
    if(n < 2) return res;
    sort(nums.begin(),nums.end());
    for(int i = 0; i < n; i++){
        int index = BinarySearch(target-nums[i], nums);
        if(index > i) {     // to avoid duplication
            res.push_back(vector<int>(nums[i], target-nums[i]));
        }
    }
    return res; 
}
```
Here, `BinarySearch(tar, array)` do a binary search and returns the index of `tar` in a sorted array.  
In addition to binary search, we can also use two pointers after sorting the original array:  
```C++
vector<vector<int>> twoSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    int n = nums.size();
    if(n < 2) return res;
    sort(nums.begin(),nums.end());
    int i = 0, j = n-1;
    while(i < j){
        if(nums[i] + nums[j] < target) i++;
        else if (nums[i] + nums[j] > target) j--;
        else {
            res.push_back(vector<int>(nums[i],nums[j]));
            i++;j--;
        }
    }
    return res; 
}
```
We first mantain two pointers at head and tail of the array. Since the array is sorted, when `nums[i] + nums[j] < target`, we know that `nums[i]` is too small, and we should let `i++` to check the next element. Similarly, when `nums[i] + nums[j] > target`, we do `j--` because `nums[j]` is too large. When we find a pair (`nums[i] + nums[j] == target`), we add the pair to the result and simutaneously increase(or decrease) the two pointers to check the next state.  
Because both of the two methods in B needs sorting, so the time complexity is at least $O(nlogn)$. However, in "find" process, the second method is better since it takes $O(n)$ while finding with`BinarySearch()` takes $O(nlogn)$ in total.  

## How To (In C++)
### 1. 2d counting array
