No.387 First Unique Character in a String
=========
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each character can only be used once).

Return the sum of lengths of all good strings in words.

 

Example 1:
```
Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation: 
The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
```
Example 2:
```
Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation: 
The strings that can be formed are "hello" and "world" so the answer is 5 + 5 = 10.
 ```

Note:

`1 <= words.length <= 1000`
`1 <= words[i].length, chars.length <= 100`
All strings contain lowercase English letters only.

## Problem Analysis  

This question is among many questions that can be solved by "counting array" or "map/set". Since we **know the input range** we can just uset counting array.  
  

## How To (In C++)
### 1. counting array
 
```C++
int countCharacters(vector<string>& words, string chars) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int res=0;
    vector<int> count_chars(26,0);
    vector<int> count_word(26,0);
    for(const auto& i: chars) count_chars[i-'a']++;
    for(const auto& word: words){
        for(const auto& i: word) count_word[i-'a']++;  // count each word
        bool judge = 1; 
        for(int i = 0 ;i < 26; i++){
            if(count_chars[i] < count_word[i]) judge &= 0;  // judge = false if one does not match
            count_word[i] = 0;  // reinitialize count_word
        }
        res = judge ? res + word.size() : res;
    }
    return res;
}
```
No special algorithm technique here. Pay attention to `const auto&` when iterating through a `string`. **Using reference will make the code more space efficient**.  

**Time complexity:**  
$O(nk)$, where n is the number of words and k is the average number of characters in a word.    
  
**Space complexity:**  
$O(1)$, because we have 2 integer arrays with size 26.  
