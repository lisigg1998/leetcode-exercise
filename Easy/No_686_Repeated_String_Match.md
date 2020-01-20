No.686 Repeated String Match
=========
Given two strings `A` and `B`, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with `A` = "abcd" and `B` = "cdabcdab".

Return 3, because by repeating `A` three times (“abcdabcdabcd”), `B` is a substring of it; and `B` is not a substring of `A` repeated two times ("abcdabcd").

Note:
The length of `A` and `B` will be between 1 and 10000.

## Problem Analysis  

Many languages has build-in methods for finding substrings, so this should not be the problem (interestingly, many people in the leetcode discussion area, even in the solution area tried to optimize this). The problem is how to properly count repeating times?  

Assume that `q` is the minimum number that `len(A*q) >= len(B)`. We just need to do `find substring` operation in `q` and `q+1` repeating times situation. When `repeating times < q`, B cannot be the substring of A. If `repeating times == q+1` but B still cannot be the substring of `A * (q+1)`, more repeating times are meaningless.  

## How To (In C++)
### 1. Brute force
```C++
int repeatedStringMatch(string A, string B) {
    vector<int> lettersA(26, 0), lettersB(26, 0);
        for(char& i : A)
            lettersA[i - 'a']++;
        for(char& i : B) 
            lettersB[i - 'a']++;
        for(int i = 0; i < 26; i++)
            if(lettersB[i]>0 && lettersA[i]==0) return -1;
    string a = A;
    int repeat = 1;
    while(a.size() < B.size()){
        a += A;
        repeat++;
    }
    if(a.find(B) != string::npos){
        return repeat;
    }
    else{
        a += A;
        repeat++;
        if(a.find(B) != string::npos){
            return repeat;
        }
        else
            return -1;
    }
    return -1;
}
```
First, we can do a simple check-out to sift most of the false cases. If B contains character that does not appear in A, then return -1 directly. Then find out `q` and check situation `q` and `q+1`.  

**Time complexity:**  
   
$O(mqn)$. `find()` method consumes $O(mn)$ time, and the length of `a` is `m * q`.  

**Space complexity:**  

$O(mq)$, since we create `a`.  

### 2. Optimized way
Many programmer choose to write own KMP substring detection algorithm. If not for OI or interview requirements, this is unnecessary.  
About KMP: check [this link](https://blog.csdn.net/starstar1992/article/details/54913261).  
