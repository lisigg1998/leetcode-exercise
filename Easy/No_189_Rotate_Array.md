No.189 Rotate array
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

Multiple ways can solve this question. But **make sure do mod arithmetic to `k` before rotating**, since `k` can be larger than the size of the array.  

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

### 3. cyclic replacement
```C++
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        int count = 0;
        for (int start = 0; count < nums.size(); start++) {
            int current = start;
            int prev = nums[start];
            do {
                int next = (current + k) % nums.size();
                int temp = nums[next];
                nums[next] = prev;
                prev = temp;
                current = next;
                count++;
            } while (start != current);
        } 
    }
```
See the idea & the proof [here](https://leetcode.com/problems/rotate-array/solution/).  


### 4. reverse
In C++ `<algorithm>` library there is a function `reverse()` which can be used to reverse a linear container which can be ordered (such as array, vector). Looking closely into the question, we can find out that the result array can be generated within three times of reverse. First, reverse the whole sequence. Second, reverse the first k sequence. Finally, reverse the sequence from k+1 to end.  
```C++
void rotate(vector<int>& nums, int k) {
    if(nums.empty()) return;
    k = k % nums.size();
    reverse(nums.begin(),nums.end());
    reverse(nums.begin(),nums.begin()+k);
    reverse(nums.begin()+k,nums.end());
}
```

**Time complexity:**  
  
$O(n)$, because `reverse()` takes only $O(n)$ time. We reverse n elements, k elements and n-k elements in total.
  
**Space complexity:**  
  
$O(1)$, because no extra space is needed. 
