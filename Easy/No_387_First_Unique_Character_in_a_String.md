No.387 First Unique Character in a String
=========
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:
```
s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
```
Note: You may assume the string contain only lowercase letters.

## Problem Analysis  

To find all non-repeating characters, we can also use counting method. Then we need to find the non-repeating character with the smallest index. We can solve this "dynamically" (find when we need the value) or "statically" (already store the value before we use).
  

## How To (In C++)
### 1. counting array, "dynamically"
 
```C++
int firstUniqChar(string s) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if(s.size() == 0) return -1;
    if(s.size() == 1) return 0;
    vector<int> count(26,0);
    for(const auto& c : s) count[c-'a']++; // counting characters
    int res = INT_MAX;
    for(int i = 0; i < 26; i++){
        if(count[i] == 1){
            int pos = s.find(char(i+'a'));
            if(pos != string::npos) res = min(res, pos);
        }
    }
    return (res < INT_MAX) ? res : -1;
}
```
This method counts and finds unique characters first. Then, it use `find` to obtain smallest index of unique character. Notice that by using `find`, we avoid traversing the string `s` again.  

**Time complexity:**  
$O(n)$, where n is the number of characters in a word.  
  
**Space complexity:**  
$O(1)$.  

### 2. unordered map, "statically"
```C++
int firstUniqChar(string s) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if(s.size() == 0) return -1;
    if(s.size() == 1) return 0;
    unordered_map<char, pair<int,int>> count;   // pair.first is count, pair.second is the first appearing index
    int range = s.size();
    for(int i = 0; i < range; i++){
        count[s[i]].first++;
        count[s[i]].second = i;
    }

    int res = INT_MAX;
    for(const auto& a : count){
        if(a.second.first == 1){
            res = min(res, a.second.second);
        }
    }
    return (res < INT_MAX) ? res : -1;
}
 ```
 This method uses an `unordered_map` to store the character, count and its first appearing index. We obtain all those information in one traversing process. Then we just need to go through the map to find the smallest index. 
 
 **Time complexity:**  
$O(n)$, where n is the number of characters in a word. Although this method just go through the string once, it is slower than method 1.  
  
**Space complexity:**  
$O(1)$.  
