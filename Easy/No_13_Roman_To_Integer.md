No.13 Roman To Integer
=========
Convert a string of Roman into integer.  

## Problem requirements
  
There is a special rule of Roman number expression. For example, I puts before V and X means 4 and 9. The algorithm
should be able to deal with such kind of conversions.  

## How To (In C++)
### 1. Direct way
```C++
// Time: 24ms, 25.89%
int romanToInt(string s) {
        int i=0, n = s.length()-1, res=0;
        while(i <= n){
            if(i==n)
                return res+auxOne(s[i]);
            else{
                if(s[i]=='I'){
                    if(s[i+1]=='V' || s[i+1]=='X'){
                        res+=auxTwo(s[i],s[i+1]);
                        i+=2;
                    }
                    else{
                        res+=auxOne(s[i]);
                        i++;
                    }
                }
                else if(s[i]=='X'){
                    if(s[i+1]=='L' || s[i+1]=='C'){
                        res+=auxTwo(s[i],s[i+1]);
                        i+=2;
                    }
                    else{
                        res+=auxOne(s[i]);
                        i++;
                    }
                }
                else if(s[i]=='C'){
                    if(s[i+1]=='D' || s[i+1]=='M'){
                        res+=auxTwo(s[i],s[i+1]);
                        i+=2;
                    }
                    else{
                        res+=auxOne(s[i]);
                        i++;
                    }
                }
                else{
                    res+=auxOne(s[i]);
                    i++;
                }
            }
        }
        return res;
    }
    
    int auxOne(char s1){
        if(s1=='I') return 1;
        else if(s1=='V') return 5;
        else if(s1=='X') return 10;
        else if(s1=='L') return 50;
        else if(s1=='C') return 100;
        else if(s1=='D') return 500;
        else if(s1=='M') return 1000;
        return -1;
    }
    
    int auxTwo(char s1, char s2){
        if(s1=='I' && s2=='V') return 4;
        else if(s1=='I' && s2=='X') return 9;
        else if(s1=='X' && s2=='L') return 40;
        else if(s1=='X' && s2=='C') return 90;
        else if(s1=='C' && s2=='D') return 400;
        else if(s1=='C' && s2=='M') return 900;
        return -1;
    }
```
There are two auxiliary functions. One convert one Roman digit into a number, and another convert special Roman expressions.
The algorithm probes two characters each time. If a special expression is found, call `auxTwo()` and then add the probing index
by 2. Otherwise, call `auxOne()` then add index by 1.  
This method however is slow, because it is doing too many if conditions, making it inefficient and tedious.  
  
### 2. Optimized way
```C++
// Time: 4ms, 98.63%
int romanToInt(string s) {
        if (s.empty()) return 0;        
        int n = s.length();
        int r = auxOne(s[n - 1]);
        int now, last = r;
        for (int i = n - 2; i > -1; i--) {
            now = auxOne(s[i]);
            r += (now < last) ? -now : now;
            last = now;
        }
        return r;
    }
    
    int auxOne(char s1){
        if(s1=='I') return 1;
        else if(s1=='V') return 5;
        else if(s1=='X') return 10;
        else if(s1=='L') return 50;
        else if(s1=='C') return 100;
        else if(s1=='D') return 500;
        else if(s1=='M') return 1000;
        return 0;
    }
```
This method indexes from the tail. **Notice that in the special expressions, the integer value of the second character is larger
than the value of the first character, and the value of the entire expression is exactly val(s2)-val(s1).** Using this property
we only need one ternary condition operation.  
Also, the type of `str[i]` is `char&`, be careful when passing `str[i]` to a function.
