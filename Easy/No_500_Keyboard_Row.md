No.500 Keyboard Row
=========
Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard.  
Example:
```
Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
 ```

**Note:**

You may use one character in the keyboard more than once.  
You may assume the input string will only contain letters of alphabet.  

## Problem Analysis  

Because characters on one row of the keyboard does not have any explicit mathematical pattern, the only way to solve the problem is to use some data structure to store row-character relationships, and examine each character of each word. However the selection of proper data structure and examination method has impact on the speed and space efficiency.  

## How To (In C++)
### 1. map and direct comparison

```C++
 vector<string> findWords(vector<string>& words) {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        map<char,int> char_map = char_row_map();
        vector<string> res;
        int indicator;
        for(string word : words) {
            indicator = char_map[tolower(word[0])];
            for(int i = 0; i < word.size(); i++) {
                if(char_map[tolower(word[i])] != indicator) goto Cont;
            }
            res.push_back(word);
            Cont:
                continue;
        }
        return res;
    }
    map<char,int> char_row_map() {
        map<char,int> res;
        res['q'] = 1;
        res['w'] = 1;
        res['e'] = 1;
        res['r'] = 1;
        res['t'] = 1;
        res['y'] = 1;
        res['u'] = 1;
        res['i'] = 1;
        res['o'] = 1;
        res['p'] = 1;
        res['a'] = 2;
        res['s'] = 2;
        res['d'] = 2;
        res['f'] = 2;
        res['g'] = 2;
        res['h'] = 2;
        res['j'] = 2;
        res['k'] = 2;
        res['l'] = 2;
        res['z'] = 3;
        res['x'] = 3;
        res['c'] = 3;
        res['v'] = 3;
        res['b'] = 3;
        res['n'] = 3;
        res['m'] = 3;
        return res;
    }
```
We can build a map and map each character to a row number (1, 2 and 3). When we iterate each word, we set an indicator according to the row number of its first character. Then, we check if all characters of this word is on the same row.  

**Time complexity:**  
$O(nk)$, where n is the number of words and k is the average number of characters per word.  
  
**Space complexity:**  
$O(1)$, since the result array does not count, and the map size is limited by the alphabet.  

### 2. dict vector and bit manipulation
```C++
 vector<string> findWords(vector<string>& words) {
     ios_base::sync_with_stdio(false);
     cin.tie(0);
     vector<int> dict(26);
     vector<string> rows = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
     for (int i = 0; i < rows.size(); i++) {
         for (auto c : rows[i]) dict[c-'A'] = 1 << i;
     }
     vector<string> res;
     for (auto w : words) {
         int r = 7;
         for (char c : w) {
             r &= dict[toupper(c)-'A'];
             if (r == 0) break;
         }
         if (r) res.push_back(w);
     }
     return res;
 }
```
In method 1, we need a tedious function to create a character-row map. The comparison process is not beautiful, either. There is a way to make both better.  
#### 1. Improve character-row map with vector
Instead of hard-coding a map, we can use a terse method, although it is still hard-coding. 
```C++
vector<int> dict(26);
vector<string> rows = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
for (int i = 0; i < rows.size(); i++) {
    for (auto c : rows[i]) dict[c-'A'] = 1 << i;
}
```
Each position of `dict` stands for each character. We put characters on the same row into one single word. Then we use bit manipulation to give each character a "row number". "Row number" are binary number 001, 010 and 100. There is a feature that applying `&` operator to any two of them will result in 0. This feature will later help us do comparison.  
  
#### 2. Improve comparison with bit manipulation
```C++
for (auto w : words) {
    int r = 7;
    for (char c : w) {
        r &= dict[toupper(c)-'A'];
        if (r == 0) break;
    }
    if (r) res.push_back(w);
}
```
We use an integer `r` as an indicator and initialize it as 7 (binary number 111) to make sure the first comparison always true. After the first comparison (the `&=` operation), `r` will become the "row number" of the first character, which should be the "row number" of the rest of the characters in this word. If one character of this word is not on the same row, then `r` will become 0. Finally, if `r` is not 0, we can push this word to the result array.  

**Time complexity:**  
$O(nk)$, where n is the number of words and k is the average number of characters per word.  
  
**Space complexity:**  
$O(1)$, since the sizes of `dict` and `rows` are limited. Although we have two auxiliary variables, their total size is smaller than map, so they are more space efficient.  
