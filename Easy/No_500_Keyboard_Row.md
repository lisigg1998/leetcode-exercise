No.500 Keyboard Row
=========
Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
 

Example 1:
```
Input: "USA"
Output: True
```

Example 2:
```
Input: "FlaG"
Output: False
``` 

**Note**: The input will be a non-empty word consisting of uppercase and lowercase latin letters.

## Problem Analysis  
If the string only has 1 character, then it is always true.  
If the string has two or more characters, there are three situations:  
1. If the first character is uppercase and the second character is uppercase, then `word[1:]` should be all uppercase;  
2. If the first character is uppercase and the second character is lowercase, then `word[1:]` should be all lowercase;  
3. If the first character is lowercase and the second character is lowercase, then `word[1:]` should be all lowercase;  
4. If the first character is lowercase and the second character is uppercase, return false;  
  
We can filter situation 4 in the beginning. Then, we know that **whether the consequtive characters are all lowercase or all uppercase is determined by `word[1]`**.  

## How To (In C++)
### 1. counting array
Because we know that `(time[i]+time[j]) % 60 == 0` is equal to `time[i]%60 + time[j]%60 == 0 or 60`, we can preprocess each `time[i]` with modular arithmetic. Then, we create a counting array of size n and count the amount of numbers from 0 to 59. Except for 0 and 30, `counting_arr[i] * counting_arr[60-i]` will be the number of pairs that `i` and `60-i` can form. 0 and 30 are counted by special way.  
```C++
bool detectCapitalUse(string word) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    if(word.length()==1)return true;

    int diff=word[1]>96?32:0;

    if(word[1]<91 && word[0]>96)return false; 

    for(int i=2;i<word.length();i++)
    {
        if(word[i]<65+diff || word[i]>90+diff)return false;
    }

    return true;
}
```

We notice that in ascii codes, lowercase and uppercase characters have the same range length, and ascii codes for corresponding lowercase and uppercase characters have a fixed difference of 32. Then we can adjust the conditional range according to `word[1]`, and check if each character of `word[1:]` is in the range of uppercase or lowercase.  

**Time complexity:**  
$O(n)$.  
  
**Space complexity:**  
$O(1)$.  
