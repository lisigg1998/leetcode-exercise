No.1018 Binary Prefix Divisible By 5
=========
Given an array, rotate the array to the right by k steps, where k is non-negative.  
  
Example 1:
```
Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
```
Notice: k may be larger than the size of array. Rotating `arr.length()` time will get the original array. This condition is **not specified in the question** but it exists.  

## Problem Analysis  

Multiple ways can solve this question.  

## How To (In C++)
### 1. Brute force
```C++
void rotate(vector<int>& nums, int k) {
    for(int i = k; i > 0; i--){
        nums.insert(nums.begin(),nums[nums.size()-1]);
        nums.erase(nums.end()-1);
    }
}
```
The most simple way is to shift every element in each rotation. This is simple but very slow.  
  
**Time complexity:**  
  
$O(nk)$, because it moves n elements k times.  
  
**Space complexity:**  
  
$O(1)$  

### 2. Using extra array
```C++
void rotate(vector<int>& nums, int k) {
    vector<int> *res = new vector<int>();
    k = k%nums.size();
    int j = nums.size() - k;
    for (int i = 0; i < nums.size(); i++) {
        res->push_back(nums[(i+j) % nums.size()]);
    }
    nums=*res;
}
```
We can circulately-iterate elements in `nums` from `nums.size()-k` and then put the elements to another array starting from position zero.  
  
**Time complexity:**  
  
$O(n)$, because it iterate through the original array.  
  
**Space complexity:**  
  
$O(n)$, because it needs an extra array.  
