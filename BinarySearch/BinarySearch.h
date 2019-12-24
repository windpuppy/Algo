#pragma once

#include <iostream>
#include <vector>

using namespace std;


class BinarySearch
{
public:
  // O(logn), O(1)
  int binarySearch(vector<int> array, int target) {
    int size = array.size();
    if (size == 0) return -1;

    int left = 0;
    int right = size - 1;
    while (left <= right) {
      auto mid = left + (right - left) / 2;
      auto val = array[mid];

      if (target == val) return mid;
      else if (target < val) right = mid - 1;
      else left = mid + 1;
    }
    return -1;
  }

  // O(logmn), O(1)
  vector<int> binarySearchSortedMatrix(vector<vector<int>> matrix, int target) {
    vector<int> invalid{ -1, -1 };
    if (matrix.empty() || matrix[0].empty()) return invalid;

    int rows = matrix.size();
    int cols = matrix[0].size();

    int left = 0;
    int right = rows * cols - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      int i = mid / cols;
      int j = mid % cols;
      int val = matrix[i][j];
      if (target == val) return vector<int>{i, j};
      else if (target < val) right = mid - 1;
      else left = mid + 1;
    }

    return invalid;
  }

  // Notes:
  // 1) exit condition: left > right - 1. we need to leave minimum 2 elements here
  // 2) right = mid, left = mid, do not do mid+1 / mid-1 because we do not want to miss out the zero Xs.
  // O(n), O(1)
  int findClosest(vector<int> array, int target) {
    if (array.empty()) return -1;

    int left = 0;
    int right = array.size();

    // leave minimum 2 elements here
    while (left < right - 1) {
      int mid = left + (right - left) / 2;
      int val = array[mid];
      if (target == val) return mid;
      else if (target < val) right = mid; // cannot do +1 here, in case we miss out the zero crossing
      else left = mid; // same reason
    }

    int distLeft = abs(array[left] - target);
    int distRight = abs(array[right] - target);
    return distLeft > distRight ? right : left;
  }

  // Find first occurrence
  // So, if (target <= val) right = mid;
  // If last occurrence
  // It's if (target >= val) left = mid;
  int firstOccurrence(vector<int> array, int target) {
    if (array.empty()) return -1;

    int left = 0;
    int right = array.size() - 1;

    // leave minimum 2 elements here
    while (left < right - 1) {
      int mid = left + (right - left) / 2;
      int val = array[mid];
      if (target <= val) right = mid; // use <= here! because we need the first occurrence!
      else left = mid; // same reason
    }

    // only two elements left
    if (array[left] == target) return left;
    else if (array[right] == target) return right;
    else return -1;
  }

  // Find last occurrence
  // So, if (target >= val) left = mid;
  // If first occurrence
  // It's if (target <= val) right = mid;
  int lastOccurrence(vector<int> array, int target) {
    if (array.empty()) return -1;

    int left = 0;
    int right = array.size() - 1;

    // leave minimum 2 elements here
    while (left < right - 1) {
      int mid = left + (right - left) / 2;
      int val = array[mid];

      // Check left first!
      if (target >= val) left = mid; // use >= here! because we want the last occurrences (ie. we can afford to skip the left ones)
      else right = mid; // same reason
    }

    // only two elements left
    if (array[right] == target) return right;
    else if (array[left] == target) return left;
    else return -1;
  }

  // Notes:
  // 1) find the largest "less equal" target, or if the target itself it doesn't matter first/last occurrence
  // 2) start from the seed, go both directions with two pointers
  //
  // 1) O(logn)
  // 2) O(k)
  // Together: O(logn) + O(k)
  // If k very very large ==? O(logn) + O(n), so it's O(n)
  vector<int> kClosest(vector<int> arr, int target, int k) {
    vector<int> res;
    int size = arr.size();
    if (size == 0 || k == 0) return res;

    // left (smallest less equal) and right should be the closest pair!
    // starting from mid (including mid), go both directions
    int left = largestLessEqual(arr, target);
    int right = left + 1;

    for (int i = 0; i < k; ++i) {
      // push left pointer when:
      // 1) right is out of bound
      // 2) both in, and left is closer to target than right
      if (right >= size ||
        (left >= 0 && target - arr[left] <= arr[right] - target)) {
        res.push_back(arr[left--]);
      }
      // or we push right pointer
      else {
        res.push_back(arr[right++]);
      }
    }
    return res;
  }

  int largestLessEqual(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left < right - 1) {
      int mid = left + (right - left) / 2;
      if (arr[mid] <= target) left = mid;
      else right = mid;
    }

    if (arr[right] <= target) return right;
    if (arr[left] <= target) return left;
    return -1; // not found (i.e. all are larger than target)
  }



  // Note
  // Because we are looking for "smallest larger than", we need to do
  //    if (midVal <= target) left = mid + 1;
  // to skip the equal values
  // Then we end up a pair of left and right
  //     just check if only right, or both > target
  // Time: O(logn), space: O(1)
  int smallestElementLargerThanTarget(vector<int> array, int target) {
    if (array.empty()) return -1;

    int left = 0;
    int right = array.size() - 1;

    // need 2 elements left
    while (left < right - 1) {
      int mid = left + (right - left) / 2;

      if (array[mid] <= target) left = mid + 1; // we are looking for smallest LARGER than, so we need to throw away the equal values here
      else right = mid;
    }

    if (array[left] > target) return left; // left qualifies
    else if (array[right] > target) return right; // both qualify

    return -1;
  }



  // Search in shifted sorted array
  // Shifted: [3,4,5,1,2], no dups, target might not exist in the array
  // Time: O(logN)
  // Space: O(1)
  int searchInShiftedSortedArray(vector<int> nums, int target) {
    if (nums.empty()) return -1;
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int midVal = nums[mid], leftVal = nums[left], rightVal = nums[right];
      if (target == midVal)
        return mid;

      // (Left) shift happened, real mid is in the left section
      if (midVal > rightVal)
        if (target < midVal && target >= leftVal)
          right = mid - 1;
        else
          left = mid + 1;

      // (Right shift) happened, real mid is in the right section
      else if (midVal < leftVal)
        if (target > midVal&& target <= rightVal)
          left = mid + 1;
        else
          right = mid - 1;

      // No shift
      else
        if (target > midVal)
          left = mid + 1;
        else
          right = mid - 1;
    }
    return -1;
  }



  // Search in shifted sorted array
  // Shifted: [3,4,5,1,2], with dups, target might not exist in the array
  // Time: O(logN)
  // Space: O(1)
  int searchInShiftedSortedArray2(vector<int> nums, int target) {
    if (nums.empty()) return -1;
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      // dedup
      while (left < right && nums[left] == nums[left + 1]) left++;
      while (left < right && nums[right] == nums[right - 1]) right--;

      int mid = left + (right - left) / 2;
      int midVal = nums[mid], leftVal = nums[left], rightVal = nums[right];
      if (target == midVal)
        return mid;

      // (Left) shift happened, real mid is in the left section
      if (midVal > rightVal)
        if (target < midVal && target >= leftVal)
          right = mid - 1;
        else
          left = mid + 1;

      // (Right shift) happened, real mid is in the right section
      else if (midVal < leftVal)
        if (target > midVal&& target <= rightVal)
          left = mid + 1;
        else
          right = mid - 1;

      // No shift
      else
        if (target > midVal)
          left = mid + 1;
        else
          right = mid - 1;
    }
    return -1;
  }



private:
  

};
