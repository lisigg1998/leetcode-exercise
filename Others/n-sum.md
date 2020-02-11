The n-sum problem
=========
Given an array A of strings made only from lowercase letters, return a list of all characters that show up in all strings within the list (including duplicates).  For example, if a character occurs 3 times in all strings but not 4 times, you need to include that character three times in the final answer.

You may return the answer in any order.

 

Example 1:
```
Input: ["bella","label","roller"]
Output: ["e","l","l"]
```
Example 2:
```
Input: ["cool","lock","cook"]
Output: ["c","o"]
 ```

Note:

1 <= `A.length` <= 100
1 <= `A[i].length` <= 100
`A[i][j]` is a lowercase letter

## Problem Analysis  

It is natural to think that we need to count numbers of characters in each word, and then for each character we find out the minimum number of repetition in all words. There are two ways to achieve this.  
  

## How To (In C++)
### 1. 2d counting array
