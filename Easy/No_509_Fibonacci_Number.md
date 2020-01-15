No.509 Fibonacci Number
=========
return the Nth Fibonacci number, assuming `fib(0) = 0`, `fib(1) = 1`.

## Problem Analysis  

Multiple ways can solve this problem given the math features Fibonacci sequence have. Here I only list some normal methods.  

## How To (In C++)
### 1. Simple Recursion
```C++
int fib(int N) {
    if(N==0) return 0;
    if(N==1) return 1;
    return fib(N-1) + fib(N-2);
}
```
This method just use the definition of Fibonacci numbers.  
  
**Time complexity:**  
$O(2^n)$. Each time you call `fib(n)` you need to recursively call `fib(n-1)` and `fib(n-2)`, and they need to recursively call `fib()`. The program will generate $2^n$ stacks.  
  
**Space complexity:**  
$O(n)$. There will be at maximum n function stacks, and this may cause stack overflow.  
  
### 2. Memoization
```C++
int fib(int n){
    if(n<=1) return n;
    int* cache = new int[n+1];
    for(int i = 0; i < n+1; i++) cache[i] = -1;
    cache[0]=0;cache[1]=1;
    return memoize(n, cache);
}
int memoize(int n, int* cache){
    if(cache[n] != -1) return cache[n];
    cache[n] = memoize(n-1, cache) + memoize(n-2, cache);
    return memoize(n, cache);
}
```
Notice that in the  recursion method, we are repeatingly counting some results, like `fib(n-1)` also need to count `fib(n-2)`, but `fib(n)` explicitly counts `fib(n-2)` again. If we can memoize previous results in an array, we does not need to generate that much times of recursion.  
  
**Time complexity:**  
$O(n)$, because in this case we only generate n times of recursion.
  
**Space complexity:**  
$O(n)$, because the number of function stacks is still n.  
### 3. no recursion method
Using only loop, we can calculate `fib(n)` from bottom to top:
```C++
int fib(int N) {
    if(N==0) return 0;
    if(N==1) return 1;
    int res, n1=1, n2=0;
    for(int i = 2; i <= N; i++){
        res = n1+n2;
        n2=n1;
        n1=res;
    }
    return res;
    }
 ```
 **Time complexity:**  
$O(n)$.
  
**Space complexity:**  
$O(1)$.

### 4. math methods
Use the math formula to directly calculate `fib(n)`, or use a matrix exponential method. see this [link](https://leetcode.com/problems/fibonacci-number/solution/).  

