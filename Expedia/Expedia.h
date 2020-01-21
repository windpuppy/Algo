#pragma once

#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <algorithm> // min_element, max_element
#include <numeric> // accummulate

using namespace std;

class Expedia {
public:
  
  // Choose a positive divisor, divide an array of positive integers by it, and sum the result of the division
  // Find the smallest divisor such that the above result is <= to the given threshold
  // Note:
  //   all divisions are rounded up: 7/3 = 3
  //   1 <= nums[i] <= 10^6
  // For example: [1, 2, 5, 9], threshold = 6
  //   divisor 4: 1 + 1 + 2 + 3 = 7
  //   divisor 5: 1 + 1 + 1 + 2 = 5, so the result is 5.
  // Time: O(nlog(10^6)), 10^6 is a constant, so O(n)
  int smallestDivisor(vector<int> nums, int threshold) {
    int left = 1, right = 1e6;
    while (left < right) {
      int mid = left + (right - left) / 2;
      int sum = getSum(nums, mid);
      
      if (sum > threshold) // divisor too small
        left = mid + 1;
      else // divisor too large
        right = mid; // IMPORTANT: don't throw away mid yet, it can be a valid solution!
    }
    return left;
  }

  int getSum(const vector<int>& nums, int divisor) {
    int sum = 0;
    for (int n : nums)
      sum += (int)ceil((double)n / divisor);
    return sum;
  }

  // A small improvement by starting the right bound at max element
  // Time: O(n + nlog(max_num))
  //   because std::max_element is O(n)
  int smallestDivisor2(vector<int> nums, int threshold) {
    int left = 1, right = *std::max_element(nums.begin(), nums.end());
    while (left < right) {
      int mid = left + (right - left) / 2;
      int sum = getSum(nums, mid);

      if (sum > threshold) // divisor too small
        left = mid + 1;
      else // divisor too large
        right = mid; // IMPORTANT: don't throw away mid yet, it can be a valid solution!
    }
    return left;
  }



  // String compression
  // compress abbccc -> ab2c3, instead of a1b2c3
  // This is an easy one, because the ouput string won't be longer than the input
  // Time: O(n)
  string compress(string input) {
    const int length = input.size();
    if (length <= 1) return input;
    int slow = 0, fast = 0, newLength = 0;

    while (fast < length) {
      // pinpoint first char in each while loop
      int first = fast++;
      while (fast < length && input[fast] == input[first])
        fast++;

      // copy first char
      input[slow++] = input[first];

      // repeating chars?
      int count = 0;
      if (fast - first > 1) {
        count = copyDigits(input, slow, fast - first);
        slow += count; // slow moves num digits (it can be a1, or it can be a12 if there are 12 'a's)
      }
      newLength += 1 + count; // char itself + num digits
    }

    input.resize(newLength);
    return input;
  }

  // copy n in the form of char(s) to index position of input string
  int copyDigits(string& input, int index, int n) {
    if (!n) return 0;
    auto str = to_string(n);
    for (auto c : str)
      input[index++] = c;
    return (int)str.size();
  }



  // Find the pivot index of an array and return that index (not value!)
  // Definition of pivot index: sum of its left == sum of its right.
  // For multiple pivot indexes, return the left-most one; if none exists, return -1.
  // Time O(n), Space O(1)
  int findPivotIndex(vector<int>& nums) {
    const int size = nums.size();
    if (size == 0) return -1; // no pivot
    if (size == 1) return 0;  // lone element itself is a pivot
    int total = accumulate(nums.begin(), nums.end(), 0);
    int prefixSum = 0;
    for (int i = 0; i < size; ++i) {
      if (prefixSum * 2 + nums[i] == total)
        return i;
      prefixSum += nums[i];
    }
    return -1;
  }



  // An array of gas stations forming a CIRCLE, gas[i] is the gas amount, cost[i] is the cost from station i to i + 1.
  // Find the clockwise route and return the starting station index
  // Note: there is only one possible such route, or there is no such route in which case we return -1
  // Observation:
  //   instead of O(n^2) to try all route, we use one pass O(n)
  //   for each station, we use a variable "carry" to indicate the amount of gas to carry to the next station
  //   we also track the minimum carry amount and that gives us the starting station of the route, reason? There won't be
  //      a smaller carry amount the rest of the route
  // Time O(n), Space O(1)
  int gasStation(vector<int>& gas, vector<int>& cost) {
    gas.push_back(gas.front()); cost.push_back(cost.front()); // Small trick: pad 1st gas & cost to end to make it circular
    const int n = gas.size();
    int carry = 0, minCarry = INT_MAX, index = 0;
    for (int i = 1; i < n; ++i) {
      carry += gas[i - 1] - cost[i - 1]; // Note: this can be negative, but it's okay.
      if (carry < minCarry) {
        minCarry = carry;
        index = i;
      }
    }
    if (carry < 0) return -1; // total gas < total cost, no solution
    return index % (n - 1);
  }



  // Given a list of daily temperatures, return a list of "how many days until a warmer temperature"
  // e.g. given: [73, 74, 75, 71, 69, 72, 76, 73]
  //      return:[1,  1,  4,  2,  1,  1,  0,  0]
  // This is essentially the Next Greater problem.
  // Observation:
  //   Next Greater means for each element we only look towards the right, and we only care about the CLOSEST of such elements.
  //   Therefore we can scan from right to left, and we throw away the further greater elements. Use Stack!
  // Approach:
  //   Scan from right to left, use a stack to save the "next greater" elements
  //   For each element "curr", we compare curr vs stack top
  //     1. if curr > stack top ? keep popping smaller elements from the stack, then push curr back
  //     2. then the "next greater" is stack top, or 0 if stack is empty
  // Time O(n), Space O(n)
  vector<int> dailyTemperatures(vector<int>& temps) {
    stack<pair<int, int>> s; // <value, index>
    const int n = temps.size();
    vector<int> res(n, -1);
    for (int i = n - 1; i >= 0; --i) {
      int curr = temps[i];
      while (!s.empty() && s.top().first <= curr) // pop stack top if it's smaller than curr
        s.pop();
      if (!s.empty())
        res[i] = s.top().second - i;
      s.push({ curr, i });
    }
    return res;
  }



  // Frequency Sort: given a string, sort the chars by frequency in decreasing order
  // For tie breakers, return any valid answers
  // "tree" -> "eert" or "eetr"
  // "Aabb" -> "bbAa"
  // Time O(n), which is better than O(nlogn)
  string frequencySort(string s) {
    const int size = s.size();
    if (size <= 1) return s;
    unordered_map<char, int> freq;
    vector<string> bucket(size + 1, ""); // 0 slot is never used because it indicates 0 freq, but still allocate size + 1 for convenience
    string res;

    for (char c : s) //count frequency of each character
      freq[c]++;
    
    for (auto& f : freq) { //put character into frequency bucket
      int count = f.second;
      char c = f.first;
      bucket[count].append(count, c);
    }
    
    for (int i = size; i > 0; i--) // decreasing freq
      if (!bucket[i].empty())
        res.append(bucket[i]);

    return res;
  }
};
