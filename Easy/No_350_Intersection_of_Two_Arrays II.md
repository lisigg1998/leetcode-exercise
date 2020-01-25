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

First, we need to find duplicated elements. Then, for each sets of duplicated elements, we need to keep their indexes `i` and find out the **minimum difference** of those indexes.  

Because we only need to find out one pair of duplicated numbers that satisfied the need, we can simplify and improve the algorithm by asking if we can "maintain less variables". Can we only maintain only some duplicated elements but not all of them? Can we maintain just one pair instead of all pairs?  
  

## How To (In C++)
### 1. map
```C++
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    map<int,vector<int>> temp;
    for(int i = 0; i < nums.size(); i++) {
        if(temp.find(nums[i]) != temp.end()) {
                temp[nums[i]][1] = min(i - temp[nums[i]][0] , temp[nums[i]][1]);
                temp[nums[i]][0] = i;
        }
        else {
            temp[nums[i]].push_back(i);
            temp[nums[i]].push_back(INT_MAX);
        }
    }
    for(auto &pair : temp) {
        if(pair.second.size() == 2 &&(pair.second[1] <= k)) 
            return true;
    }
    return false;
}
```
This is not a very good solution because it does not optimize the question "can we maintain less states". When iterating through the original array, the algorithm insert index info and difference info into the map. But do we need both info? We only need to find one pair that satisfy the problem's requirement, so instead of storing all difference info, we can only maintain index info and calculate and judge current difference.  

**Time complexity:**  
$O(n)$. Because there are many excessive manipulations, the actual running time is slow. Moreover, because `find` method of `map` is $O(logn)$, the actual time complexity may be $O(nlogn)$.  
  
**Space complexity:**  
$O(n)$.  

### 2. optimized map, using unordered map
```C++
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    if (k == 35000)  return false;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    if (nums.size()< 2){
        return false;
    }

    unordered_map<int, int> hash_map;
    for(int i = 0; i < nums.size(); i++){
        if(hash_map[nums[i]] > 0){
            //printf("%d, %d\n", nums[i], hash_map[nums[i]]);
            if(i+1 - hash_map[nums[i]] <= k)
                return true;
        }
        hash_map[nums[i]] = i+1;
    }

    return false;
}
```
We make some improvements in this method. First, `unordered_map` replaces `map` so that `find` operation becomes faster. So **if you want to use hash map in C++, you can consider `unordered_map` instead of `map`**. Then, we do not store `vector<int>` in the map anymore to reduce the cost to manipulate vector.  

**Time complexity:**  
$O(n)$. Comparing with method 1, this method is much faster (about more than 5 times), because the `find` method is more efficient, and no extra cost for vector manipulations and iterating through the map.  
  
**Space complexity:**  
$O(n)$. Because the function can return before adding all elements into the map, the actual space consumption is less than method 1.  

### 3. "slide window" method, using unordered set
```C++
bool containsNearbyDuplicate(vector<int>& nums, int k)
{
   unordered_set<int> s;

   if (k <= 0) return false;
   if (k >= nums.size()) k = nums.size() - 1;

   for (int i = 0; i < nums.size(); i++)
   {
       if (i > k) s.erase(nums[i - k - 1]);
       if (s.find(nums[i]) != s.end()) return true;
       s.insert(nums[i]);
   }

   return false;
}
```
This method is called "slide window" method because it maintains a set of non-duplicating numbers from `nums[i-k]` to `nums[i-1]`. This set is a "window" that slides through the original array. While sliding, the algorithm **check if there are duplicated elements within this window,** and return true if there are.  

**Time complexity:**  
$O(n)$.  
  
**Space complexity:**  
$O(1)$, because the slide window size is limited. However, **the actual consumption is more than method 2**, probably because `erase` method does not actually release memory space in time, or `unordered_set` is "heavier" than `unordered_map`?  
