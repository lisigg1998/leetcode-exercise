No.476 Number Complement
=========
Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

Note:
The given integer is guaranteed to fit within the range of a 32-bit signed integer.
You could assume no leading zero bit in the integer’s binary representation.
Example 1:
```
Input: 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
```
Example 2:
```
Input: 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
```
## Problem Analysis  

This problem requires understanding about bitwise operations. Many ways can solve it.  

## How To (In C++)
### 1. Pure bitwise operation
```C++
int findComplement(int num) {
    short count = 0;
    int a = num;
    while(a != 0){
        a >>= 1;
        count++;
    }
    uint32_t b = (-num-1);
    b <<= (32-count);
    return b >> (32-count);
}
```
First, use bitwise operation to determine where is the MSB of 1. Then, because we know that $neg\=complement \+ 1$, we can deduct that complement is equal to negation minus 1. Finally, use `uint32_t` to do left and right shift to eliminate leading 1 bits. Using `uint32_t` is because it is unsigned, so shifting is logical.  
  
### 2. Use XOR
```C++
int findComplement(int num) {
    bool st=false;
    for(int i=31;i>=0;--i){
        if(num&(1<<i)) st=true;
        if(st) num^=(1<<i);
    }
    return num;
}
```
We still need to find the MSB first. Then, from MSB down to LSB, we XOR each bit with 1. This will flip every bits from MSB to LSB, which is exactly what we want.  





