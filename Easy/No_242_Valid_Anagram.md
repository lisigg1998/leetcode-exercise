No.242 Valid Anagram
=========
Given two strings `s` and `t` , write a function to determine if `t` is an anagram of `s`.

Example 1:
```
Input: s = "anagram", t = "nagaram"
Output: true
```
Example 2:
```
Input: s = "rat", t = "car"
Output: false
```
Note:
You may assume the string contains only lowercase alphabets.

## Problem Analysis  

If `s` and `t` are anagrams, they contain same type of characters with exactly the same quantity. We can solve this with counting array.  

## How To (In C++)
### 1. counting array
```C++
bool isAnagram(string s, string t) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int count[26] = {0};
    for(int i = 0; i < s.size(); i++){
        count[s[i]-'a']++;
    }
    for(int i = 0; i < t.size(); i++){
        if(count[t[i]-'a'] > 0) count[t[i]-'a']--;
        else count[t[i]-'a']++;
    }
    for(int i = 0; i < 26; i++){
        if(count[i] != 0) return false;
    }
    return true;
}
```
**Time complexity:**  
  
$O(m+n)$, where m and n are the size of `s` and `t`.  

**Space complexity:**
  
O(1), since the amount of lower-case letters are limited.  

### 2. general case, using map
If the two strings are in unicode and they are not just lower-case English characters, we can use map instead of fixed-size array:  
```C++
bool isAnagram(string s, string t) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    map<char,int> count;
    for(int i = 0; i < s.size(); i++){
        if(count.find(s[i]) == count.end()) count[s[i]] = 1;
        else count[s[i]]++;
    }
    for(int i = 0; i < t.size(); i++){
        if(count.find(t[i]) == count.end()) return false;
        else {
            count[t[i]]--;
            if(count[t[i]] == 0) count.erase(t[i]);
        }
    }
    return count.empty();
}
```
**Time complexity:**  
  
$O(m+n)$, where m and n are the size of `s` and `t`.  

**Space complexity:**
  
O(n), if the "characters" are any kinds of symbols.
    
