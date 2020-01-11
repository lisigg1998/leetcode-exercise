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
But directly using this method is too tedious. Actually, it is better to just do decimal addition first, and then convert the decimal value to "sum" and "carry out".  
Third, there are many ways to concatenate and adding something to a string. Performance varied among methods.  
Here is the code:  
```C++
string addBinary(string a, string b) {
	string res = "";
	int c = 0, i = a.length() - 1, j = b.length() - 1;

	while (i >= 0 || j >= 0 || c == 1) {
		c += i >= 0 ? a[i--] - '0' : 0;
		c += j >= 0 ? b[j--] - '0' : 0;
		res.insert(0, 1, char(c % 2 + '0'));
		c /= 2;
	}
	return res;
}
```
This is a very neat code with high efficiency. First, see the while loop part. It is not necessary to determine which input string is longer, just count down two indexes in each iteration and determine if the index is less than zero before doing an indexing.  
How to do the addition? This code just get an integer result first. It uses a good way to get decimal results from character type. Because arithmetic calculation between `char` type variables can be seen as calculation between ASCII values, `a[i--] - '0'` can get
0 or 1. `c` is itself a carry in at the beginning of the while loop. After addition, `c` contains both "sum" and "carry out" information. If turn `c` into a two-digits binary number, the LSB is "sum", and then the MSB is "carry out", which is the new carry in. "sum" is the digit we want to add to the result string. Carry out can be used as the next carry in. If i and j both count down to zero but c is still equal to 1, it means there is a final carry bit need to be added.  
As for how to form the result string, we can compare two operations:
1. `res.insert(0, 1, char(c % 2 + '0'));`  
2. `res = char(c % 2 + '0') + res;`  
  
The first one is faster. If using method 2, each iteration will create a new string object, which will cause additional overhead.  
Plus, somebody choose to use `str.push_back()` to create a reversed string and then reverse it back before return. This method and
the method 1 have the same complexity as $O(n)$.  

## Advanced question
### How to do subtraction?
Transform the subtractor to its opposite using **completion code plus 1**.  

