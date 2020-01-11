No.67 Add Binary
=========
Add two strings of binary numbers, to form another string of binary number. Notice that the two strings may not have the same length.

## Problem requirements
  
The problem itself is very simple. Inputs and outputs are all strings, any manipulation can be done within the function. But it is not
easy to write a neat code to implement.  

## How To (In C++)
  
The basic steps are as follows:  
1. Align and obtain each digit;  
2. Do calculation according to the input digits, deal with carry in/ carry out;  
3. Add digit into the result string;  

First, how to align digits, since input strings may have different length? In that case, we may include two indexing starting from the
tail of two strings. When the shorter index counts down to less than zero, we can consider its digit as zero.  
Second, how to calculate binary addition? At first I tried to implement something like full adder by hard-coding the true value table.
But directly using this method is too tedious. Actually, it is better to just do decimal 
