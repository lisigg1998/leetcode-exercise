No.7 Reverse Integer
=========
Given a 32-bit signed integer, reverse digits of an integer.

## Problem requirements
  
The input is an integer with base 10. Using x % 10 can get the tail digit, and x /= 10 get the "rest digit".  
  
However, the problem require us to deal with the overflow by our own. Because it is a 32-bit signed integer, so
the range of input value is [$-2^{31},2^{31}-1$]. $2^{31}-1\=2147483647$, so make sure rev < INT_MAX/10 or rev == INT_MAX/10 and
x%10 > 7 if x>0. If x < 0, just translate it into positive.

## How To (In C++)
```C++
    int reverse(int x) {
        int rev = 0;
        if(x == INT_MIN) return 0;
        int n = x>0 ? x : -x;
        while(n) {
            if(rev > INT_MAX/10 || (rev == INT_MAX/10 && n%10 > 7)) {
                return 0;
            }
            rev = rev * 10 + n%10;
            n/=10;
        }
        return x>0 ? rev : -rev;
    }
```
  
Notice that how to deal with overflow. 
  
