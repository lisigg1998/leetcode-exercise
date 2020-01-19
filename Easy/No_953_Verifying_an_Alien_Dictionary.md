No.953 Verifying an Alien Dictionary
=========
In an alien language, surprisingly they also use english lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.  
  
Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographicaly in this alien language.  
  
Example 1:  
```
Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
```
Example 2:  
```
Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
```
Example 3:  
```
Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
```

Constraints:  

1. 1 <= `words.length` <= 100
2. 1 <= `words[i].length` <= 20
3. `order.length` == 26
4. All characters in` words[i] `and `order` are English lowercase letters.  

## Problem Analysis  

According to the `order`, we have a rank for each possible word. A dictionary of words are ordered only if they are ranked in non-decreasing rank. To justify non-decreasing, we just need to check each pair of adjacent words.  
  

## How To (In C++)
```C++
bool isAlienSorted(vector<string>& words, string order) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i = 0; i < words.size()-1; i++){
        string prev = words[i], next = words[i+1];
        for(int j = 0; j < min(prev.size(),next.size()); j++){
            if(order.find(prev[j]) < order.find(next[j])) goto True_cond;
            else if(order.find(prev[j]) > order.find(next[j])) return false;
            else continue;
        }
        if(prev.size() > next.size()) return false;
        True_cond:
            continue;
    }
    return true;
}
```
For each pair of adjacent words, we check each character position. If in one position, the previous word's rank is larger than the next word's, we can immediately return false. If one word is the substring of another, but the previous word is the longer one, we can also return false. Otherwise, the adjacent words are in order, but only for them. We return true if and only if all pairs of adjacent words return true.  
  
**Time complexity:**  
Suppose the number of words is `n`, the average length of words is `k`. Then the time complexity is $O(nk)$.  
  
**Space complexity:**  
$O(1)$.  
