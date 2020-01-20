#pragma once

#include <vector>
#include <string>
#include <algorithm>

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

};
