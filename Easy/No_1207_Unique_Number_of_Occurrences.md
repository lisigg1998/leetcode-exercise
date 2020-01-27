No.1207 Unique Number of Occurrences
=========
Given an array of integers arr, write a function that returns true if and only if the number of occurrences of each value in the array is unique.


Example 1:
```
Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
```
Example 2:
```
Input: arr = [1,2]
Output: false
```
Example 3:
```
Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true
 ```

Constraints:

`1 <= arr.length <= 1000`
`-1000 <= arr[i] <= 1000`

## Problem Analysis  

This problem can be solved by two mapping. First, we use map to count repeating number of each interge in `arr`. Then, we use another map to count all repeating numbers. If repeating numbers do not repeat (for example, repeating number i only occurs once), the algorithm return true.  
  

## How To (In C++)
### 1. two maps
 
```C++
bool uniqueOccurrences(vector<int>& arr) {
    if(arr.size() == 1) return true;
    // first map: count repeating number of each integer
    unordered_map<short,short> temp;
    for(int i : arr){
        if(temp[i] >= 0){
            temp[i]++;
        }
        else temp[i] = 1;
    }
    // second map: count repeating numbers
    unordered_map<short,short> temp2;
    for(auto& pair : temp){
        if(temp2[pair.second] >= 0){
            temp2[pair.second]++;
        }
        else temp2[pair.second] = 0;
    }
    // redundant repeating number will cause false
    for(auto& pair : temp2){
        if(pair.second != 1) return false;
    }
    return true;
}
```
There is a second version of this type of method. **The second map can be replaced by a set.** We can either check if `map.size() == set.size()`, or return false when`s.insert(element).second == false`.  

**Time complexity:**  
$O(n)$. The code above will go through 3n loops in the worst case. The code below should be better:
```C++
bool uniqueOccurrences(vector<int>& arr) {
  unordered_map<int, int> m;
  unordered_set<int> s;
  for (auto n : arr) ++m[n];
  for (auto& p : m)
      if (!s.insert(p.second).second) return false;
  return true;
}
```
  
**Space complexity:**  
$O(m)$, where m is the number of unique integers.  

### 2. counting sort

This specific question gives us the range of input and the maximum size of input. In this case we can definitely use counting sort. We first count integers in a counting array, and then sort the counting array. Finally we examine the sorted array to see if two adjacent elements (namely two counts) are the same.  
```C++
bool uniqueOccurrences(vector<int>& arr) {
  short m[2001] = {};
  for (auto n : arr) ++m[n + 1000];  // counting
  sort(begin(m), end(m));  // sorting
  for (auto i = 1; i < 2001; ++i)
      if (m[i] && m[i] == m[i - 1]) return false;  // m[i] must > 0 (have occurred in arr)
  return true;
}
```
Because we know the maximum size of input, we don't even need to sort. Check the following code:  
```C++
bool uniqueOccurrences(vector<int>& arr) {
    short m[2001] = {}, s[1001] = {};
    for (auto n : arr) ++m[n + 1000];
    for (auto i = 0; i < 2001; ++i)
        if (m[i] && ++s[m[i]] > 1) return false;  // ++s: increase before comparing
    return true;
}
```
The repeating time must be less than 1001, so we can use another counting array to count the repeating time.  
**Method 2 is actually a specification of method 1.** The two map (or map and set) are two "counting arrays" to some extent.  

**Time complexity:**  
First solution: $O(n + m log m)$.  
Second solution: $O(n)$.  
  
**Space complexity:**  
$O(m)$, where m is the number of unique integers.  
