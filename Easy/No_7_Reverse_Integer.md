No.7 Reverse Integer
=========
Given a 32-bit signed integer, reverse digits of an integer.

## Problem requirements
  
The input is an integer with base 10. Using x % 10 can get the tail digit, and x /= 10 get the "rest digit".  
  
However, the problem require us to deal with the overflow by our own. Because it is a 32-bit signed integer, so
the range of input value is [$-2^31$,2^31-1].

## How To (In C++)
```C++
    int reverse(int x) {
        int rev = 0;
        if(x == INT_MIN) return 0;
        x = x>0 ? x : -x;
        while(x) {
            if(rev > INT_MAX/10 || (rev == INT_MAX/10 && x%10 > 7)) {
                return 0;
            }
            rev = rev * 10 + x%10;
            x/=10;
        }
        return rev>0 ? rev : -rev;
    }
```
  
Notice that how to deal with overflow. 
  
