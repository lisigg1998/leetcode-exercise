No.26 Remove Duplicates from Sorted Array
=========
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

## Problem requirements
  
The problem can be solved by binary search. The key point is to accurately analyze boundary conditions.

## How To (In C++)
  
```C++
// Time: 4ms, 98.19%
// Space: 8.9MB, 57.81%
int searchInsert(vector<int>& nums, int target) {
    int i=0, j=nums.size()-1,mid=0;
    while(i!=j){
        mid = (i+j)/2;
        if(nums[mid]==target){
            return mid;
        }
        else if(nums[mid]>target){
            j=mid;
        }
        else{
            i=mid+1;
        }
    }
    return (nums[i]>=target) ? i : i+1;
}
```
In this piece of code, when the while loop ends, i is equal to j. nums[i] is or is not the target, then just return 
the index according to the results of (nums[i]>=target).  
Also, this problem can be solved by recursion:
```C++
// Time: 4ms, 98.19%
    // Space: 8.9MB, 57.81%
    int searchInsert(vector<int>& nums, int target) {
        return searchInsertRecursive(nums,target,0,nums.size()-1);       
    }
    int searchInsertRecursive(vector<int>& nums, int target, int low, int high){
        if(low==high){
            return (nums[low]>=target) ? low : low+1;
        }
        int mid=(low+high)/2;
        if(nums[mid]==target){
            return mid;
        }
        else if(nums[mid]>target){
            return searchInsertRecursive(nums, target,low,mid);
        }
        else{
            return searchInsertRecursive(nums, target,mid+1,high);
        }
    }
```  
Recursion is a little bit slower because function stack overhead, and the code is not neater.

## Advanced question:
**How if there are repeating elements?**  
Suppose the target always exists but there are duplicated elements. There are two situations:  
1. Find the target element with the smallest index  
2. Find the target element with the largest index  
  
It is actually very simple. In situation 1, just let `j=mid` when `nums[mid]>=target`. By this boundary we are making sure
that j is approaching to the left most target element.  
Similarly, let `i=mid` when `nums[mid]<=target` in situation 2. However, the condition to break the while loop should be 
`low+1<high`.

