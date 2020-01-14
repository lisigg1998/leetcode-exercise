No.1122 Relative Sort Array
=========
Given two arrays `arr1` and `arr2`, the elements of `arr2` are distinct, and all elements in `arr2` are also in `arr1`.  
  
Sort the elements of `arr1` such that the relative ordering of items in `arr1` are the same as in `arr2`.  Elements that don't appear in `arr2` should be placed at the end of `arr1` in ascending order.  
  
Constraints:
  
1. `arr1.length`, `arr2.length` <= 1000
2. 0 <= `arr1[i]`, `arr2[i]` <= 1000
3. Each `arr2[i]` is distinct.
4. Each `arr2[i]` is in arr1.


## Problem Analysis  

This problem can be solved by brute force way, or use counting sort (bucket sort).  
  
### What is counting sort?  
Counting sort is a kind of non-comparison sort that trade space for time. It is specifically fit for sorting integers.  
  
Suppose that we know an array `arr` being sorted is of size `n`, and we know the elements are all integer in range `[0,b]`. Then we first create another integer array `counting` of size b+1, with all elements initialized as 0. When we iterate through `arr`, we count the number of `arr[i]` by `counting[arr[i]]++`. After the iteration, `counting[i]` should have the number of `i` in `arr`. Because labels `i` are sorted, so just output `i` in order according to their numbers.  

## How To (In C++)
```C++
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    int* counting = new int[1001](); // initialize all elements to 0
    for(int i : arr1){
        counting[i]++;
    }
    vector<int> res;
    // insert with relative order
    for(int i : arr2){
        res.insert(res.end(),counting[i],i); // inserting counting[i] numbers of i into res.end()
        counting[i]=0; // turn zero because it is inserted
    }
    // insert elements not in arr2
    for(int i = 0; i < 1001; i++){
        if(counting[i] != 0) res.insert(res.end(),counting[i],i);
    }
    return res;
}
```
First, do counting sort of `arr1`. Then, according to the elements and the order in `arr2`, insert numbers with the relative order. Finally, insert elements not in `arr2` in ascending order.  
**Time complexity:**  
$O(n)$
