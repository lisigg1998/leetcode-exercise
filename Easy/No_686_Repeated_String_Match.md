No.686 Repeated String Match
=========
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:
```
Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
             Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
```
Example 2:
```
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.
```
Example 3:
```
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

## Problem Analysis  

This problem can be solved in multiple ways. But the most straightforward and simple solution is the peak-and-valley one.  

## How To (In C++ & Java)
### 1. Brute force
```Java
class Solution {
    public int maxProfit(int[] prices) {
        return calculate(prices, 0);
    }

    public int calculate(int prices[], int s) {
        if (s >= prices.length)
            return 0;
        int max = 0;
        for (int start = s; start < prices.length; start++) {
            int maxprofit = 0;
            for (int i = start + 1; i < prices.length; i++) {
                if (prices[start] < prices[i]) {
                    int profit = calculate(prices, i + 1) + prices[i] - prices[start];
                    if (profit > maxprofit)
                        maxprofit = profit;
                }
            }
            if (maxprofit > max)
                max = maxprofit;
        }
        return max;
    }
}
```
**Time complexity:**  
   
$O(n^n)$.  

**Space complexity:**  

$O(n)$.  

### 2. peak and valley
```C++
int maxProfit(vector<int>& prices) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    if(prices.empty() || prices.size() == 1) return 0;
    int sum=0;
    for(int i = 0; i < prices.size()-1; i++){
        sum += max((prices[i+1] - prices[i]),0);
    }
    return sum;
}
```
**Time complexity:**  
   
$O(n)$.  

**Space complexity:**  

$O(1)$.  
