No.268 Missing Number
=========
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

## Problem Analysis  

This is a very simple question that can be solved by multiple way. Remember the elements in the array are distinct, are in a fixed range, and only one element is missing.  

## How To (In C++)
### 1. Sort & brute force find
First, sort the array with any sorting algorithm. Second, go through the sorted array and compare if `nums[i]-1==nums[i-1]` to find the missing number.  
**Time complexity:**  
Sorting at least takes $O(nlogn)$ (except trading space for time). Brute force finding takes $O(n)$. So totally it is $O(nlogn)$.  

### 2. Hashset & brute force
First, insert all elements in a hashset, then find with brute force. This is even simpler than sorting.  
**Time complexity:**  
Although finding if an element in a hashset takes only $O(1)$ time, inserting all elements and trying from 0 to n still takes $O(n)$ time. Also, the space complexity is $O(n)$.  

### 3. Math solution  
When you think about it, the range of elements are from 0 to n. The sum of the array plus the missing element is equal to a fixed value. In this case, the problem can be solved like:  
```C++
    int missingNumber(vector<int>& nums) {
        int result = 0;
    for (int i = 0; i < nums.size(); ++i) {
        result += (i+1)-nums[i];
    }
    return result;
    }
```
In `<numeric>` library of C++, we can use `accumulate(v.begin(),v.end(),0)` to make the code even simpler.  
**Time complexity:**  
$O(n)$. Space complexity is $O(1)$.

### 4. XOR solution
There are some interesting features about XOR operation. For example:
1.`a^0=a`;
2.`a^a=0`;
3.`a^b^a=b`;  
This problem can be solved using these features. Assume `T` is the value to XOR all elements in the array. Then, the XOR or all numbers from 0 to n is `T^x`, where `x` is the missing number. So `x=T^(T^x)=(T^T)^x=0^x`, and we get the answer:  
```C++
int missingNumber(vector<int>& nums) {
        int n=nums.size();
        int ans=0;
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        for(int i=0;i<n;i++){
            ans^=(i+1)^nums[i];
        }
        return ans;
    }
```
Notice the two line:  
```C++
        ios_base::sync_with_stdio(false);
        cin.tie(0);
```
They can unsyncrinize stdio and untie cin so that the input speed is increased.  
**Time complexity:**  
The time complexity is $O(n)$.




