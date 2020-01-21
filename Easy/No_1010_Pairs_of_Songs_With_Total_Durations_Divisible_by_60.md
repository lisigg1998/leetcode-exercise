No.1010 Pairs of Songs With Total Durations Divisible by 60
=========
In a list of songs, the i-th song has a duration of time[i] seconds. 

Return the number of pairs of songs for which their total duration in seconds is divisible by 60.  Formally, we want the number of indices i < j with (time[i] + time[j]) % 60 == 0.

 

Example 1:
```
Input: [30,20,150,100,40]
Output: 3
Explanation: Three pairs have a total duration divisible by 60:
(time[0] = 30, time[2] = 150): total duration 180
(time[1] = 20, time[3] = 100): total duration 120
(time[1] = 20, time[4] = 40): total duration 60
```
Example 2:
```
Input: [60,60,60]
Output: 3
Explanation: All three pairs have a total duration of 120, which is divisible by 60.
 ```

Note:

1.`1 <= time.length <= 60000`  
2.`1 <= time[i] <= 500`

## Problem Analysis  

If use brute force, the time complexity will be $O(n^2)$, which is not good. We need to find a $O(n)$ time solution, and this can be done by using a counting array.  
  

## How To (In C++)
### 1. counting array
Because we know that `(time[i]+time[j]) % 60 == 0` is equal to `time[i]%60 + time[j]%60 == 0 or 60`, we can preprocess each `time[i]` with modular arithmetic. Then, we create a counting array of size n and count the amount of numbers from 0 to 59. Except for 0 and 30, `counting_arr[i] * counting_arr[60-i]` will be the number of pairs that `i` and `60-i` can form. 0 and 30 are counted by special way.  
```C++
int numPairsDivisibleBy60(vector<int>& time) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int count = 0;
    vector<int> arr(60,0);
    for(int i = 0; i < time.size(); i++) {
        arr[time[i] % 60]++;
    }
    for(int i = 0; i < 31; i++){
        if(i == 0 || i == 30){
            count += (arr[i] * (arr[i]-1)) / 2;
        }
        else{
            count += arr[i]*arr[60-i];
        }
    }
    return count;
}
```

The code can be more simple. We can count the result when we are building the counting array. When we add a count to position `i`, it can form new `counting_arr[(60-i)%60]` pairs with those counted in `counting_arr[(60-i)%60]`. When all elements belong to position `i` and `(60-i)%60` are added, the number of pairs is precisely counted. So we have the code like this:  
```C++
int numPairsDivisibleBy60(vector<int>& time) {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        vector<int> c(60);
        int res = 0;
        for (int t : time) {
            res += c[(60 - t%60) % 60];
            c[t % 60] += 1;
        }
        return res;
    }
```

**Time complexity:**  
$O(n)$.  
  
**Space complexity:**  
$O(n)$.  


