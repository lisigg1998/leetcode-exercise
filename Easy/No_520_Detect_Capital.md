No.520 Detect Capital
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

If use brute force, the time complexity will be $O(n^2)$, which is not good. We need to find a $O(n)$ time solution, and this can be done by using a counting array.  
  

## How To (In C++)
### 1. counting array
Because we know that `(time[i]+time[j]) % 60 == 0` is equal to `time[i]%60 + time[j]%60 == 0 or 60`, we can preprocess each `time[i]` with modular arithmetic. Then, we create a counting array of size n and count the amount of numbers from 0 to 59. Except for 0 and 30, `counting_arr[i] * counting_arr[60-i]` will be the number of pairs that `i` and `60-i` can form. 0 and 30 are counted by special way.  
```C++
int numPairsDivisibleBy60(vector<int>& time) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int count = 0;
    vector<int> arr(60,0);
    for(int i = 0; i < time.size(); i++) {
        arr[time[i] % 60]++;
    }
    for(int i = 0; i < 31; i++){
        if(i == 0 || i == 30){
            count += (arr[i] * (arr[i]-1)) / 2;
        }
        else{
            count += arr[i]*arr[60-i];
        }
    }
    return count;
}
```

The code can be more simple. We can count the result when we are building the counting array. When we add a count to position `i`, it can form new `counting_arr[(60-i)%60]` pairs with those counted in `counting_arr[(60-i)%60]`. When all elements belong to position `i` and `(60-i)%60` are added, the number of pairs is precisely counted. So we have the code like this:  
```C++
int numPairsDivisibleBy60(vector<int>& time) {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        vector<int> c(60);
        int res = 0;
        for (int t : time) {
            res += c[(60 - t%60) % 60];
            c[t % 60] += 1;
        }
        return res;
    }
```

**Time complexity:**  
$O(n)$.  
  
**Space complexity:**  
$O(n)$.  
