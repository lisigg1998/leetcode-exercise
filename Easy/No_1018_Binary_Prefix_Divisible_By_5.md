No.1018 Binary Prefix Divisible By 5
=========
Given an array A of 0s and 1s, consider `N_i`: the i-th subarray from `A[0]` to `A[i]` interpreted as a binary number (from most-significant-bit to least-significant-bit.)

Return a list of booleans answer, where `answer[i]` is true if and only if `N_i` is divisible by 5.  

Note:  
1. 1 <= `A.length` <= 30000
2. `A[i]` is 0 or 1

## Problem Analysis  

**The length of `A` indicates that if we simply adding up digits the integer will definitely overflow.** We need to solve this problem with some math knowledge about mod arithmetics.  

## How To (In C++)
### Mod arithmetic without overflow  
For mod arithmetic, there is a fact that $(ab+c)%d\=((a%d)(b%d)+(c%d))%d$.  
  
The problem requires us to calculate about `A[0:i]`, and we know that `A[0:i] = A[0:i-1] * 2 + A[i]`(here we use `A[0:i]` to represent the ith binary number with the digit sequence `A[0:i]`). Using the mod arithmetic fact stated above, we know `A[0:i]%5 = ((A[0:i-1]%5) * 2 + A[i]) % 5`. And thus we have the code:  
```C++
  vector<bool> prefixesDivBy5(vector<int>& a) {
      ios_base::sync_with_stdio(false);
      cin.tie(0);
      vector<bool> answer;
      int num=0;
      for(int i=0; i<a.size(); i++)
      {
          num = ((num << 1) | a[i])%5;
          answer.push_back(num==0);
      }
      return answer;
  }
 ```
 To accelerate culculation speed, we can also use bitwise operation to replace normal 10_base arithmetic calculation, like using `<< 1` to represent `* 2`, and use `|` to represent `+`.  
  
**Time complexity:**  
$O(n)$
