No.1025 Divisor Game
=========
Alice and Bob take turns playing a game, with Alice starting first.  

Initially, there is a number N on the chalkboard.  On each player's turn, that player makes a move consisting of:  

Choosing any x with 0 < x < N and N % x == 0.  
Replacing the number N on the chalkboard with N - x.  
Also, if a player cannot make a move, they lose the game.  

Return True if and only if Alice wins the game, assuming both players play optimally.  

 

Example 1:
```
Input: 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.
```
Example 2:
```
Input: 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
 ```

Note:

`1 <= N <= 1000`

## Problem Analysis  

This is a math problem which can be solved by induction.  

First, we need to use the following two rules:  
1. If N makes Alice lose, then N+1 makes Alice win.
2. When Alice starts with an odd number, any move will results in an even number.  
  
Rule 1 is simple to prove. N+1 makes Alice win since she just need to do `(N+1)-1` and let Bob deal with N, then Bob will lose.  
Rule 2 is also very straightforward. Odd number has only odd factors, so subtracting any factor will results in an even number.  

With the two rules, we can prove that **when Alice receives an odd number, she will lose; when she receives an even number, she will win**.  
We prove by strong induction:  
**If when n < k, the former proposition holds → n = k also holds, then the whole proposition is true.**  
1. When n = 1:  
When Alice receive 1, she lose because she cannot make further move.  
2. When n = 2:  
Because 1 will make Alice lose, 2 will make her win according to rule 1.  
3. When n < k, odd numbers make Alice lose and even numbers make her win:  
If n is odd, according to rule 2, Bob will receive an even number less than k. So Bob wins, Alice lose;  
If n is even, n-1 is an odd number less than k. So with n-1 Alice lose, then (n-1+1) makes her win.  
In conclusion, n = k also holds.  


## How To (In C++)
```C++
bool divisorGame(int N) {
    return N%2 == 0;
}
```
