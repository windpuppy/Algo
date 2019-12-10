#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <sstream>
#include <map>

using namespace std;

class TreeNode {
public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

class DynamicProgramming {

public:
  long fibonacci2(int k) {
    if (k <= 1) return k;

    vector<long> M(k + 1); // k + 1 for convenience
    M[0] = 0;
    M[1] = 1;
    for (int i = 2; i <= k; ++i)
      M[i] = M[i - 1] + M[i - 2];
    return M[k];
  }

  long fibonacci2_iter(int k) {
    // handle k = 0 or 1
    if (k <= 1) return k;

    // handle k = 2
    long a = 0, b = 1, sum = a + b;

    int n = 2;
    while (n <= k) {
      sum = a + b;
      a = b;
      b = sum;
      n++;
    }
    return sum;
  }

  // Note: this one does not need DP (unlike the longest ascending subsequence)
  // Just do EAST MOUNTAIN UP AGAIN when we see a dip (OR EQUAL)
  int longestAscendingSubArray(vector<int> nums) {
    if (nums.empty()) return 0;

    int longest = 1;
    int curr = 1;

    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] > nums[i - 1]) {
        curr++;
        longest = max(longest, curr);
      }
      else {
        curr = 1;
      }
    }
    return longest;
  }

  // M[i] represents: the length of LAS ending at i
  // Induction rule: for each i, M[i] = 1 + max(M[j]), if there is a j between (0,i) and a[j] < a[i]
  //                             physical meaning: find the max answer at j (a[j] also a smaller number than myself), then plus 1 (myself) is my current answer
  //                             M[i] = 1, if no such j exists
  // Return, max(M)
  // Time: O(n^2), Space: O(n)
  int longestAscendingSubSequence(vector<int> nums) {
    if (nums.empty()) return 0;
    const int size = nums.size();
    vector<int> M(size);
    M[0] = 1;

    for (int i = 1; i < size; ++i) {
      // Now lets find the max number within (0,i) that
      int pos = -1;
      int len = 0;
      for (int j = 0; j < i; ++j)
        if (M[j] > len && nums[j] < nums[i]) {
          len = M[j];
          pos = j;
        }

      M[i] = pos == -1 ? 1 : 1 + M[pos];
    }

    int res = *max_element(M.begin(), M.end());
    return res;
  }



  // Longest consecutive ones
  int longestConsecutiveOnes(vector<int> nums) {
    if (nums.empty()) return 0;

    int longest = 0;
    int curr = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 1) {
        curr++;
        longest = max(longest, curr);
      }
      else
        curr = 0;
    }
    return longest;
  }


  // Longest consecutive ones, and we can absorb 1 zero
  int longestConsecutiveOnes2(vector<int> nums) {
    const int size = nums.size();
    if (size < 1) return 0;
    int slow = 0, fast = 0, globalMax = 0;
    bool zeroAbsorbed = false;

    while (fast < size) {
      if (nums[fast] == 1) // hit a 1
        globalMax = max(globalMax, ++fast - slow);

      else if (!zeroAbsorbed) { // hit a 0, but we can absorb? move fast
        globalMax = max(globalMax, ++fast - slow);
        zeroAbsorbed = true;
      }

      else { // hit a 0, but 0 already absorbed? move slow
        slow++;
        if (nums[slow - 1] == 0) zeroAbsorbed = false; // did we just throw away a 0?
      }
    }
    return globalMax;
  }



  // Longest consecutive ones, and we can absorb k zeros
  // Instead of a boolean control flag used in above, we use a count to record "how many 0s we have absorbed in the current sliding window"
  int longestConsecutiveOnes3(vector<int> nums, int k) {
    const int size = nums.size();
    if (size < 1) return 0;
    int slow = 0, fast = 0, count = 0, globalMax = 0;

    while (fast < size) {
      // 1. If we hit a 1
      if (nums[fast] == 1) // hit a 1
        globalMax = max(globalMax, ++fast - slow);

      else if (count < k) { // hit a 0, but we can absorb another 0? move fast
        globalMax = max(globalMax, ++fast - slow);
        count++;
      }
      else { // hit a 0, but no more 0 can be absorbed? move slow
        slow++;
        if (nums[slow - 1] == 0) count--; // did we just throw away a 0?
      }
    }
    return globalMax;
  }



  // Input: [100, 4, 200, 1, 3, 2], Output: 4, because [4, 1 3 2], yes, output needs to be a consecutive sequence ie. no missing number
  // The difficulty here is when we see a 4, we don't know what's happening on the right, and if we scan from right to left we face the same issue, so what do we do?
  // Solution 1: sort and count. That's O(nlogn). Can we do it in O(n) time?
  // Solution 2: use hash
  // 1) insert all elements into a hashset, then do the following for each element a[i]
  // 2) Check if a[i] is the starting point of a sequence. We can simply look for a[i]-1 in the hash.
  //     If not found, then a[i] is the start of a sequence
  //     then, count a[i] + 1, +2, +3 etc. towards right, see how many we can find, update global max
  int longestConsecutiveSequence(vector<int> nums) {
    unordered_set<int> set;
    for (auto n : nums)
      set.insert(n);
    int res = 0;
    //vector<int> temp(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      int curr = nums[i];
      if (set.find(curr - 1) == set.end()) {
        int next = curr + 1;
        while (set.find(next) != set.end())
          next++;
        res = max(res, next - curr);
        //temp[i] = next - curr;
      }
    }
    return res;
  }



  // Build 4 auxilary 2D matrices, left, right, top, bottom to record longest 1s from each direction
  // For each (i, j), take its shortest arm
  // Double for loop to find the global max
  // Optimization: merge 4 books into 1, as we are taking min of them
  // Time: O(n*m)
  // Space: O(n*m)
  int longestCrossOfOnes(vector<vector<int>> matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    vector<int> temp(cols);
    vector<vector<int>> top(rows, temp);
    vector<vector<int>> bottom(top), left(top), right(top);

    // top down
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        if (i == 0)
          top[i][j] = matrix[i][j];
        else
          top[i][j] = matrix[i][j] == 0 ? 0 : top[i - 1][j] + 1;

    // bottom up
    for (int i = rows - 1; i >= 0; --i)
      for (int j = 0; j < cols; ++j)
        if (i == rows - 1)
          bottom[i][j] = matrix[i][j];
        else
          bottom[i][j] = matrix[i][j] == 0 ? 0 : bottom[i + 1][j] + 1;

    // left right
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        if (j == 0)
          left[i][j] = matrix[i][j];
        else
          left[i][j] = matrix[i][j] == 0 ? 0 : left[i][j - 1] + 1;

    // right left
    for (int i = 0; i < rows; ++i)
      for (int j = cols - 1; j >= 0; --j)
        if (j == cols - 1)
          right[i][j] = matrix[i][j];
        else
          right[i][j] = matrix[i][j] == 0 ? 0 : right[i][j + 1] + 1;

    int longest = 0;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        longest = max(longest,
          min(min(top[i][j], bottom[i][j]), min(left[i][j], right[i][j])));

    return longest;
  }

  // Almost exactly the same as longest cross of ones
  int longestXOfOnes(vector<vector<int>> matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    vector<int> temp(cols);
    vector<vector<int>> a(rows, temp);
    vector<vector<int>> b(a), c(a), d(a);

    // top left
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        if (i == 0 || j == 0)
          a[i][j] = matrix[i][j];
        else
          a[i][j] = matrix[i][j] == 0 ? 0 : a[i - 1][j- 1] + 1;

    // bottom left
    for (int i = rows - 1; i >= 0; --i)
      for (int j = 0; j < cols; ++j)
        if (i == rows - 1 || j == 0)
          b[i][j] = matrix[i][j];
        else
          b[i][j] = matrix[i][j] == 0 ? 0 : b[i + 1][j - 1] + 1;

    // top right
    for (int i = 0; i < rows; ++i)
      for (int j = cols - 1; j >= 0; --j)
        if (i == 0 || j == cols - 1)
          c[i][j] = matrix[i][j];
        else
          c[i][j] = matrix[i][j] == 0 ? 0 : c[i - 1][j + 1] + 1;

    // bottom right
    for (int i = rows - 1; i >= 0; --i)
      for (int j = cols - 1; j >= 0; --j)
        if (i == rows - 1 || j == cols - 1)
          d[i][j] = matrix[i][j];
        else
          d[i][j] = matrix[i][j] == 0 ? 0 : d[i + 1][j + 1] + 1;

    int longest = 0;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        longest = max(longest,
          min(min(a[i][j], b[i][j]), min(c[i][j], d[i][j])));

    return longest;
  }

  

  // M[i] represents from 0 to i-th elementing (including i), the largest sum of subarray
  // Induction rule: M[i] = max(M[i - 1], 0) + input
  // physical meaning: if my previous contribution is minus, why should I bring it with me?
  // Time O(n), Space O(n) but can be optimized to O(1)
  int largestSubArraySum(vector<int> nums) {
    if (nums.empty()) return 0;
    const int n = nums.size();
    vector<int> M(nums);
    int globalMax = nums[0];

    for (int i = 1; i < n; ++i) {
      int contrib = max(M[i - 1], 0);
      M[i] = contrib + nums[i];
      globalMax = max(globalMax, M[i]);
    }

    return globalMax;
  }



  // Same as above, but need to return [sum, left, right]
  // We use ci, cj, gi, gj for current left/right, global left/right
  //   When to update current left/right:
  //     curr right = i
  //     curr left "reset" to i when negative contribution is detected, otherwise it doesn't change
  //   When to update global left/right:
  //     whenever global max is updated
  vector<int> largestSubArraySum2(vector<int> input) {
    if (input.empty()) return vector<int>();
    const int n = input.size();
    vector<int> M(input);
    int globalMax = input[0];

    int ci = 0, cj = 0, gi = 0, gj = 0;

    for (int i = 1; i < n; ++i) {
      cj = i;
      int contrib = M[i - 1];
      if (contrib < 0) {
        contrib = 0;
        ci = i;
      }
      M[i] = contrib + input[i];

      if (M[i] > globalMax) {
        globalMax = M[i];
        gi = ci;
        gj = cj;
      }
    }

    return vector<int>{globalMax, gi, gj};
  }



  // O(n^6) solution: 2 for loops for top left corner, 2 for loops for bottom right corner, 2 for loops to sum the square - 6 in total
  // O(n^5) solution: build 1D prefix book: sum of everything to its left:
  //                  prefix[i][j] = prefix[i][j-1] + a[i][j]
  //                  4 for loops to define a rectangle, in which we do row by row sum:
  //                  for each y, sum += prefix[x2][y] - prefix[x1-1][y]
  // O(n^4) solution: build 2D prefix book: sum of everything to its top left
  //                  ----------
  //                  | xo | o |
  //                  -----------
  //                  | x  |   |
  //                  ------ (i,j)
  //                  prefix[i][j] = prefix x + prefix o - prefix xo + a[i][j]
  //                  sum[i][j] = square x + square o - square xo
  int largestSubmatrixSum(vector<vector<int>> matrix) {
    if (matrix.empty() || matrix[0].empty())  return 0;
    else if (matrix.size() == 1 && matrix[0].size() == 1) return matrix[0][0];
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    vector<vector<int>> M(matrix);
    int globalMax = INT_MIN;

    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        if (i == 0 && j == 0) continue;
        else if (i == 0) M[i][j] = M[i][j - 1] + matrix[i][j];
        else if (j == 0) M[i][j] = M[i - 1][j] + matrix[i][j];
        else M[i][j] = M[i][j - 1] + M[i - 1][j] - M[i - 1][j - 1] + matrix[i][j];

    for (int y1 = 0; y1 < rows; y1++)
      for (int x1 = 0; x1 < cols; x1++)
        for (int y2 = y1; y2 < rows; y2++)
          for (int x2 = x1; x2 < cols; x2++) {
            int partA = 0, partB = 0, partC = 0;
            if (x1 != 0 && y1 != 0) {
              partA = M[y2][x1 - 1];
              partB = M[y1 - 1][x2];
              partC = M[y1 - 1][x1 - 1];
            }
            else if (x1 != 0)
              partA = M[y2][x1 - 1];
            else if (y1 != 0)
              partB = M[y1 - 1][x2];

            int sum = M[y2][x2] - partA - partB + partC;
            globalMax = max(sum, globalMax);
          }

    return globalMax;
  }

  // O(^3) solution: only 2 for loops, define top and bottom rows of a rectangle, run "largest subarray sum" on a "squashed" row
  // ooooooooooooooooooooo
  // ooooooooooooooooooooo
  // xxxxxxxxxxxxxxxxxxxxx <-- top row
  // xxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxx <-- bottom row
  // XXXXXXXXXXXXXXXXXXXXX <-- squashed row of the above 3
  // ooooooooooooooooooooo
  // Advantage: Time O(^3), no need to keep a DP book
  int largestSubmatrixSum2(vector<vector<int>> matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    else if (matrix.size() == 1 && matrix[0].size() == 1) return matrix[0][0];
    const int rows = matrix.size(), cols = matrix[0].size();
    int globalMax = INT_MIN;

    for (int i = 0; i < rows; ++i) {
      vector<int> squashed(cols, 0);
      for (int i2 = i; i2 < rows; ++i2) {
        // accumulate current row
        for (int k = 0; k < cols; ++k) squashed[k] += matrix[i2][k];
        
        // run largest subarray sum
        int maxSum = largestSubArraySum_helper(squashed);

        // update global max
        globalMax = max(globalMax, maxSum);
      }
    }
    return globalMax;
  }

  int largestSubArraySum_helper(const vector<int>& input) {
    int globalMax = input[0], m = input[0];
    for (int i = 1; i < input.size(); ++i) {
      int contrib = max(m, 0);
      m = contrib + input[i];
      globalMax = max(globalMax, m);
    }
    return globalMax;
  }



  // Very similar to largest subarray sum, but here we need to consider the negative value
  // so in additional to tracking the max, we need to track a global min as well, so when a negative number comes in, we might have a max
  // Time: O(n)
  // Space: O(1)
  double largestSubArrayProduct(vector<double> nums) {
    const int size = nums.size();
    vector<double> Max(size), Min(size);
    Max[0] = Min[0] = nums[0];
    double res = nums[0];

    for (int i = 1; i < size; ++i) {
      double val = nums[i];
      if (val > 0) {
        Max[i] = max(val, Max[i-1] * val);
        Min[i] = min(val, Min[i-1] * val);
      }
      else {
        Max[i] = max(val, Min[i-1] * val);
        Min[i] = min(val, Max[i-1] * val);
      }
      res = max(res, Max[i]);
    }
    return res;
  }

  // Space optimization for the above solution
  // Space: O(1);
  double largestSubArrayProduct2(vector<double> nums) {
    const int size = nums.size();
    double maxCurr = nums[0], minCurr = nums[0], maxPrev = nums[0], minPrev = nums[0];
    double res = nums[0];

    for (int i = 1; i < size; ++i) {
      double val = nums[i];
      if (val > 0) {
        maxCurr = max(val, maxPrev * val);
        minCurr = min(val, minPrev * val);
      }
      else {
        maxCurr = max(val, minPrev * val);
        minCurr = min(val, maxPrev * val);
      }
      res = max(res, maxCurr);
      maxPrev = maxCurr;
      minPrev = minCurr;
    }
    return res;
  }



  // Similar to 1D problem, and we optimize space by using max min variables instead of vectors
  double largestSubmatrixProduct(vector<vector<double>> matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    else if (matrix.size() == 1 && matrix[0].size() == 1) return matrix[0][0];
    const int rows = matrix.size(), cols = matrix[0].size();
    double res = matrix[0][0];

    for (int i = 0; i < rows; ++i) {
      vector<double> squashed(cols, 1.0);
      for (int i2 = i; i2 < rows; ++i2) {
        // accumulate current row ie. THE BLUE SQUASHED AREA
        for (int k = 0; k < cols; ++k) squashed[k] *= matrix[i2][k];

        // run largest subarray sum
        double maxProduct = largestSubArrayProduct(squashed);

        // update global max
        res = max(res, maxProduct);
      }
    }
    return res;
  }


  // Max product of 3 elements
  // It's either 3 biggest positive values, or 1 biggest positive * 2 largest negative values
  // TIme: O(nlogn)
  int maximumProduct(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int v1 = nums[n - 1] * nums[n - 2] * nums[n - 3];
    int v2 = nums[0] * nums[1] * nums[n - 1];
    return max(v1, v2);
  }

  // A better solution:
  // Track the max product of 3 numbers, and track the max & min products of 2 numbers (min for negative)
  // Time: O(n)
  int maximumProduct2(vector<int>& nums) {
    int high3 = nums[0] * nums[1] * nums[2];
    int high2 = nums[0] * nums[1];
    int low2 = high2;
    int maxVal = max(nums[0], nums[1]);
    int minVal = min(nums[0], nums[1]);

    for (auto n : nums) {
      // make sure of the order of calculation below!
      high3 = max3(high3, n * high2, n * low2);

      high2 = max3(high2, n * maxVal, n * minVal);
      low2 = min3(low2, n * maxVal, n * minVal);

      maxVal = max(maxVal, n);
      minVal = min(minVal, n);
    }
    return high3;
  }

  // helper
  int max3(int a, int b, int c) { return max(a, max(b, c)); }
  int min3(int a, int b, int c) { return min(a, min(b, c)); }



  // Max product of 3 numbers
  int maximumProduct3(vector<int>& nums) {
    int f[2][4], i, j;
    f[0][0] = f[1][0] = 1;
    for (j = 3; j > 0; --j) {
      f[0][j] = INT_MIN;
      f[1][j] = INT_MAX;
    }

    for (i = 0; i < nums.size(); ++i) {
      for (j = 3; j > 0; --j) {
        if (f[0][j - 1] == INT_MIN) {
          continue;
        }
        f[0][j] = max(f[0][j], max(f[0][j - 1] * nums[i], f[1][j - 1] * nums[i]));
        f[1][j] = min(f[1][j], min(f[0][j - 1] * nums[i], f[1][j - 1] * nums[i]));
      }
    }
    return f[0][3];
  }



  // Try rope from 2 - n meter long
  // Then try right cut, from n - 1 to 1 (and assume the right cut is "final" such that right part cannot be cut anymore
  // Example, 5 meter long rope
  // case 4: _ | _ _ _ _ max(1m, M[1]) * 4m
  // case 3: _ _ | _ _ _ max(2m, M[2]) * 3m
  // case 2: _ _ _ | _ _ max(3m, M[3]) * 2m
  // case 1: _ _ _ _ | _ max(4m, M[4]) * 1m
  // and we record a rolling max from case 4 to case 1
  // 
  // Time: O(n^2), Space: O(n)
  int maxProductCuttingRope(int n) {
    vector<int> M(n + 1);
    M[0] = 0; // 0 meter long, doesn't make sense
    M[1] = 0; // 1 meter long, at least 1 cut, doesn't make sense

    for (int len = 2; len <= n; ++len) {
      int currMax = 0;

      for (int right = len - 1; right >= 1; --right) {
        auto left = len - right;
        auto currCase = right * max(left, M[left]);
        currMax = max(currMax, currCase);
      }

      M[len] = currMax;
    }

    return M[n];
  }



  // array hopper
  // e.g [2, 3, 1, 1, 4]
  // M[]: T  T  T  T  T
  // M[4] = true, because 4 is the final destination
  // Induction rule:
  // M[i] means whether I can jump from the i-th position to the final target
  // M[i] is true, if we can jump from i to a location j, and j is already known to be true (ie. j can reach final target)
  //
  // Time: O(n^2), Space: O(n)
  bool arrayHopper(vector<int> nums) {
    const int n = nums.size();
    if (n == 1) return true;
    vector<bool> M(n, false);
    M[n - 1] = true; // final target

    // optimization 1:
    if (nums[0] >= n - 1) return true;

    for (int i = n - 2; i >= 0; i--) {
      int ability = nums[i];
      int distance = n - 1;
      // optimization: if we can take one big step past final target, we must be able to reach that target
      if (ability >= distance) {
        M[i] = true;
        continue;
      }

      // look for any j location within i's reach, see if there is any j that can reach the target
      bool found = false;
      for (int jump = 1; jump <= ability; jump++) {
        int j = i + jump;
        if (M[j] == true) {
          found = true;
          break;
        }
      }

      // if not found, don't just return false;
      // because you cannot reach target, but some stops before you can jump over you and reach it.
      M[i] = found;
    }

    return M[0] == true;
  }



  // Instead of unlimited number of jumps, Array Hopper 2 need to return the minimum mumber of jumps
  // e.g. 3, 3, 1, 0, 4
  // Same as Array Hopper 1, we go right to left
  // M[i] records the min number of stops from i to the target
  // Base case M[4] = 0
  // Induction Rule M[i] = min(M[j]) + 1, where j is within (i, target) and can be reached from i by 1 jump
  // Time O(n^2)
  int arrayHopper2(vector<int> nums) {
    const int n = nums.size();
    if (n == 1) return 0;

    // optimization:
    if (nums[0] >= n - 1) return 1;

    vector<int> M(n, INT_MAX); // minimum jumps at each location
    M[n - 1] = 0;

    for (int i = n - 2; i >= 0; --i) {
      int ability = nums[i]; // ability 0? by pass
      if (ability == 0)
        continue;

      for (int j = i + 1; j < n; ++j)
        if (ability >= j - i) // ability >= distance ? can reach
          M[i] = min(M[i], M[j]);

      // plus extra jump from current i to j
      if (M[i] != INT_MAX)
        M[i]++;
    }

    return M[0] == INT_MAX ? -1 : M[0];
  }


  // For example, to check input of "bobcatrob" with dict of "bob", "cat", "rob"
  // Use book M, M[i] represents can "the substring from the begining to the i-th character" be composed by words from the dict
  // Same as cutting rope, left considered as "Big Section" - can cut, right considered as "Small Section" - no cut
  // Big Section: check M[], Small Section: manual work
  // M[0] = true (empty string)
  // M[1] = b, false
  // M[2] = bo,  case 0 no cut, bo -> false
  //             case 1 cut, b check M[1], o -> false
  //               case  0 || case 1
  // M[3] = bob, case 0 no cut, bob -> true
  //             case 1 b | ob, b check M[1], ob -> false
  //             case 2 bo | b, bo check M[2], b -> false
  //               case 0 || case 1 || case 2
  bool wordBreak(string word, vector<string> dict) {
    unordered_set<string> set(dict.begin(), dict.end());
    vector<bool> M(word.size() + 1, false); // plus 1, because we reserve M[0] for empty string, for convenience
    M[0] = true;

    for (int i = 1; i <= word.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        string right = word.substr(j, i - j);
        bool rightMatch = set.find(right) != set.end();

        if (M[j] && rightMatch) { // eg. bob | c, left BIG (use M), right SMALL (manual check)
          M[i] = true;
          break;
        }
      }
    }
    return M.back();
  }



  // Workbreak 2
  // Give string "catsanddog", dictionary {cat, cats, sand, and, dog} ... find all possible sentences
  // Return "cats and dog", "cat sand dog"
  // Problem break down - still follow the LEFT BIG RIGHT SMALL principle!
  // wordBreak2("") + lookup("catsanddog")
  // wordBreak2("c") + lookup("atsanddog")
  // wordBreak2("ca") + lookup("tsanddog")
  // wordBreak2("cat") + lookup("sanddog")
  // wordBreak2("cats") + lookup("anddog")
  // wordBreak2("catsa") + lookup("nddog")
  // wordBreak2("catsan") + lookup("ddog")
  // wordBreak2("catsand") + lookup("dog") --> right match, dfs call "catsand"
  // wordBreak2("catsandd") + lookup("og")
  // wordBreak2("catsanddo") + lookup("g")
  // wordBreak2("catsanddog") + lookup("")
  //
  // wordBreak2("") + lookup("catsand")
  // wordBreak2("c") + lookup("atsand")
  // wordBreak2("ca") + lookup("tsand")
  // wordBreak2("cat") + lookup("sand") --> right match, dfs call "cat"
  // wordBreak2("cats") + lookup("and") --> right match, dfs call "cats"
  // wordBreak2("catsa") + lookup("nd")
  // wordBreak2("catsan") + lookup("d")
  // wordBreak2("catsand") + lookup("")
  // ...
  vector<string> wordBreak2(string s, vector<string>& dict) {
    unordered_set<string> set(dict.begin(), dict.end());
    unordered_map<string, vector<string>> map;
    return wordBreak2_dfs(s, set, map);
  }

  const vector<string>& wordBreak2_dfs(string s, unordered_set<string>& set, unordered_map<string, vector<string>>& map) {
    if (map.count(s)) return map[s];
    vector<string> ans;
    if (set.count(s)) // if in dictionary, add to answer
      ans.push_back(s);

    for (int i = 1; i < s.length(); ++i) {
      // check if right part is a word
      const string& right = s.substr(i);
      if (!set.count(right)) continue;

      // get ans for left, right, and stich them together
      string left = s.substr(0, i);
      auto left_ans = wordBreak2_dfs(left, set, map);
      auto curr_ans = append(left_ans, right);

      // append the current answer to the global answer collection
      ans.insert(ans.end(), left_ans.begin(), left_ans.end());
    }

    map[s] = ans; // memo and return
    return ans;
  }

  vector<string> append(const vector<string>& prefixes, const string& word) {
    vector<string> res;
    for (const auto& p : prefixes)
      res.push_back(p + " " + word);
    return res;
  }



  // Input: pattern = "abba", str = "dog cat cat dog"
  // Output: true
  bool wordPattern(string str, string pat) {
    unordered_map<char, int> p2i;
    unordered_map<string, int> w2i;
    istringstream in(str);
    int i = 0, n = pat.size();

    for (string word; in >> word; ++i) {
      char c = pat[i];
      if (i == n || p2i[c] != w2i[word])
        return false;
      p2i[c] = w2i[word] = i + 1;
    }
    return i == n;
  }

  // Given two words, return the minimum number of operations needed to convert word 1 to word 2
  // Operation allowed: insert, delete, replace a char
  // DFS naive approach, O(3^(m+n))
  int editDistance_DFS(string one, string two) {
    if (one.empty()) return two.size();
    if (two.empty()) return one.size();

    // same char
    if (one[0] == two[0])
      return editDistance_DFS(one.substr(1), two.substr(1));

    int rep = editDistance_DFS(one.substr(1), two.substr(1)); // try replace
    int del = editDistance_DFS(one.substr(1), two); // try delete from one
    int ins = editDistance_DFS(one, two.substr(1)); // try insert in one

    return min(rep, min(del, ins)) + 1;
  }

  // DP solution
  // s1 = xxxxxxx + 'a'
  // s2 = yyyyyyyyyyy + 'b'
  // M[i][j] represents the minimum number of edits to transform first i chars (0 ~ i-1) of one, to first j chars (0 ~ j-1) of two
  // Now we fill the 2D table, we first fill the top row and left column (ie. to transform "" to n char string, we need n steps)
  // Then we can either fill row-wise, or column-wise.
  // The rule is: if we see the same two chars, we copy diagonally; otherwise, we take the min(diag, top, left) + 1.
  //       0 1 2 3 4
  //         s g h j
  //   -------------
  // 0   | 0 1 2 3 4
  // 1 a | 1 1 2 3 4
  // 2 s | 2 1 2 3 4
  // 3 d | 3 2 2 3 4
  // 4 f | 4 3 3 3 4
  int editDistance(string one, string two) {
    if (one.empty()) return two.size();
    if (two.empty()) return one.size();

    const int rows = one.size() + 1;
    const int cols = two.size() + 1;
    vector<int> tmp(cols);
    vector<vector<int>> M(rows, tmp);
    M[0][0] = 0;

    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        if (i == 0) M[i][j] = j;
        else if (j == 0) M[i][j] = i;
        else if (one[i - 1] == two[j - 1])
          M[i][j] = M[i - 1][j - 1];
        else
          M[i][j] = min(M[i - 1][j - 1], min(M[i][j - 1], M[i - 1][j])) + 1;
      }

    return M[rows - 1][cols - 1];
  }



  // Naive solution - use 2D DP, check if return > 1
  // That would be O(m*n)
  // A more efficient solution is to simultaneously traverse both strings with two pointers
  // 1) if same char, move i and j
  // 2) if diff char
  //    a) increment count, if > 1, return false
  //    b) if string length not the same? only possible edit is remove a char, so we increment pointer to the longer string
  //    c) if string length are the same? only possible edit is replace a char, so we move both pointers
  //    increment counter
  // NOTE, EQUAL STRINGS ARE NOT ONE EDIT DISTANCE!
  bool oneEditDistance(string one, string two) {
    const int m = one.size();
    const int n = two.size();
    if (abs(m - n) > 1) return false;

    // if we reach here, the size difference between two strings are either 0 or 1
    int count = 0, i = 0, j = 0;
    while (i < m && j < n) {
      if (one[i] == two[j]) {
        i++;
        j++;
      }
      else {
        if (count == 1) return false;
        count++;

        if (m == n) {
          i++; j++;
        }
        else if (m > n)
          i++;
        else
          j++;
      }
    }

    // if both strings run out and counter is not violated? NOTE, EQUAL STRINGS ARE NOT ONE EDIT DISTANCE!
    if (i == m && j == n)
      return count == 1;
    // if not, that means we have one extra bit left, so the current counter has to be 0
    else
      return count == 0;
  }



  // DP solution
  // M[i][j] meaning: the largest square that can be formed till point (i,j) where (i,j) is the right bottom corner
  // Induction rule:
  //   first set top row and first column all to input[i][j], then scan row by row. for each (i,j),
  //   2---3
  //   |   |
  //   1---x
  //   For x, if matrix[i][j] is 1, set it to min of 3 values + 1
  //          if matrix[i][j] is 0, reset to 0
  //   maintain a globalMax
  // Time: O(n^3) ==> O(n^2)
  int largestSquareOfOnes(vector<vector<int>> matrix) {
    const int n = matrix.size();
    if (n == 0 || matrix[0].size() == 0) return 0;
    vector<vector<int>> M(matrix);
    int globalMax = 0;

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        if (i == 0 || j == 0)
          M[i][j] = matrix[i][j];
        else if (matrix[i][j] == 1)
          M[i][j] = min(min(M[i][j - 1], M[i - 1][j]), M[i - 1][j - 1]) + 1;

        globalMax = max(globalMax, M[i][j]);
      }
    return globalMax;
  }



  // https://www.youtube.com/watch?v=ZmnqCZp9bBs&t=628s
  // Use a stack to save index positins
  // 1. If we "step up", continue to push bars into the stack
  // 2. If we "step down", we need to look left: by keep popping higher bars out of the stack until stack is empty or we have a <= value at the stock top
  // 3. When popping:
  //    height = stack top
  //    left boundary = 0 if stack empty, (stack top + 1) if not empty
  //    area = height * (i - left)
  // Time O(n), Space O(n)
  int largestRectangleInHistogram(vector<int> input) {
    int maxArea = 0;
    stack<int> stack;

    // Note, we need the final i when we run through all elements, so we add a virtual bar 0 at the end
    input.push_back(0);
    for (int i = 0; i < input.size(); ++i) {
      int curr = input[i];

      while (!stack.empty() && curr <= input[stack.top()]) {
        int height = input[stack.top()];
        stack.pop();

        int left = stack.empty() ? 0 : stack.top() + 1;
        int area = height * (i - left);
        maxArea = max(area, maxArea);
      }
      stack.push(i);
    }
    return maxArea;
  }



  // This is TOTALLY different than largest SQUARE of ones
  // We stack row by row: accummulate if 1, reset to 0 if 0
  // Then for each row, we do "max area of histogram"
  // Time: O(n^3), Space: O(n)
  int largestRectangleOfOnes(vector<vector<int>> matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    const int rows = matrix.size(), cols = matrix[0].size();
    int globalMax = 0;

    vector<int> curr(matrix[0]);
    for (int i = 0; i < rows; ++i) {
      if (i != 0)
        for (int j = 0; j < cols; ++j)
          curr[j] += matrix[i][j] ? 1 : -curr[j];

      int area = largestRectangleInHistogram(curr);
      globalMax = max(globalMax, area);
    }
    return globalMax;
  }



  // Build two tables with "reverse scan": right to left, bottom to up
  // Run 2 for loops for each (i, j) point
  // At(i, j), run 3rd for loop for size(n ~ 1), n is the min of rightArm[i][j], bottomArm[i][j] -- that's maximum possible square allowed at (i, j)
  //    we obviously also need to check two additional corners
  //      (i,j) ------ A   bottomArm[A] >= size?
  //        |          |
  //        |
  //        B   ---        rightArm[B] >= size?
  // Time: O(n^6) ==> O(n^3)
  int largestSquareSurroundedByOnes(vector<vector<int>> matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    vector<vector<int>> right(matrix), bottom(matrix);
    int globalMax = 0;

    for (int i = 0; i < rows; ++i) // initialize right
      for (int j = cols - 1; j >= 0; --j)
        if (j == cols - 1) right[i][j] = matrix[i][j];
        else right[i][j] = matrix[i][j] * (right[i][j + 1] + 1);

    for (int i = rows - 1; i >= 0; --i) // initialize bottom
      for (int j = 0; j < cols; ++j)
        if (i == rows - 1) bottom[i][j] = matrix[i][j];
        else bottom[i][j] = matrix[i][j] * (bottom[i + 1][j] + 1);

    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        if (matrix[i][j] == 0) continue; // pruning 1

        int w = right[i][j];
        int h = bottom[i][j];
        int size = min(w, h);
        if (size <= globalMax) continue; // pruning 2

        for (int s = size; s >= 1; --s) {
          if (bottom[i][j + s - 1] >= s && right[i + s - 1][j] >= s)
            globalMax = max(s, globalMax);
        }
      }
    return globalMax;
  }



  // 0 no match; 1 right; 2 down; 3 both
  // Keep two books: right[][], down[][], to record at (i,j) position, its longest possible right/down arms
  // For each (i,j), the biggest square it can form is to start searching from min(right, bottom) and gradually reduce size, try form a square
  // Time: O(n^3), Space: O(n^2)
  int largestSquareOfMatches(vector<vector<int>> matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    int globalMax = 0;
    const int rows = matrix.size(), cols = matrix[0].size();

    // The longest right/down arm length ending at (i,j)
    vector<int> tmp(cols + 1, 0);
    vector<vector<int>> right(rows + 1, tmp), down(right);

    for (int i = rows - 1; i >= 0; --i)
      for (int j = cols - 1; j >= 0; --j) {
        if (hasRight(matrix[i][j]))
          right[i][j] = right[i][j + 1] + 1;
        if (hasDown(matrix[i][j]))
          down[i][j] = down[i+1][j] + 1;
        
        // max square formed at (i,j) as top left corner, is determined by min of its two arms: right(i,j), down(i,j)
        // we start with that size, and gradually reduce, stop at the first formed square
        if (hasBoth(matrix[i][j])) {
          int size = min(right[i][j], down[i][j]);
          for (int len = size; len >= 1; len--)
            if (right[i + len][j] >= len && down[i][j + len] >= len) {
              globalMax = max(globalMax, len);
              break;
            }
        }
      }
    return globalMax;
  }

  bool hasRight(int value) { return value % 2 == 1; }
  bool hasDown(int value) { return value >= 2; }
  bool hasBoth(int value) { return value == 3; }


  // Brutal force solution:
  // For each position, find its left highest bar and right highest bar, the amount of water it can trap is min(left, right) - bar[i]
  // This will be O(n^2)
  //
  // DP solution:
  // Instead of using a book, we use two values: lmax and rmax
  // lmax: at any point, its left highest wall; same for rmax
  // We start with left most and right most walls, push two boundaries inward
  // Push rule: between lmax and rmax, we push inward the lower one, because the higher wall will have future impact on the inner bars, but lower wall won't
  // e.g. left 3, right 5, we push 3, because if there is a 7 in between, [7,5] can potentially hold more water, but [3,7] cannot
  // Stop until those two walls meet
  //
  // Time: O(n)
  // Space: O(1)
  int maxWaterTrapped(vector<int> w) {
    if (w.empty()) return 0;
    int i = 0, j = w.size() - 1, sum = 0;

    int lh = w[i]; // highest wall to its left at point i, including i
    int rh = w[j]; // highest wall to its right at point j, including j

    while (i < j) {
      if (w[i] <= w[j]) {
        sum += max(0, lh - w[i]); // add POSITIVE water
        lh = max(lh, w[i]); // update left wall
        i++;
      }
      else {
        sum += max(0, rh - w[j]); // add POSITIVE water
        rh = max(rh, w[j]); // update right wall
        j--;
      }
    }
    return sum;
  }



  // 1 transaction!
  // Brutal force: enumerate all (i, j) pairs, O(n^2)
  // Because it's one transaction, we want to buy at the lowest, and sell at the highest
  // For buy options for day i, there shouldn't be a lower price before i;
  // For sell options for day i, there shouldn't be a higher price after i.
  // So we need to track min price, and max profit
  //
  // L[i]: min PRICE so far
  // P[i]: max PROFIT so far, max(P[i - 1], price[i] - L[i])
  // Induction rule: P[i] = max(P[i-1], price[i] - L[i-1])
  //   meaning: at day i, I can simply not make a transaction (take my profit from yesterday)
  //        OR: at day i, I do make a transaction by price[i] - L[i] (minimum price seen so far)
  //        then I take the max of the two
  //
  // Time: O(n)
  // Space: O(n)
  int buyStock(vector<int> prices) {
    const int n = prices.size();
    if (n <= 1) return 0;

    vector<int> L(n); // min PRICE so far
    vector<int> P(n); // max PROFIT so far
    L[0] = prices[0];
    P[0] = 0;

    for (int i = 1; i < n; ++i) {
      L[i] = min(L[i - 1], prices[i]);
      P[i] = max(P[i - 1], prices[i] - L[i - 1]); // L[i - 1] here instead of L[i], because you cannot buy and sell on the same day
    }

    return P[n - 1];
  }



  // As many transactions
  // Trick: just simply add up all the positive sections
  int buyStock2(vector<int> prices) {
    const int n = prices.size();
    if (n <= 1) return 0;

    int sum = 0;
    for (int i = 1; i < n; ++i) {
      auto delta = prices[i] - prices[i - 1];
      sum += delta > 0 ? delta : 0;
    }
    return sum;
  }



  // At most 2 transactions (see below for k transactions)
  int buyStock3(vector<int>& prices) {
    if (prices.empty()) return 0;
    vector<int> tmp(prices.size(), 0);
    vector<vector<int>> M(3, tmp);
    const int trans = 3; // 0, 1, 2, trans
    const int days = prices.size();

    for (int i = 1; i < trans; ++i)
      for (int j = 1; j < days; ++j) {
        int maxVal = 0;
        for (int x = 0; x < j; ++x)
          maxVal = max(maxVal, prices[j] - prices[x] + M[i - 1][x]);
        M[i][j] = max(M[i][j - 1], maxVal);
      }
    return M.back().back();
  }



  // At most k transactions
  // 2D DP table as follows
  // M[i][j] : i transactions, jth day, max profit
  // M[i][j] = max of: I dont make a transaction on day j, and I do make transaction on day J
  //                1) I dont make a transaction on day j: M[i-1][j] - copy left
  //                2) I do make a transaction on day j, which is, the best you can get by transacting on jth day
  //                   formula: (price[j] - price[x]) + M[i-1][x], for x = 0 ... j-1
  //                   above meaning, profict of (sell the stock on day j that I bought on day x)
  //                                  plus max profit on day x with one less (i-1) transaction
  // Observation: from left to right in the table, it will not be decreasing because we can just NOT make any transaction if it hurts our value
  //              same for top down direction
  //
  // 1) Fill 0s first - 0 trans, 0 profit for all days
  //       day |   0 1 2 3 4 5 6 7
  //     price |   2 5 7 1 4 3 1 3 
  // trans     | 0 0 0 0 0 0 0 0 0
  //           | 1 0
  //           | 2 0
  // 2) Fill table for 1 max transactions
  //       day |   0 1 2 3 4 5 6 7
  //     price |   2 5 7 1 4 3 1 3 
  // trans     | 0 0 0 0 0 0 0 0 0
  //           | 1 0 3 5 5 5 5 5 5
  //           | 2 0
  // 3) Fill table for 2 max transactions
  //       day |   0 1 2 3 4 5 6 7
  //     price |   2 5 7 1 4 3 1 3 
  // trans     | 0 0 0 0 0 0 0 0 0
  //           | 1 0 3 5 5 5 5 5 5
  //           | 2 0 3 5 5 8 8 8 8
  //
  // Time: O(k^2 * n)
  // and when k > n, it's essentially O(n^3) because we can make at most 1 transcation per day
  int buyStock4(vector<int> price, int k) {
    vector<int> tmp(price.size(), 0);
    vector<vector<int>> M(k + 1, tmp);
    const int trans = k + 1;
    const int days = price.size();

    for (int i = 1; i < trans; ++i)
      for (int j = 1; j < days; ++j) {
        int maxVal = 0;

        // explore if the best scenario day x where profit on M[x] plus one more transaction (buy on x sell on j
        for (int x = 0; x < j; ++x)
          maxVal = max(maxVal, price[j] - price[x] + M[i - 1][x]);

        // then compare it against "not making a transaction on day j", which is just taking the max profit from day j-1
        M[i][j] = max(M[i][j - 1], maxVal);
      }
    return M.back().back();
  }
  
  // DP solution
  // Three cases
  // 1) if s[i] == p[j] || p[j] is '?' - meaning either it's a perfect match, or '?' replaces the new char
  //     M[i][j] copy diagonal
  // 2) else if p[j] is '*' - meaning we can either use * to ABSORB the new char, or we can consider * as empty string
  //     M[i][j] set to true if either up and left is true
  // 3) else
  //     M[i][j] = false
  // M[i][j] meaning: for string(0,i) and pattern(0,j) can they match
  // Note: add 0 row and 0 col for empty string!
  // Example:
  //     "" x ? y * z
  // ---------------
  // "" | T f f f f f
  // x  | f T f f f f
  // a  | f f T f f f
  // y  | f f f T T f
  // l  | f f f f T f
  // m  | f f f f T f
  // z  | f f f f T T
  bool wildCardMatching(string s, string p) {
    const int rows = s.length() + 1;
    const int cols = p.length() + 1;

    vector<bool> tmp(cols, false);
    vector<vector<bool>> M(rows, tmp);
    
    // first row
    for (int j = 0; j < cols; ++j) {
      if (j == 0) M[0][j] = true;
      else if (p[j-1] == '*') M[0][j] = M[0][j - 1];
      //else M[0][j] = false;
    }

    // first column
    // already initialized as T followed by all Fs

    for (int i = 1; i < rows; ++i)
      for (int j = 1; j < cols; ++j) {
        if (s[i-1] == p[j-1] || p[j-1] == '?')
          M[i][j] = M[i - 1][j - 1];
        else if (p[j-1] == '*')
          M[i][j] = M[i][j - 1] || M[i - 1][j];
        //else
        //  M[i][j] = false;
      }

    return M[rows - 1][cols - 1];
  }



  // stairs(n) is actually fibonacci(n+1)
  int climbingStairs(int n) {
    int m = n + 2;
    vector<int> M(m, 0);
    M[0] = 0; M[1] = 1;

    for (int i = 2; i < m; i++) {
      M[i] = M[i - 1] + M[i - 2];
    }
    return M.back();
  }



  // Given an array, find ascending 3 element subsequence
  // Build smaller, where smaller[i] records the index of a value to its left AND smaller than the current value, -1 if none such exist
  // Build larger, where larger[i] records the index of a value to its right AND larger than the current value, -1 if none such exist
  // Then we traverse these 2, if we find a i where smaller[i] and larger[i] are both not -1, that's (one of) our solutions
  // Time: O(3n), so it's O(n)
  // Space: O(1)
  bool ascendingTriple(vector<int> nums) {
    const int size = (int)nums.size();

    // build smaller
    int min_i = 0;
    vector<int> smaller(size);
    for (int i = 0; i < size; ++i)
      if (nums[i] <= nums[min_i]) {
        min_i = i;
        smaller[i] = -1;
      }
      else {
        smaller[i] = min_i;
      }

    // build larger
    int max_i = size - 1;
    vector<int> larger(size);
    for (int i = size - 1; i >= 0; --i)
      if (nums[i] >= nums[max_i]) {
        max_i = i;
        larger[i] = -1;
      }
      else {
        larger[i] = max_i;
      }

    // find solution(s)
    for (int i = 0; i < size; ++i)
      if (smaller[i] != -1 && larger[i] != -1)
        return true;

    return false;
  }



  // Least obstacle in 2*n matrix
  // We can only go up, down, right, but not left
  // Naitve solutions: dfs, bfs
  int leastObstacle(vector<vector<int>> matrix) {
    if (matrix.size() != 2) {
      return -1; // invalid input
    }
    else if (matrix[0].empty()) {
      return 0; // empty matrix
    }

    const int size = matrix[0].size();
    vector<int> M(2);
    M[0] = matrix[0][0];
    M[1] = M[0] + matrix[1][0];

    for (int j = 1; j < size; j++) {
      int i = M[0] < M[1] ? 0 : 1; // pick the better solution so far

      if (M[0] == M[1] && j != size - 1) {
        i = matrix[0][j + 1]; // if both solutions are the same, explore right
      }

      M[i] = M[i] + matrix[i][j];
      M[1 - i] = min(M[i], M[1 - i]) + matrix[1 - i][j];
    }

    return M.back();
  }




  // matrix all 0s, count unique paths
  int uniquePaths(int m, int n) {
    vector<vector<int>> M(m, vector<int>(n, 1));
    for (int i = 1; i < m; ++i)
      for(int j = 1; j < n; ++j)
        M[i][j] = M[i][j-1] + M[i-1][j];
    return M.back().back();
  }

  // This might sound like a DFS problem, but actually DP
  // 1) initialize first row and col, 1 if no obstacle, 0 if obstacle
  // 2) fill the book. 0 if obstacle, otherwise sum up + left
  int uniquePathsObstacles(vector<vector<int>> grid) {
    if (grid.empty() || grid[0].empty() || grid[0][0] == 1) return 0;
    const int rows = grid.size();
    const int cols = grid[0].size();
    vector<vector<int>> M(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        if (i == 0 || j == 0) M[i][j] = 1 - grid[i][j];
        else M[i][j] = grid[i][j] == 1 ? 0 : M[i][j-1] + M[i-1][j];
      }
    return M.back().back();
  }



  // Minimum path sum in a 2D grid to go from top left to bottom right - we can only move right or down
  // Dijkastra problem
  // Solution 1: use DFS from src to dst, explore all paths, record min, O(mn) time
  // Solution 2: use BFS from src to dst, explore all paths, record min, O(mn) time, (slightly better because we avoided recursion)
  // Solution 3: use DP
  int minimumPathSum(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    const int rows = grid.size();
    const int cols = grid[0].size();
    vector<vector<int>> M(rows, vector<int>(cols));
    M[0][0] = grid[0][0];

    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        if (i == 0 && j == 0)
          continue;
        else if (i == 0 && j != 0)
          M[i][j] = M[i][j - 1] + grid[i][j];
        else if (j == 0 && i != 0)
          M[i][j] = M[i - 1][j] + grid[i][j];
        else
          M[i][j] = min(M[i - 1][j], M[i][j - 1]) + grid[i][j];
      }
    return M.back().back();
  }

  // Space optimization to O(n)
  int minimumPathSum2(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    const int rows = grid.size();
    const int cols = grid[0].size();
    vector<int> M(cols);
    M[0] = grid[0][0];

    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        if (i == 0) {
          if (j != 0)
            M[j] = M[j - 1] + grid[i][j];
        }
        else if (j == 0) {
          if (i != 0)
            M[j] += grid[i][j];
        }
        else {
          M[j] = max(M[j], M[j - 1]) + grid[i][j];
        }

      }
    return M.back();
  }



  // DFS solution (very inefficient!)
  // "12345" is "1" + helper("2345")
  //       plus "12" + helper("345")
  // and we have to check "12" is within 26
  // Why inefficient? To get w(6), we compute w(5) + w(4), and w(5) = w(4) + w(3), so yes, the original fibonacci!
  // Time: O(2^n)
  // (we can add memoization to improve this)
  int decodeWays(string s) {
    int res = decodeWays_helper(s, s.size());
    return res;
  }

  // k: remaining chars to decode
  int decodeWays_helper(string s, int k) {
    if (k == 0) return 1; // "" decoded as ""

    int i = s.size() - k;
    char curr = s[i];
    char next = s[i + 1];

    if (curr == '0') return 0; // "011" cannot be decoded

    int res = decodeWays_helper(s, k - 1);
    if (k >= 2 && (curr == '1' || (curr == '2' && next <= '6')))
      res += decodeWays_helper(s, k - 2);

    return res;
  }

  // DP solution
  // dp size+1 because dp[0] means zero length string
  // so dp[i] is substring at i, including i
  int decodeWays2(string s) {
    vector<int> dp(s.size() + 1, 0);
    dp[0] = 1;
    dp[1] = s[0] == '0' ? 0 : 1;
    for (int i = 2; i <= s.size(); ++i) {
      char curr = s[i - 1];
      char prev = s[i - 2];
      if (curr >= '1')
        dp[i] += dp[i - 1];
      if (prev == '1' || (prev == '2' && curr <= '6'))
        dp[i] += dp[i - 2];
    }
    return dp.back();
  }




  // We pre - compute a 2D bool palindrome helper table for quick lookup : P[i][j] = true meaning substring from i to j is a palindrome, otherwise not
  // Then we form two for loops:
  // 1. j from 0 to size - 1, to define the substring end position
  // 2. i from 0 to j - 1, to define the substring start position
  //
  // Initialize :
  // M[0] = 0 which means an empty string is a palindrome itself
  // Induction rule :
  // M[i] = min{ left | right } out of all possible cuts, where left is the minimum number of cut that can be read from the lookup table, and right has to be a palindrome
  //
  // Time: O(n^2) for both palindrome table buildingand the main function
  // Space: O(n^2)
  int minimumCutsPalindromes(string input) {
    if (input.empty()) return 0;
    const int n = input.size();

    // pre-compute the palindrome table using DP
    vector<vector<bool>> P(n, vector<bool>(n));
    palindromeSubstring_helper(input, P);

    // Physical meaning of M[i]:
    // the minimum number of cuts up to character i (including i)
    vector<int> M(n, 0);
    for (int j = 0; j < n; ++j) {
      if (P[0][j] == true) {
        M[j] = 0;
      }
      else {
        M[j] = INT_MAX;
        // make a cut at every location starting from i to j-1
        // use "左大端右小段"思想
        for (int i = 0; i < j; ++i) {
          if (P[i + 1][j])
            M[j] = min(M[j], M[i] + 1);
        }
      }
    }
    return M.back();
  }

  void palindromeSubstring_helper(string s, vector<vector<bool>>& p) {
    int n = s.size();

    // Fill length of 1
    for (int i = 0; i < n; ++i)
      p[i][i] = true;

    // Fill length of 2
    for (int i = 0; i < n - 1; ++i)
      if (s[i] == s[i + 1])
        p[i][i + 1] = true;

    // Fill length greater than 2
    for (int offset = 2; offset <= n - 1; ++offset) {
      for (int i = 0; i < n - offset; ++i) {
        int j = i + offset;
        if (p[i + 1][j - 1] && s[i] == s[j]) {
          p[i][j] = true;
        }
      }
    }
  }



  // Given [1, 2, 5], minimum amount of coints to make 11
  // Naive solution: we run DFS to try out all combinations, also track a global min
  // Time: O(11^3) - upper bound, assume the smallest coin is 1 cent
  //
  // Better solution: DP
  // 0 1  2  3  4  5  6  7  8  9  10 11
  // 0 12 12 12 12 12 12 12 12 12 12 12
  // 0 1
  //
  // eg. lets fill the amount of 2
  // 1) use 1 as the last coin: min(M[2-1] + 1, 12) = 2   (M.left + 1) vs 12 = 2
  // 2) use 2 as the last coin: min(M[2-2] + 1, 2) = 1    (M.left2 + 1) vs 2 = 1
  // 3) use 5 as the last coin: invalid
  // 0 1  2  3  4  5  6  7  8  9  10 11
  // 0 12 12 12 12 12 12 12 12 12 12 12
  // 0 1  1
  //
  // Lets fill the rest
  // 0 1  2  3  4  5  6  7  8  9  10 11
  // 0 12 12 12 12 12 12 12 12 12 12 12
  // 0 1  1  2  2  1  2  2  3  3  2  3
  int coinChange(vector<int>& coins, int amount) {
    sort(coins.begin(), coins.end()); //for pruning purpose, won't help the worst case, but will help average case
    vector<int> M(amount + 1, amount + 1);
    M[0] = 0;
    for (int i = 0; i <= amount; ++i)
      for (int j = 0; j < coins.size(); ++j)
        if (coins[j] <= i)
          M[i] = min(M[i], M[i - coins[j]] + 1);
        else
          break; // pruning
    return M[amount] > amount ? -1 : M[amount];
  }



  // Now the problem becomes number of unique ways
  // [1, 2, 5] to make 5, how many ways?
  // Naive solution: we run DFS to try out all combinations, also track a global min
  // Time: O(11^3) - upper bound, assume the smallest coin is 1 cent
  // Better solution: DP
  //
  //         0 1 2 3 4 5
  // []                       at each level, we have two choice: we use the new coin, or we do not use the new coin
  // [1]                      if we use the new coin, we pull the number from above
  // [1,2]                    if we do not use the new coin, we pull the number from x cells to the left where x = new coint value
  // [1,2,5]                  then we sum those two numbers together is our answer
  //
  //         0 1 2 3 4 5
  // []      1 0 0 0 0 0      initial column: for 0 amount, we always have 1 way to do it - no use any coins
  // [1]     1                initial row: for not using any coins, we have no way to make up any amount (except for 0 cents)
  // [1,2]   1                
  // [1,2,5] 1                
  //
  //         0 1 2 3 4 5
  // []      1 0 0 0 0 0
  // [1]     1 1 1 1 1 1      for 1 cent: either dont use it (pull above), + do use it (pull left cell)
  // [1,2]   1 1 2 2 3 3      for 2 cent: either dont use it (pull above), + do use it (pull 2 cells left)
  // [1,2,5] 1 1 2 2 3 4      for 5 cent: either dont use it (pull above), + do use it (pull 5 cells left)
  int coinChange2(vector<int>& coins, int amount) {
    if (amount == 0) return 1;
    if (coins.size() == 0) return 0;
    vector<int> M(amount + 1, 0);
    M[0] = 1;
    for (int i = 0; i < coins.size(); ++i)
      for (int j = coins[i]; j <= amount; ++j)
        M[j] += M[j - coins[i]];
    return M.back();
  }



  // On a telephone board, we hop n times, how many times in total
  // 1 2 3
  // 4 5 6
  // 7 8 9
  //   0
  // Naive solution: DFS (can add memo later on for pruning)
  // Time: O(3^n) because we have n level, each node we have at most 3 splits
  // Memo: for number k at level n, how many combinations below this node in the recursion tree
  //
  // Best solution: DP
  // Jump look up table: from key k, what set of v points you can jump to
  // Below: left is lookup table
  // Right: we first fill 1st column with ones, then gradually fill the rest by grabbing answers from its left column
  // 
  //        number\hop 0 1 2 3
  // {0|4,6}     0     1 2 6 12
  // {1|6,8}     1     1 2 5 10
  // {2|7,9}     2     1 2 4 10
  // {3|4,8}     3     1 2 5 10
  // {4|0,3,9}   4     1 3 6 16
  // {5}         5     1 0 0 0
  // {6|0,1,7}   6     1 3 6 16
  // {7|2,6}     7     1 2 5 10
  // {8|1,3}     8     1 2 4 10
  // {9|2,4}     9     1 2 5 10
  int knightDialer(int n) {
    const long long mod = 1e9 + 7;
    const vector<vector<int>> g = { {4,6}, {6,8}, {7,9}, {4,8}, {3,9,0}, {}, {1,7,0}, {2,6}, {1,3}, {2,4} };
    vector<long long> prev(10, 1), curr(10, 0);
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < 10; j++) {
        curr[j] = 0;
        for (auto n : g[j])
          curr[j] += prev[n];
        curr[j] %= mod;
      }
      prev = curr;
    }
    auto ans = accumulate(prev.begin(), prev.end(), 0LL) % mod;
    return ans;
  }



  
  // House robber: nums representing the value of each house, and we cannot rob two houses next to each other
  // What's the max profit?
  // Idea: at each house, we only have two decisions to make: rob, or no rob
  int houseRobber(vector<int>& nums) {
    int rob = 0, noRob = 0;
    for (int i = 0; i < nums.size(); ++i) {
      int preRob = rob, preNotRob = noRob;
      rob = preNotRob + nums[i];
      noRob = max(preRob, preNotRob);
    }
    return max(rob, noRob);
  }



  // Now House Robber 2: all houses are in a cycle
  // Key difference: if we rob the first house, then we cannot rob the last house; vice versa.
  // So we split the problem into two:
  // rob house 0 to n-2, or rob house 1 to n-1
  int houseRobber2(vector<int>& nums) {
    if (nums.size() <= 1) return nums.empty() ? 0 : nums[0];
    return max(houseRobber2_helper(nums, 0, nums.size() - 2),
               houseRobber2_helper(nums, 1, nums.size() - 1));
  }

  int houseRobber2_helper(vector<int>& nums, int left, int right) {
    int rob = 0, noRob = 0;
    for (int i = left; i <= right; ++i) {
      int preRob = rob, preNotRob = noRob;
      rob = preNotRob + nums[i];
      noRob = max(preRob, preNotRob);
    }
    return max(rob, noRob);
  }


  // House robber on a binary tree.
  // 1. no connected nodes should be robbed
  // 2. all non-root nodes strictly have 1 child node (either left for right)
  //
  // Basically you want to compare which one is bigger between:
  //  root + result from your grand child
  //  result from your direct child

  int houseRobber3(TreeNode* root) {
    int robMax = 0, notRobMax = 0;
    return houseRobber3_helper(root, robMax, notRobMax);
  }

  int houseRobber3_helper(TreeNode* root, int& robMax, int& notRobMax) {
    if (!root) return 0;
    int leftRobMax = 0, leftNoRobMax = 0, rightRobMax = 0, rightNoRobMax = 0;

    int leftMax = houseRobber3_helper(root->left, leftRobMax, leftNoRobMax);
    int rightMax = houseRobber3_helper(root->right, rightRobMax, rightNoRobMax);

    robMax = root->value + leftNoRobMax + rightNoRobMax;
    notRobMax = leftMax + rightMax;
    return max(robMax, notRobMax);
  }

  

  // Problem description: split the array into m subarrays, so achieve the "smallest largest" sum 
  // 2D dp table with a prefix sum calculation (to avoid another for loop to constantly adding sums, we will see)
  // We will be using the idea of "左大段右小段", which is 左大段查表，右小段计算
  //
  // Take the input, [7,2,5,10,8], split into 2 groups, what's the minimum largest sum
  // M[i][j]: for nums 0 to j, if I split them into i subarrays, what is my smallest largest sum
  //
  // prefixSum:   7  9  14  24  32
  //      nums:   7  2  5   10  8
  // # groups: 0
  //           1
  //           2
  // Initialize: 0 groups ? all max because we don't have solution
  //             1 number into 2 groups? we can't do that, so we fill Max
  // prefixSum:   7  9  14  24  32
  //      nums:   7  2  5   10  8
  // # groups: 0  M  M  M   M   M
  //           1  7
  //           2  M
  // Now we fill the table
  // Initialize: 0 groups ? all max because we don't have solution
  //             1 number into 2 groups? we can't do that, so we fill Max
  // How to fill the table beyond 1 group?
  //     for each column j, we try make a cut at all the positions from 0 to j - 1
  //     then user the 左大段右小段 principle, read left result from DP table M, read right result from prefixSum, take the max
  //     then for the result from all of those cuts, we take the min
  // prefixSum:   7  9  14  24  32
  //      nums:   7  2  5   10  8
  // # groups: 0  M  M  M   M   M
  //           1  7  9  14  24  32
  //           2  M  7  7   14  18
  // So 18 is our final answer, because [7,2,5] [10,8] split
  int splitArrayLargestSum(vector<int>& nums, int m) {
    const int n = nums.size();
    vector<int> prefixSum(n);
    vector<vector<int>> M(m + 1, vector<int>(n, INT_MAX));

    // compute prefix sum for later use
    prefixSum[0] = nums[0];
    for (int i = 1; i < n; ++i)
      prefixSum[i] = prefixSum[i - 1] + nums[i];

    // 1st row (ie. 1 group) is just the sum
    for (int i = 0; i < n; ++i)
      M[1][i] = prefixSum[i];

    // Fill DP table
    for (int i = 2; i <= m; ++i)
      for (int j = i - 1; j < n; ++j)
        for (int k = 0; k < j; ++k)
          // The DP result from first k items into i-1 groups, and sum of remaining j-k items into one last group, ie group i
          // 左大段右小段：左大段查表，右小段计算
          M[i][j] = min(M[i][j], max(M[i - 1][k], prefixSum[j] - prefixSum[k]));

    return M[m][n - 1];
  }


};
