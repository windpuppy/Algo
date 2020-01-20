#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <thread>
#include <iostream>
#include <chrono>
#include <future>
#include <thread>
#include <Windows.h>

using namespace std;

class Sorting {
public:
  // Time O(n^2)
  // Space O(1)
  //
  // Time analaysis:
  // outer loop: n
  // inner loop: n-1, n-2, n-3, ..., 1
  // 1 + 2 + 3 + ... + n = n(n+1)/2 = n^2
  vector<int> selectionSort(vector<int> nums)
  {
    int size = nums.size();
    if (size <= 1) return nums;

    for (int i = 0; i < size - 1; ++i) {
      int minIndex = i;

      for (int j = i; j < size; ++j)
        if (nums[j] < nums[minIndex])
          minIndex = j;

      if (minIndex != i)
        swap(nums[i], nums[minIndex]);
    }

    return nums;
  }

  //                3157986420
  //       31579               86420       O(1) time, O(n) if LL
  //   315      79         864       20    O(2) time, O(n) if LL
  //  31  5    7 9        8 6  4     2 0   O(4) time, O(n) if LL
  // 3  1  5   7 9        8 6  4     2 0   O(8) time, O(n) if LL
  // Time spent above: 1 + 2 + 4 + ... + n/2 = O(n)
  // Time above: O(n) / O(nlogn), LL faster
  //===========================================================
  // Time below: O(nlogn) / O(nlogn), same
  // In total: O(nlogn) for both
  //
  // Space complexity:
  // Both users O(logn) for call stack, but the array version uses O(n) extra for merge
  // n dominates logn
  // Conclusion: O(n) for array, O(logn) for LL
  vector<int> mergeSort(const vector<int>& array) {
    if (array.size() == 0 || array.size() == 1) return array;
    return mergeSort(array, 0, array.size() - 1);
  }

  vector<int> mergeSort(const vector<int>& array, int left, int right) {
    if (left == right) return vector<int>{array[left]};
    int mid = left + (right - left) / 2;

    auto a = mergeSort(array, left, mid);
    auto b = mergeSort(array, mid + 1, right);
    return merge(a, b);
  }

  vector<int> merge(const vector<int>& left, const vector<int>& right) {
    vector<int> res(left.size() + right.size());

    int i = 0, j = 0, k = 0;

    while (k != res.size()) {
      int val;

      if (i >= left.size()) val = right[j++];
      else if (j >= right.size()) val = left[i++];
      else if (left[i] < right[j]) val = left[i++];
      else val = right[j++];

      res[k++] = val;
    }

    return res;
  }



  // Worse case: pivot gets "unlucky"
  // n + (n-1) + (n-2) + ... = n^2
  //
  // Time complexity
  // O(n^2) worst
  // O(nlogn) average
  vector<int> quickSort(vector<int> array) {
    if (array.size() <= 1) return array;
    quickSort(array, 0, array.size() - 1);
    return array;
  }

  void quickSort(vector<int>& array, int left, int right) {
    // Break condition
    if (left >= right) return;

    // Partition
    int p = partition(array, left, right);

    // Recurse (do NOT include pivot)
    quickSort(array, left, p - 1);
    quickSort(array, p + 1, right);
  }

  // Partion array: pick a pivot, move smaller values to its left, and bigger values to its right
  int partition(vector<int>& array, int left, int right) {
    int pIndex = (left + right) / 2;
    int pVal = array[pIndex];

    // First, swap pivot to the right most
    swap(array[pIndex], array[right]);

    // Create and move two bounds
    int lb = left;
    int rb = right;
    while (lb <= rb) { // less equal, to cover all elements
      if (array[lb] < pVal) // push left
        lb++;
      else if (array[rb] >= pVal) // push right
        rb--;
      else
        swap(array[lb++], array[rb--]); // small trick: if we reach here, rb is already < pivot, so we can do lb++ after the swap to skip it!
    }

    // Move pivot back to the left bound position
    swap(array[lb], array[right]);

    // Return left bound
    return lb;
  }



  // Move all zeros to the right
  // Time O(n), Space O(1)
  vector<int> moveZero(vector<int> nums) {
    const int size = nums.size();
    if (size <= 1) return nums;
    int left = 0, right = size - 1;
    while (left <= right) {
      if (nums[left] != 0) // non-zero on left: push lb
        left++;
      else  if (nums[right] == 0) // zero on right: push rb
        right--;
      else // zero on left
        swap(nums[left++], nums[right--]);
    }
    return nums;
  }

  // A more elegant way than the above
  vector<int> moveZero2(vector<int> nums) {
    const int size = nums.size();
    if (size <= 1) return nums;
    int left = 0, right = size - 1;
    while (left <= right) {
      if (nums[left] != 0) // non-zero on left: push lb
        left++;
      else
        swap(nums[left], nums[right--]);
    }
    return nums;
  }

  // Above two methods are not stable, this is a stable version
  vector<int> moveZeroes_stable(vector<int> nums) {
    const int size = nums.size();
    if (size <= 1) return nums;
    int s = 0, f = 0;

    while (f < size) {
      if (nums[f] != 0)
        nums[s++] = nums[f];
      f++;
    }

    fill(nums.begin() + s, nums.end(), 0);
    return nums;
  }



  // Three colors: -1, 0, 1
  // Time O(n) - iterate through all elements once
  // space O(1)
  vector<int> rainbowSort(vector<int> nums) {
    if (nums.size() <= 1) return nums;

    // Three gates
    int g1 = 0;
    int g2 = 0;
    int g3 = nums.size() - 1;

    // Move g2 towards g3
    while (g2 <= g3) {
      int val = nums[g2];

      if (val == -1)
        swap(nums[g1++], nums[g2++]);
      else if (val == 0)
        g2++;
      else
        swap(nums[g2], nums[g3--]); // do NOT g2++ !!!
    }

    return nums;
  }



  // Four colors: 0, 1, 2, 3
  // 0000 1111 2222 xxxx 3333
  //      a    b    c  d
  // Time O(n) - iterate through all elements once
  // space O(1)
  vector<int> rainbowSort2(vector<int> nums) {
    if (nums.size() <= 1) return nums;

    // Four gates
    int a = 0;
    int b = 0;
    int c = 0;
    int d = nums.size() - 1;

    // Move g3 towards g4
    while (c <= d) {
      int val = nums[c];

      if (val == 0) {
        swap(nums[b], nums[c++]); // first, from unknown section to 1 section
        swap(nums[a++], nums[b++]); // then from 1 section to 0 section
      }
      else if (val == 1)
        swap(nums[b++], nums[c++]);
      else if (val == 2)
        c++;
      else
        swap(nums[c], nums[d--]);
    }

    return nums;
  }



  // Rainbow sort 3: sort k colors, 1~k
  // Solution: counting sort
  // Time: O(n)
  // Space: O(k)
  vector<int> rainbowSort3(vector<int> nums, int k) {
    vector<int> count(k + 1, 0);
    for (auto n : nums)
      count[n]++;

    int i = 0;
    for (int color = 1; color <= k; color++) {
      int c = count[color];
      while (c-- > 0)
        nums[i++] = color;
    }
    return nums;
  }



  // Time: O(n^2)
  vector<int> insertionSort(vector<int> input) {
    if (input.empty()) return input;

    for (int i = 1; i < input.size(); ++i) {
      int key = input[i];
      int j = i - 1;
      if (key >= input[j])
        continue;

      while (j >= 0 && key < input[j]) {
        input[j + 1] = input[j];
        j--;
      }
      input[j + 1] = key;
    }
    return input;
  }



  // Naive approach - SHUI XIAO YI SHUI
  // Time O(k), Space O(1)
  //
  // Binary search approach - divide and conquer
  // We can compare the k/2th element from a and b
  // If a[k/2] > b[k/2], then we can throw away the first K/2 elements from b because it's guaranteed that the kth smallest will not be within that range
  // e.g.
  // a: 1 3 5 7 
  // b: 2 4 6 8 10 12
  // k: 6, so k/2 = 3
  // a k/2th is 5, b k/2th is 6, b element is larger, so we can throw away the first 3 elements of a, see below
  // a: (1 3 5) | 7 
  // b:  2 4 6  | 8 10 12
  // No, the 6th smallest will not come from a(1 3 5)
  // Now a bigger problem becomes a smaller problem, and we continue
  // Time O(logk)
  int kthSmallestInTwoSortedArrays(vector<int> a, vector<int> b, int k) {
    int sizea = a.size();
    int sizeb = b.size();
    if (k < 1 || k > sizea + sizeb)
      return -1;

    if (a.empty())
      return b[k - 1];
    else if (b.empty())
      return a[k - 1];

    return kthSmallest_helper(a, 0, b, 0, k);
  }

  int kthSmallest_helper(vector<int> a, int low1, vector<int> b, int low2, int kmore) {
    int high1 = a.size() - 1;
    int high2 = b.size() - 1;

    if (low1 > high1) // a used up, answer is in b
      return b[low2 + kmore - 1];
    else if (low2 > high2) // b used up, answer is in a
      return a[low1 + kmore - 1];

    // is this neccessary? absolutely yes!
    if (kmore == 1)
      return min(a[low1], b[low2]);

    // Take k/2 numbers from a and b, compare their end points
    int i = min(low1 + kmore / 2 - 1, high1);
    int j = min(low2 + kmore / 2 - 1, high2);

    // If a[end] < b[end], throw away first part of a; otherwise throw away first part of b
    if (a[i] < b[j]) {
      kmore -= i - low1 + 1;
      return kthSmallest_helper(a, i + 1, b, low2, kmore);
    }
    else {
      kmore -= j - low2 + 1;
      return kthSmallest_helper(a, low1, b, j + 1, kmore);
    }
  }



  // Median of two sorted arrays
  // Naive solution: combine two arrays, find median - O(m+n)
  // A better solution that can do O(log(min(m,n)) ? Why not!!!
  //    x|xxx
  // yyyy|yy
  // If we can find such partition that the left size are equal to right size, and x1 <= y2 && y1 <= x2, then all my left elements <= than my right elementsthen
  // so the median will be
  // 1. if m + n is even number, avg(max(x1, y1), min(x2, y2)) is the median
  // 2. if m + n is odd number, max(x1, y1) is the median -- assuming we always put one extra element to the left
  //
  // Example:
  // a: 1 3 8 9 15
  // b: 7 11 18 19 21 25
  // Partition equation: partition X + partion Y = (m + n + 1)/2
  // We do binary search on array a, then assign b. We get below.
  //        1 3 | 8 9 15
  // 7 11 18 19 | 21 25
  // This means b has too many elements on the left side, that means for a, we need to keep pushing the partition boundary towards right (another binary search)
  //   1 3 8 | 9 15
  // 7 11 18 | 19 21 25
  // Not good! Push again.
  // 1 3 8 9 | 15
  //    7 11 | 18 19 21 25
  // Now the middle 4 elements meet our requirement, because m + n is odd size, median is max(9, 11) which is 11.
  // Time log(min(m, n))
  double medianOfTwoSortedArrays(const vector<int> a, const vector<int>b) {
    const int x = a.size();
    const int y = b.size();
    if (a > b)
      return medianOfTwoSortedArrays(b, a);

    int left = 0, right = x;
    while (left <= right) {
      int xLeft = (left + right) / 2;
      int yLeft = (x + y + 1) / 2 - xLeft;

      // Remember to handle special case where nothing is on the left side or nothing is on the right side
      int x1 = xLeft == 0 ? INT_MIN : a[xLeft - 1];
      int x2 = xLeft == x ? INT_MAX : a[xLeft];
      int y1 = yLeft == 0 ? INT_MIN : b[yLeft - 1];
      int y2 = yLeft == y ? INT_MAX : b[yLeft];

      if (x1 <= y2 && y1 <= x2)
        return (x + y) % 2 == 0 ? 0.5 * (max(x1, y1) + min(x2, y2)) : (double)max(x1, y1);
      else if (x1 > y2) // too many in left partition x
        right = xLeft - 1;
      else              // too few in left partition x
        left = xLeft + 1;
    }
    // If we reach here it means input is invalid ie. might not be sorted
    throw;
  }



  // Sort intervals by start time, O(nlogn)
  // Check intervals end time, O(n)
  // Total Time: O(nlogn)
  bool meetingRooms(vector<vector<int>> intervals) {
    sort(intervals.begin(), intervals.end());
    for (int i = 0; i < intervals.size() - 1; ++i)
      if (intervals[i].back() > intervals[i + 1].front())
        return false;
    return true;
  }

  // Sort intervals by start time, O(nlogn)
  // Group all non-conflicting intervals into a same "room", or otherwise open a new "room", O(n^2)
  // A more efficient solution is to use minHeap of meeting end time: top of the minHeap = earliest end time
  // for each interval, if start > heap top (end time), replace top; otherwise push end time
  int meetingRooms2(vector<vector<int>> intervals) {
    sort(intervals.begin(), intervals.end());
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (auto i : intervals) {
      int start = i.front();
      int end = i.back();

      if (!minHeap.empty() && start >= minHeap.top())
        minHeap.pop();

      minHeap.push(end);
    }
    return minHeap.size();
  }


  int meetingRooms2b(vector<vector<int>> intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> rooms;
    for (auto i : intervals) {
      int index = findRoom(rooms, i);
      if (rooms.empty() || index == -1)
        rooms.push_back(i);
      else
        rooms[index] = i; // replace room with the latest meeting
    }
    return rooms.size();
  }

  // helper function: find non-overlapping room
  int findRoom(vector<vector<int>> rooms, vector<int> interval) {
    for (int i = 0; i < rooms.size(); ++i)
      if (interval.front() >= rooms[i].back())
        return i;
    return -1;
  }



  // Sleep sort. Just for fun!
  static void wait(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
    cout << seconds << endl;
  }

  void sleepSort(vector<int>& nums) {
    vector<thread> threadList;
    for (auto n : nums)
      threadList.push_back(std::thread(wait, n));

    for_each(threadList.begin(), threadList.end(), mem_fn(&thread::join));
  }


};