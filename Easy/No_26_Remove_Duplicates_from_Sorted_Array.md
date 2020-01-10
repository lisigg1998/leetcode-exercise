No.26 Remove Duplicates from Sorted Array
=========
Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

## Problem requirements
  
The problem requires us to remove duplicated elements in a sorted array. Specifically, we should remove elements in-place, so no additional arrays should be created.  
  
  **Notice that the question does not require actually "cutting" the array.** As long as the function returns the correct 
length `len` of the modified non-repeating array, and `array[0:len-1]` is the resulting array, the question is done.

## How To (In C++)
  
1. Use two pointers  

```C++
    // Time: 16ms, 99.25%
    // Space: 9.9MB, 93.75%
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
            return 0;
        if(nums.size()==1)
            return 1;
        int temp = nums[0];
        int ind = 1;
        int s = nums.size();
        
        for(int i = 0; i < s; i++){
            if(nums[i]!=temp){
                nums[ind]=nums[i];
                temp = nums[i];
                ind++;
            }
        }
        return ind;
    }
```  

After the for loop completes, all non-repeating elements are moved to the beginning of the array. Counting size while looping
may save time.  

2. Use STL

```C++
#include <algorithm> // to use unique()
        // Time: 24ms, 62.31%
        // Space: 9.8MB, 97.50%
        int removeDuplicates(vector<int>& nums) {
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
        return nums.size();
    }
```

`unique()` is used to de-duplication. It can be used to some containers like vector. It receives the starting and ending address
of the container, and returns the **tail address** of the resulting array. It also does not cut the original array.  
If cutting the array is needed, using `erase()` method of the vector should be helpful.
