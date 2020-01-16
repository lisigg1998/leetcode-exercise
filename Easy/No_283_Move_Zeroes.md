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
### 1. erase & insert
```C++
void moveZeroes(vector<int>& nums) {
    for(int i = nums.size()-1; i>=0;i--){
        if(nums[i]==0){
            nums.erase(nums.begin()+i);
            nums.insert(nums.end(),0);
        }
    }
}
```
**Time complexity:**  
$O(n^2)$, because erase and insert both needs $O(n)$ time.  
  
### 2. optimal way
```C++
void moveZeroes(vector<int>& nums) {
    int pos = 0;
    for(int i : nums){
        if(i!=0) nums[pos++] = i;
    }
    for(pos; pos<nums.size();pos++){
        nums[pos]=0;
    }
}
```
There is another way:  
```C++
void moveZeroes(vector<int>& nums) {
    for (int lastNonZeroFoundAt = 0, cur = 0; cur < nums.size(); cur++) {
        if (nums[cur] != 0) {
            swap(nums[lastNonZeroFoundAt++], nums[cur]);
        }
    }
}
```

**Time complexity:**  
$O(n)$. 
