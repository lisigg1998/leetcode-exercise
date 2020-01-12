No.13 Long Pressed Name
=========
Your friend is typing his name into a keyboard.  Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.  
  
You examine the typed characters of the keyboard.  Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.   

## Problem requirements
  
First we need to define what is long pressed names. Consider a name is a string concatenated by many repeating substrings. Substrings are repeating withing themselves for at least once. For example, the name `saeed` consists of substrings `s`, `a`, `ee`, and `d`.  
  
A long pressed name is the name with same substring characters in the same order, but the repeating times may be larger or equal to the original one. For example, `saeeed` is a long pressed name of `saeed` because the substrings are still in the order `s`, `a`, `e` and `d`, but the substring `eee` is longer than the original `ee`. On the contrary, `saed` is not a long pressed name because it misses a character `e`.  

## How To (In C++)
### 1. Detecting substrings
Since we have the definition, we can just compare substrings of `name` and `typed` one by one. If in one comparison, the character does not match, or the length of the substring from `typed` is smaller, we return `false`.  
  
Here is the code:  
```C++
bool isLongPressedName(string name, string typed) {

	int i = 0, j = 0, c1=1, c2=1;
	char a,b;
	if (name == "" && typed == "") return true;

	while (i <= name.length() - 1 && j <= typed.length() - 1) {
		a = name[i], b = typed[j];
		while (i < name.length() - 1 && name[i] == name[i + 1]) {
			i++;
			c1++;
		}
		while (j < typed.length() - 1 && typed[j] == typed[j + 1]) {
			j++;
			c2++;
		}
		if (a != b || c2 < c1) return false;
		i++; j++;
		c1 = c2 = 1;
		
	}
	return (i == name.length() && j == typed.length()) ? true : false;

}
```  
The code can work, but still need to be improved. First, because each comparison needs to get info from substrings, we need to handle
boundary conditions such as empty strings, index at the tail. Second, there are two additional variables `c1` and `c2` storing length
information.   

### 2. Optimized code
Actually, the code does not need to stick on the "substring" concept. The problem can be viewd as an extension of "how to determine if
two names are the same".
  
Consider comparing two names. We just need 1 index `i` and see if `name[i]==typed[i]`. In a long pressed name problem, we need two indexes `i` and `j`. When `name[i]==typed[j]`, `i` and `j` both increase by 1. If `name[i]!=typed[j]`, this may be caused by substring mismatch or just long pressing. If it is because of long pressing, then `typed[j]` should be equal to `typed[j-1]`, and only `j` is increased to detect the next position. Both mistyping or missing characters will let `typed[j]==typed[j-1]` fail.  
  
Here is the code:  
```C++
    bool isLongPressedName(string name, string typed) 
    {
        int i = 0, j = 0;
        while(i < name.size() && j < typed.size())
        {
            if(name[i] == typed[j])
            {
                i++;
                j++; 
            }
            else if(typed[j] == typed[j-1])
                j++;
            else
                return false;            
        }
        return i == name.size();
        
    }
```
The last line `return i == name.size();` is to deal with boundary situation that `typed` misses the last few characters (like `saeed` and `saee`). Notice that how this method simplifies complex boundary conditions in the first method, so that the code is much more neat.  







