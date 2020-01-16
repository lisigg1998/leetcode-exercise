No.448 Find All Numbers Disappeared in an Array
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
### 1. Use counting array
```C++
vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int> counting(nums.size(),0);
    vector<int> res;
    for(int i : nums){
        counting[i-1]++;
    }
    for(int i = 0; i < counting.size(); i++){
        if(counting[i] == 0) res.push_back(i+1);
    }
    return res;
}
```
**Time complexity:**  
  
$O(n)$.  
  
**Space complexity:**  
  
$O(n)$.  

### 2. Optimal counting
If the input array is allowed to be modified, this question can be completed in $O(1)$ space.  
  
We just need to find missing elements, so the counting array can just store 1 or 0 to indicate existence. If we view the original array as the counting array, and use + and - signs to represent 0 and 1, we can store information in the original array. Since we know all original elements are larger than zero, we can deal with signs so that original info is not destroyed.  

```C++
vector<int> findDisappearedNumbers(vector<int>& nums) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int len = nums.size();
    for(int i=0; i<len; i++) {
        int m = abs(nums[i])-1; // index start from 0
        nums[m] = nums[m]>0 ? -nums[m] : nums[m];
    }
    vector<int> res;
    for(int i = 0; i<len; i++) {
        if(nums[i] > 0) res.push_back(i+1);
    }
    return res;
}
```
**Time complexity:**  
  
$O(n)$.  
  
**Space complexity:**  
  
$O(1)$.  
Many people in the leetcode comment zone do not admit this is a $O(1)$ solution because it modifies the original array. However I still can't figure out or find anyone can solve without modifying or creating an array.  
