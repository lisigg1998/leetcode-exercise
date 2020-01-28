No.1160 Find Words That Can Be Formed by Characters
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
 
```C++
vector<string> commonChars(vector<string>& A) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<vector<int>> temp(26,vector<int>(A.size(),0));

    int i = 0;
    for(string word : A){
        for(char character : word){
            temp[character - 'a'][i]++;
        }
        i++;
    }

    vector<string> res;
    for(int i = 0; i < 26; i++){
        int count = INT_MAX;
        for(int j = 0; j < temp[i].size();j++){
            if(temp[i][j] < count) count = temp[i][j];
        }
        for(int k = 0; k < count; k++){
            string s(1,char('a'+i));
            res.push_back(s);
        }
    }
    return res;
}
```
Pay attention to the way how **`char` type can transform to `string` type**.  

**Time complexity:**  
$O(nk)$, where n is the number of words and k is the average number of characters in a word.    
  
**Space complexity:**  
$O(n)$, because we have 26 integer vectors with size n.  

### 2. only two counting arrays

```C++
vector<string> commonChars(vector<string>& A) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int> cnt(26, INT_MAX);
    vector<string> res;
    for (auto s : A) {
        vector<int> cnt1(26, 0);
        for (auto c : s) ++cnt1[c - 'a'];
        for (auto i = 0; i < 26; ++i) cnt[i] = min(cnt[i], cnt1[i]);
    }
    for (auto i = 0; i < 26; ++i)
        for (auto j = 0; j < cnt[i]; ++j) res.push_back(string(1, i + 'a')); 
    return res;
}
```
                                 
If we think about it, we just need to maintain the minimum repeating number of each character in each word. Instead of a 2d array, we just use two 1d arrays. One stores the current minimum counts, and one stores the counts of current words. In each iteration, we update the current minimum counts.  

**Time complexity:**  
$O(nk)$, where n is the number of words and k is the average number of characters in a word.    
  
**Space complexity:**  
$O(1)$, because we only two arrays with size 26.  
