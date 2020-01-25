No.350 Intersection of Two Arrays II
=========
Given two arrays, write a function to compute their intersection.  

Example 1:  
``
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
``
Example 2:  
``
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
``
Note:  

Each element in the result should appear as many times as it shows in both arrays.  
The result can be in any order.  

Follow up:  

1.What if the given array is already sorted? How would you optimize your algorithm?  
2.What if nums1's size is small compared to nums2's size? Which algorithm is better?  
3.What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?  

## Problem Analysis  

We need to find the intersection of two arrays. That is a set of elements which appears both in `nums1` and `nums2`. The two arrays are not necessary non-duplicating, but we still need to treat each elements with the same value as unique. In many programming language, set operation can be directly completed with build-in `set` data structures. We can also use other method to solve the problem.  
  

## How To (In C++)
### 1. map
```C++
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    unordered_map<int,int> temp;
    vector<int> res;
    for(int i = 0; i < nums1.size(); i++) {
        if(temp[nums1[i]] >= 0) temp[nums1[i]]++;
        else temp[nums1[i]] = 0;
    }
    for(int i = 0; i < nums2.size(); i++) {
        if(temp[nums2[i]]-- > 0) res.push_back(nums2[i]);
    }
    return res;
}
```
This method adds one of the arrays into a map and counts the number of distinct integers. Then the algorithm iterate another array and generate intersection by comparing each elements with the map. Although this is relatively fast, map consumes lots of space, and if the arrays are too large to be put into the memory, this algorithm should be further improved.  

**Time complexity:**  
$O(m+n)$, where m and n are the size of `nums1` and `nums2`.  
  
**Space complexity:**  
$O(n)$, where n is the size of array inserted into the map.  

### 2. sorting and two pointers
```C++
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    sort(nums1.begin(),nums1.end());
    sort(nums2.begin(),nums2.end());
    int i=0,j=0;
    vector<int> res;
    while(i < nums1.size() && j < nums2.size()){
        if(nums1[i] < nums2[j]) i++;
        else if (nums1[i] > nums2[j]) j++;
        else{
            res.push_back(nums1[i]);
            i++; j++; 
        }
    }
    return res;
}
```
Since the elements are all integers, we can also get the intersection by sorting and then use two pointers. First, sort the two arrays. Then, put two pointers at the beginning of two arrays. While either of the pointer does not reach the end, compare the elements they point. If they are not equal, increase the pointer pointing to the smaller number by one. If two pointers point to the elements with the same value, push the element in the result array and increase both pointers by one.  

**Time complexity:**  
$O(nlogn)$. The comparison process will repeates at most n times, depending on the smallest size of two original arrays. However, the sorting algorithm has at least $O(nlogn)$ complexity, dragging the overall efficiency.  
  
**Space complexity:**  
$O(1)$. If original arrays do not count, and sorting algorithm also does not require extra space, this method will consumes much less space than method 1.  

### 3. set intersection method
```C++
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> out(nums1.size() < nums2.size() ? nums1.size():nums2.size() );
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        out.resize(std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), out.begin())-out.begin());
        return out;
    }
```
C++ has build-in set operations to complete this problem, for example `set_intersection()`. It does not require value of each elements should be different, but it requires that **the object it applies must be ordered containers**. And still **we need to sort the original arrays before using this method.**  

**Time complexity:**  
$O(nlogn)$. Although `set_intersection()` has linear time complexity, the sorting algorithm restricts the overall efficiency.  
  
**Space complexity:**  
$O(1)$, this method can generate result array inplace.  

## Advanced questions
1. If the given array is already sorted, method 2 and 3 are faster than method 1, and space consumption is much less.  
2. If one array's size is significantly smaller, method 2 and 3 are faster since we do not need to iterate through two arrays. However, we can improve space complexity of method 1 by inserting the smallest array into the map.  
3. If the memory is not large enough to contain original arrays, we can use external sort to sort the two arrays first, and then apply method 2 or 3.  
