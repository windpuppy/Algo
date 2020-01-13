#pragma once

#include "NestedInteger.h"

#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

class LinkedIn {

public:
  // Given a collection of intervals, merge all overlapping ones
  // Input : [[1,3], [2,6], [8,10], [15,18]]
  // Output : [[1,6], [8,10], [15,18]]
  // Method: sort all intervals by start times, then merge by end times
  // Time: O(n), Space: O(1)
  vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() <= 1) return intervals;
    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end());
    res.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); ++i) {
      auto& in = intervals[i];
      if (res.back()[1] < in[0])
        res.push_back(in);
      else
        res.back()[1] = max(res.back()[1], in[1]);
    }
    return res;
  }



  // Given a collection of intervals, insert a new interval into them (merge if needed).
  // Input intervals are non-overlapping, AND sorted by start times.
  // Input: intervals = [[1,2], [3,5], [6,7], [8,10], [12,16]], newInterval = [4,8]
  // Output:            [[1,2], [3,10],               [12,16]]
  // Explanation : Because the new interval[4, 8] overlaps with[3,5], [6,7], [8,10].
  // Implementation:
  // Go through all intervals
  //   1. if newInterval is to the right of intervals[i], push intervals[i]
  //   2. if newInterval is to the left or intervals[i], push newInterval, then push all the rest (and call it done)
  //   3. otherwise they must overlap - merge them
  // Time: O(n), Space: O(1)
  vector<vector<int>> insertInterval(vector<vector<int>>& intervals, vector<int>& newInterval) {
    const int size = intervals.size();
    vector<vector<int>> res;
    for (int i = 0; i < size; ++i) {
      auto& itv = intervals[i];
      if (newInterval[0] > itv[1]) // 1. right
        res.push_back(itv);
      else if (newInterval[1] < itv[0]) { // 2. left
        res.push_back(newInterval);
        for (int j = i; j < size; ++i) res.push_back(intervals[j]);
        return res;
      }
      else // 3. merge
        newInterval = { min(newInterval[0], itv[0]), max(newInterval[1], itv[1]) };
    }
    res.push_back(newInterval);
    return res;
  }

  // Above solution times out on LC, this is a faster implementation with iterator
  vector<vector<int>> insertInterval2(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    auto it = intervals.begin();
    for (auto it = intervals.begin(); it != intervals.end(); ++it) {
 
      if (newInterval[0] > (*it)[1]) // 1. right
        res.push_back(*it);
      else if (newInterval[1] < (*it)[0]) { // 2. left
        res.push_back(newInterval);
        while (it != intervals.end()) {
          res.push_back(*it);
          it++;
        }
        return res;
      }
      else // 3. merge
        newInterval = { min(newInterval[0], (*it)[0]), max(newInterval[1], (*it)[1]) };
    }
    res.push_back(newInterval);
    return res;
  }



  // Maximum Subarray
  // This is actually the exact same problem as "Longest subarray sum"
  // Time: O(n), Space: O(1) (optimized space)
  int maxSubarray(vector<int>& nums) {
    if (nums.empty()) return 0;
    int res = nums[0], maxSoFar = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      int contrib = max(maxSoFar, 0);
      maxSoFar = nums[i] + contrib;
      res = max(res, maxSoFar);
    }
    return res;
  }



  // Minimum length window that contains all chars in template t (chars can be in any order)
  // e.g. "adobecodebanc", "abc" ==> "banc" is the minimum window that contains "abc"
  // Use slow and fast pointers, we traverse all chars at most twice each
  // Time: O(n), Space: O(1) - the remain vector is fixed size 128
  string minWindowSubstring(string s, string t) {
    vector<int> remain(128, 0);
    for (auto c : t) remain[c]++; // remain chars to match in t
    int count = t.size(); // remain count of chars

    int slow = 0, fast = 0, minHead = 0, minLen = INT_MAX;

    while (fast < s.size()) {
      if (remain[s[fast++]]-- > 0) // explore fast
        count--;

      while (count == 0) { // we found a solution here!
        if (fast - slow < minLen) {
          minLen = fast - slow;
          minHead = slow;
        }

        if (remain[s[slow++]]++ == 0) // explore slow
          count++;
      }
    }
    return minLen == INT_MAX ? "" : s.substr(minHead, minLen);
  }



  // Shortest word distance
  // Given a list of words and two words (both in the list, and not equal to each other), return their minimum distance
  // Note: The list can contain dups
  // e.g. input is {"practice", "makes", "perfect", "coding", "makes"}, distance between "makes" and "coding" is 1, not 3!
  // Time: O(n), Space: O(1)
  int shortestWordDistance(vector<string>& words, string a, string b) {
    int i = -1, j = -1, dist = INT_MAX;
    for (int n = 0; n < words.size(); ++n) {
      string& w = words[n];

      if (w == a) i = n;
      else if (w == b) j = n;
      else continue; // small optimization

      if (i >= 0 && j >= 0)
        dist = min(dist, abs(i - j));
    }
    return dist;
  }



  // Shortest word distance 3
  // Follow up from Shortest word distance 1, what if a and b could be the same?
  // e.g. input is {"practice", "makes", "perfect", "coding", "makes"}, distance between "makes" and "makes" is 3, not 0!
  // Time: O(n)
  int shortestWordDistance3(vector<string>& words, string a, string b) {
    int i = -1, j = -1, dist = INT_MAX;
    for (int n = 0; n < words.size(); ++n) {
      string& w = words[n];

      if (a == b) { // SAME word
        if (w == a)
          if (i < j) i = n; // always move the further one between i and j, to make it "shortest"
          else j = n;
        else
          continue;
      }
      else { // NOT SAME word
        if (w == a) i = n;
        else if (w == b) j = n;
        else continue;
      }

      if (i >= 0 && j >= 0)
        dist = min(dist, abs(i - j));
    }
    return dist;
  }



  // Shortest word distance 2
  // Follow up for Shortest word distance 1, what if we need to repeatedly make such query many times? (assume the two target words are always different and both exist in the list)
  // Naive solution: pre-process all word distance and save them into a hashmap
  //    pre-process: O(n^2), query: O(1)
  // More realistic solution:
  //    pre-process: O(n), query: O(n)
  class WordDistance {
    unordered_map<string, vector<int>> map; // <word, {its indexes}>
  
  public:
    // O(n) pre-process
    WordDistance(vector<string>& words) {
      for (int i = 0; i < words.size(); ++i)
        map[words[i]].push_back(i);
    }

    // O(n) query
    int shortest(string a, string b) {
      int i = 0, j = 0, dist = INT_MAX;
      while (i < map[a].size() && j < map[b].size()) {
        int index_a = map[a][i], index_b = map[b][j];
        dist = min(dist, abs(index_a - index_b));
        index_a < index_b ? i++ : j++;
      }
      return dist;
    }
  };




  // Given a nested list of integers, return the weighted sum (weight is the depth of the integer)
  // e.g. [1,[4,[6]]] ==> 1 + 4*2 + 6*3 = 27
  int nestedListWeightSum(const vector<NestedInteger>& nestedList, int depth = 1) {
    int sum = 0;
    for (const auto& ni : nestedList) {
      sum += ni.isInteger()
        ? ni.getInteger() * depth
        : nestedListWeightSum(ni.getList(), depth + 1);
    }
    return sum;
  }

  
  
  // Follow up for the previous problem - now the weights are reversed
  // e.g. [1,[4,[6]]] ==> 1*3 + 4*2 + 6 = 17
  // Naive solution: run two passes. First pass to record depths for all elements, second pass to do the weighted sum.
  // Better (one pass) solution:
  //    Observation: for [a,[b,[c]]]
  //    weightSum = 1a + 2b + 3c
  //    reverseSum = 3a + 2b + 1c
  //    totalSum = 4a + 4b + 4c
  //    Therefore: reverseSum = totalSum - weightedSum
  //                          = (maxDepth + 1)*(a+b+c) - weightedSum
  int nesedListWeightSum2(const vector<NestedInteger>& nestedList) {
    int depth = 1, maxDepth = 1, singleSum = 0, weightedSum = 0;
    for (const auto& ni : nestedList)
      reverseSum(ni, depth, maxDepth, singleSum, weightedSum);
    return singleSum * (maxDepth + 1) - weightedSum;
  }

  void reverseSum(const NestedInteger& ni, int depth, int& maxDepth, int& singleSum, int& weightedSum) {
    maxDepth = max(maxDepth, depth);
    if (ni.isInteger()) {
      singleSum += ni.getInteger();
      weightedSum += ni.getInteger() * depth;
      return;
    }
    else {
      for (const auto& i : ni.getList())
        reverseSum(i, depth + 1, maxDepth, singleSum, weightedSum);
    }
  }



  // Given a row of houses, paint them with 3 colors so that no adjacent houses have the same color, return the minimum cost.
  // Cost matrix is given as follows:
  //  Cost    R   G   B
  // House 0  7   2   7
  // House 1  8   4   3
  // House 2  4   5   12
  // ...
  // DFS solution, Time O(2^n)
  int paintHouse_dfs(vector<vector<int>>& costs) {
    if (costs.empty()) return 0;
    return paint_dfs(costs, 0, -1, 0);
  }


  int paint_dfs(vector<vector<int>>& costs, int index, int prevColor, int sum) {
    if (index == costs.size()) return sum;

    int newSum = INT_MAX;
    for (int color = 0; color <= 2; color++) {
      if (color == prevColor) continue;
      newSum = min(newSum, costs[index][color] + paint_dfs(costs, index + 1, color, sum));
    }
    return newSum;
  }

  // DP solution
  // We create a n*3 matrix M, where M[i][j] = first i houses ending with color j
  // Induction rule: M[i][0] = min(M[i-1][1], M[i-1][2]) + costs[i][0]
  //                 M[i][1] = min(M[i-1][0], M[i-1][2]) + costs[i][1]
  //                 M[i][2] = min(M[i-1][0], M[i-1][1]) + costs[i][2]
  // Time O(n), Space O(n) - space can be further optimized to O(1) by overwriting the cost matrix
  int paintHouse(vector<vector<int>>& costs) {
    if (costs.empty()) return 0;
    const int n = costs.size();
    vector<vector<int>> M(n + 1, vector<int>(3, 0));
    for (int i = 1; i <= n; ++i) {
      M[i][0] = min(M[i - 1][1], M[i - 1][2]) + costs[i-1][0];
      M[i][1] = min(M[i - 1][0], M[i - 1][2]) + costs[i-1][1];
      M[i][2] = min(M[i - 1][0], M[i - 1][1]) + costs[i-1][2];
    }
    return min(M.back()[0], min(M.back()[1], M.back()[2]));
  }



  // Instead of 3 colors, we paint n houses with k colors
  // Time: O(n*m^2), Space: O(nm)
  int paintHouse2(vector<vector<int>>& costs) {
    if (costs.empty() || costs[0].empty()) return 0;
    const int n = costs.size();
    const int m = costs[0].size();
    if (n == 1 && m == 1) return costs[0][0];
    vector<vector<int>> M(n + 1, vector<int>(m, 0));
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < m; ++j) {
        M[i][j] = INT_MAX;
        for (int k = 0; k < m; ++k) {
          if (k == j) continue;
          M[i][j] = min(M[i][j], M[i - 1][k] + costs[i - 1][j]);
        }
      }
    }
    int res = INT_MAX;
    for (auto k : M.back())
      res = min(res, k);
    return res;
  }



  // Can Plant Flowers
  // Given a flower bed in the form of array of 0 and 1s, see if we can plant n more flowers so that no flowers are adjacent
  // e.g. [1 0 0 0 1], n=1 --> true, n=2 --> false.
  // Little trick: we can mutate the array by padding two zeros at both ends
  // Time O(n)
  bool canPlaceFlowers(vector<int>& bed, int n) {
    if (n == 0) return true;
    bed.insert(bed.begin(), 0);
    bed.push_back(0);
    for (int i = 1; i < bed.size() - 1; ++i)
      if (bed[i - 1] + bed[i] + bed[i + 1] == 0) {
        bed[i] = 1; // plant a flower here
        if (--n <= 0)
          return true;
      }
    return false;
  }
};
