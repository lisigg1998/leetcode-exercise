No.53 Maximum Subarray
=========
Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.  
## Problem requirements
  
This is a classic question, which can be solved both by dp or divide-and-conquer.  

## How To (In C++)
### 1. Divide and conquer
```C++
int aux(vector<int>& nums, int low, int mid, int high) {
	if (high - low == 0) return nums[low];
	if (high - low == 1) return max(max(nums[high], nums[low]), nums[high] + nums[low]);
	// recursively solve the left and right situations
	int left_situation = aux(nums, low, (mid+low) / 2, mid);
	int right_situation = aux(nums, mid+1, (high + mid) / 2, high);
	// solve the crossing situation
	int left_sum = INT_MIN, right_sum = INT_MIN, temp=0;
	for (int i = mid; i >= low; i--) {
		temp += nums[i];
		if (temp > left_sum) left_sum = temp;
	}
	
	temp = 0;
	for (int i = mid + 1; i <= high; i++) {
		temp += nums[i];
		if (temp > right_sum) right_sum = temp;
	}
	return max(max(left_situation, right_situation),left_sum+right_sum);
}

int maxSubArray(vector<int>& nums) {
	return aux(nums, 0, (nums.size() - 1) / 2, nums.size() - 1);
}
```
The original problem can be divided to 3 subproblems:  
1. Max subarray is on the left side of `mid`;  
2. Max subarray is on the right side of `mid`;  
3. Max subarray is across the `mid`.  
  
The first two can be solved by recursion. The third is solved like this. The max array across the `mid` consists of two subarrays attaching to the `mid`,and extending to the left and to the right. All we need to do is try out every elements to find the left and right limits.  
**Time complexity:**  
Assume this algorithm takes $T(n)$ time for array of size n. The two recursive part takes $T(n/2)$ time and the third part takes $O(n)$ time since it needs to examine every elements. The recursive definition is $T(n)\=2T(n/2)+O(n)$. The final solution is $O(nlogn)$.  

### 2. Dynamic programming  
```C++
int maxSubArray(vector<int>& nums) {
	int length = nums.size(), maximum=nums[0], dp = nums[0];
	for (int i = 1; i < length; i++) {
		dp = max(nums[i] + dp, nums[i]);
		maximum = max(maximum, dp);
	}
	return maximum;
}
```
This problem is an optimization problem, and normally when we see such kind of problem we think of dp.  
#### Subproblem structure
The original problem can be divided into n subproblems: find the maximum subarray in all maximum subarrays ending with `nums[i]`. Subarrays ending with `nums[i]` covers all situations because one subarray only has one ending. Thus the optimization of the original problem contains the optimization of subproblems.
### Recursive definition
Suppose max length of subarray ending with `nums[i]` is stored in `dp[i]`, where `dp` is another array. `dp[i]` depends on `dp[i-1]`, because `dp[i]` is either `nums[i]` or `nums[i] + dp[i-1]`. Then we have the recursive definition: $dp\[i\]\=max(nums\[i\] + dp\[i-1\], nums\[i\])$.  
Further more, since we don't need to reconstruct the whole process, and `dp[0:i-2]` will never be used again, so we even do not need to use an array to store the previous stages.  
**Time Complexity:**  
The time complexity is $O(n)$.

