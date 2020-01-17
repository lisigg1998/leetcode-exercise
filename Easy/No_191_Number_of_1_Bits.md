No.191 Number of 1 Bits
=========
Write a function that takes an unsigned integer and return the number of '1' bits it has (also known as the Hamming weight).  

## Problem Analysis  

Use mod 2 and loop method can solve this problem, but it is too slow to use an arithmetic approach. Instead, we should use bitwise manipulation approaches.  

## How To (In C++)
### 1. bitwise loop and flip
```C++
int hammingWeight(uint32_t n) {
    int bits = 0;
    int mask = 1;
    for (int i = 0; i < 32; i++) {
        if ((n & mask) != 0) {
            bits++;
        }
        mask <<= 1;
    }
    return bits;
}
```
### 2. bitwise without mask
```C++
int hammingWeight(uint32_t n) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    short count=0;
    while(n != 0){
        count++;
        n &= (n-1);
    }
    return count;

}
```
This method uses the feature that **n & (n-1) will flip the least significant bit, namely the lowest 1 bit**.  
  
**Time complexity:**  
$O(1)$, because the input number of bits is fixed.  
**Space complexity:**  
$O(1)$.


