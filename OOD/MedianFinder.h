#pragma once
#include <queue>

using namespace std;

// Implementation ideas:
// We use two PQ: min heap and max heap which gives me O(1) access to the two middle values
// C++ PQ is max heap, to avoid writing an overload operator for min heap, we push negative values into max heap
// We use long instead of int to avoid the -2^31 problem
class MedianFinder {
  priority_queue<long> min, max;

public:
  // make sure min always has one more (or equal) than max
  void addNum(int num) {
    long n = (long)num;
    min.push(n);
    max.push(-min.top());
    min.pop();
    if (min.size() < max.size()) {
      min.push(-max.top());
      max.pop();
    }
  }

  double findMedian() {
    if (min.size() > max.size())
      return (double)min.top();
    else
      return (min.top() - max.top()) / 2.0;
  }
};



// Optimize: if all of the numbers are between 0-100, how to optimize it?
// Solution: use a bucket
class MedianFinder2 {
  vector<int> nums;
  int size;

public:
  void MeidanFinder2() { nums.resize(101); }

  void addNum(int num) {
    nums[num]++;
    size++;
  }

  double findMedian() {
    int count = 0;
    int i = 0;
    while (count < size / 2)
      count += nums[i++];
    int j = i;
    while (count < size / 2 + 1)
      count += nums[j++];
  }
};