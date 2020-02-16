Bitonic search Problem
=========
This problem is from problem 1.4.20, Algorithm(4th edition).  
  
An array is bitonic if it is comprised of an increasing sequence of integers followed immediately by a decreasing sequence of integers.
Write a program that, given a bitonic array of `N` distinct int values, determines whether a given integer is in the array. 
Your program should use `~3lg N` compares in the worst case.

## Problem Analysis  

The book gives us a hint that the time complexity can reach $O(logn)$. **Normally time complexity with logn indicates that the problem can be solved by divide and conquer method.** In problem 1.4.18 of the same book, there is an algorithm which can find local minimum/maximum in `~2lg N` time. Can this algorithm help us solve bitonic search question?  
  
The answer is yes. Actually, we can think like this:  
1. Find the local maximum, which is also the global maximum of the bitonic array. This takes `~2lg N` time.  
2. The maximum is the limit dividing ascending and descending parts of the bitonic array. Compare the `key` with `nums[0]`(the first
element of the array), we can decide to use binary search on the ascending side or the descending side. This takes `~lg N` time.  
  
In total, the time complexity adds up to `~3lg N`.  

## How to (In C++)
### 1. Use local maximum algorithm
```C++
// return the index if key is in the array, and return -1 if key is not in the array.
// up_down == 1: increasing array, up_down == 0: decreasing array
int BinarySearch(vector<int>& nums, int key, int low, int high, bool up_down) {
	if (nums.size() == 0) return -1;
	if (nums.size() == 1) return nums[0] == key ? 0 : -1;
	int lo = low, hi = high;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (nums[mid] == key) return mid;
		// increasing array
		else if (up_down) {
			if (key < nums[mid]) hi = mid - 1;
			else lo = mid + 1;
		}
		// decreasing array
		else {
			if (key < nums[mid]) lo = mid + 1;
			else hi = mid - 1;
		}
	}
	return -1;
}

// return the index of local maximum
// caution: this local maximum finder can only deal with monotinic or bitonic arrays!!!
int localMax(vector<int>& nums) {
	// zero size vector
	if (nums.size() == 0) {
		return -1;
	}
	// size 1 or monotonic decreasing
	if (nums.size() == 1 || nums[0] > nums[1]) {
		return 0;
	}
	// monotinic increasing
	if (nums[nums.size() - 1] > nums[nums.size() - 2]) {
		return nums.size() - 1;
	}

	int lo = 1, hi = nums.size() - 2; // the first/last element must not be the maximum
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		// if find the peak, return
		if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) return mid;
		// if nums[mid] is not the peak, search on the side which is larger
		else {
			if (nums[mid - 1] > nums[mid + 1]) hi = mid - 1;
			else lo = mid + 1;
		}
	}
	return -1;
}

// bitonic search 1: find local maximum first, then use binary search on either side, determined by 
// which is larger, key or nums[0]?
int bitonicSearch(vector<int>& nums, int key) {
	if (nums.size() < 3) {
		cout << "Not a bitonic array!" << endl;
		return -1;
	}
	// find the maximum, which is the "border line" of the bitonic array
	int max_index = localMax(nums);

	// key is larger than the maximum, not found
	if (key > nums[max_index]) return -1;
	// key is larger than the minimum of ascending part, search the ascending part
	else if (key > nums[0]) 
	{
		return BinarySearch(nums, key, 0, max_index, 1);
	}
	// key is smaller than the minimum of ascending part, search the descending part
	else
	{
		return BinarySearch(nums, key, max_index, nums.size()-1, 0);
	}
}
```
**Time complexity:**  
  
$O(logn)$, it takes only `~3logn` times of comparison operations.  
  
**Space complexity:**
  
$O(1)$.

### 2. Another divide and conquer
Notice that **if we divide the bitonic array from the middle, there must be one side monotinic and the other side bitonic**. With this 
property we can design another divide and conquer method:  
1. Divide the whole array into two parts. There must be one monotonic part.  
2. If the left part is monotinic, then it's the ascending part. If key is less than `nums[mid]`, we use binary search on the left 
part. If the key is not in the left part, we apply the method recursively on the right part.  
3. If the right part is monotinic, then it's the descending part. If key is less than `nums[mid]`, we use binary search on the right 
part. If the key is not in the right part, we apply the method recursively on the left part.  
  
To conclude, we apply normal binary search to the monotonic part, and apply the bitonic search recursively on the bitonic part. Although it can be non-recursive (just like binary search can be implemented with just loop), the main idea remains the same.  

```C++
int bitonicSearch(vector<int>& nums, int key) {
	if (nums.size() < 3) {
		cout << "Not a bitonic array!" << endl;
		return -1;
	}
	int lo = 0, hi = nums.size() - 1;

	while (hi - lo >= 2) {
		int mid = (lo + hi) / 2;

		// if find the key, return
		if (nums[mid] == key) return mid;
		// if left monotinic, right bitonic:
		if (nums[mid] > nums[mid - 1]) {
			// if key less than nums[mid], it can be on the left; if not found, search right side
			if (nums[mid] > key) {
				int index = BinarySearch(nums, key, lo, mid, 1);
				if (index != -1) return index;
			}
			lo = mid + 1;
		}
		// if right monotinic, left bitonic:
		if (nums[mid] < nums[mid - 1]) {
			// if key less than nums[mid], it can be on the right; if not found, search left side
			if (nums[mid] > key) {
				int index = BinarySearch(nums, key, mid, hi, 0);
				if (index != -1) return index;
			}
			hi = mid - 1;
		}
	}
	// boundary situation: when the sub-array size less than 3
	if (hi - lo <= 1) {
		if (nums[hi] == key) return hi;
		if (nums[lo] == key) return lo;
	}
	return -1;
}
```

**Time complexity:**  
  
$O(logn^2)$, it takes only `~logn` times of comparison operations.  
  
**Space complexity:**
  
$O(1)$.



