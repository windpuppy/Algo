#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class TreeNode {
public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

class Array {
public:
  // Merge two sorted arrays
  // Time: O(m+n), Space: O(1)
  vector<int> mergeTwoSortedArrays(vector<int> one, vector<int> two) {
    vector<int> res(one.size() + two.size());
    int i = 0, j = 0, k = 0;

    while (k != res.size()) {
      if (i >= one.size()) res[k++] = two[j++];
      else if (j >= two.size()) res[k++] = one[i++];
      else if (one[i] < two[j]) res[k++] = one[i++];
      else res[k++] = two[j++];
    }

    return res;
  }



  // Merge two sorted arrays, but only take m elements from one, and n from two
  // Note, m and n are not the lenghts of those two arrays.
  // Time: O(m+n), Space: O(1)
  vector<int> mergeTwoSortedArrays2(vector<int> one, int m, vector<int> two, int n) {
    vector<int> res(m + n);
    int i = 0, j = 0, k = 0;

    while (i < m && j < n) {
      if (one[i] <= two[j]) res[k++] = one[i++];
      else res[k++] = two[j++];
    }

    // at this point, at least one of i or j has run out of bound, so we can safely check either
    while (i < m) res[k++] = one[i++];
    while (j < n) res[k++] = two[j++];
    return res;
  }



  // no duplicates
  // push them into two maps
  vector<int> commonNumbersOfTwoArrays(vector<int> a, vector<int> b) {
    map<int, int> map;
    for (auto n : a) map[n]++;
    for (auto n : b) map[n]++;

    vector<int> res;
    for (auto it = map.cbegin(); it != map.cend(); ++it)
      if (it->second > 1)
        res.push_back(it->first);
    return res;
  }



  // with duplicates
  // push them into two maps
  vector<int> commonNumbersOfTwoArrays2(vector<int> a, vector<int> b) {
    map<int, int> map1;
    for (auto n : a) map1[n]++;
    map<int, int> map2;
    for (auto n : b) map2[n]++;
    vector<int> res;
    for (auto it = map1.cbegin(); it != map1.cend(); ++it) {
      int key = it->first;
      int val = it->second;
      if (map2.count(key)) {
        int val2 = map2[key];
        res.insert(res.end(), min(val, val2), key);
      }
    }
    return res;
  }



  // with duplicates, output unique elements
  // push them into two sets
  vector<int> commonNumbersOfTwoArrays3(vector<int>& a, vector<int>& b) {
    unordered_set<int> set1(a.begin(), a.end());
    unordered_set<int> set2(b.begin(), b.end());

    vector<int> res;
    for (auto it = set1.cbegin(); it != set2.cend(); ++it) {
      int key = *it;
      if (set2.count(key))
        res.push_back(key);
    }
    return res;
  }



  /// 3 -> III, 4 -> IV, 9 -> IX
  // Note: start trying from the largest number: 1000
  string intToRoman(int number) {
    vector<int> num = { 1,4,5,9,10,40,50,90,100,400,500,900,1000 };
    vector<string> sym = { "I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M" };
    const int size = 13;
    string out;
    for (int i = size - 1; i >= 0; --i) {
      int div = number / num[i];
      number = number % num[i];
      while (div-- > 0)
        out += sym[i];
    }
    return out;
  }



  // Note: scan the string from right to left
  // Hit a smaller numter? sum minus; hit a larger or equal number, sum plus
  int romanToInt(string s) {
    unordered_map<char, int> m = { { 'I' , 1 },
                                   { 'V' , 5 },
                                   { 'X' , 10 },
                                   { 'L' , 50 },
                                   { 'C' , 100 },
                                   { 'D' , 500 },
                                   { 'M' , 1000 } };

    int sum = m[s.back()];
    for (int i = s.length() - 2; i >= 0; --i) {
      if (m[s[i]] < m[s[i + 1]])
        sum -= m[s[i]];
      else
        sum += m[s[i]];
    }

    return sum;
  }



  // Naive method: sort the array first, use two pointers from each side
  // Better solution: use hashset
  // Time: O(n)
  // space: O(n)
  // 
  // Note: typical two sum problems can also use sort + two pointers method, Time O(nlogn), but Space O(1) - eg. heap sort
  bool TwoSum(vector<int> nums, int target) {
    unordered_set<int> set;

    for (auto n : nums) {
      if (set.find(target - n) != set.end()) return true;
      set.insert(n);
    }
    return false;
  }



  // Return one index pair
  vector<int> TwoSum2(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); ++i) {
      int needed = target - nums[i];
      if (!map.count(needed))
        map.insert({ nums[i], i });
      else
        return vector<int>{map[needed], i};
    }
    return vector<int>();
  }



  // No need to dedup result
  // User a book to record <i, vector<all i's locations>>
  vector<vector<int>> TwoSumAllPairs(vector<int> input, int target) {
    vector<vector<int>> res;
    unordered_map<int, vector<int>> map; //<i, vector<all i's locations>>

    for (int i = 0; i < input.size(); ++i) {
      if (map.count(target - input[i])) {
        auto indices = map[target - input[i]];
        for (auto j : indices)
          res.push_back(vector<int>{j, i});
      }

      // do this regardless
      map[input[i]].push_back(i);
    }
    return res;
  }



  // Need to dedup result
  // Use one set to record i, another to record all visited & qualified pairs so we don't repeat
  // Potential space optimization:
  //   check map<int, count>, if count > 1, then skip
  //   https://docs.google.com/document/d/1Kh1KP02TH1j-Lcjuntr0V0xTkglENgRggZ3iV79xsoQ/edit
  vector<vector<int>> TwoSumAllPairs2(vector<int> input, int target) {
    vector<vector<int>> res;
    unordered_set<int> set;
    unordered_set<int> visited;

    for (auto n : input) {
      if (visited.count(n))
        continue;

      // A qualified pair? Push to result, and mark it "visited"
      if (set.count(target - n)) {
        res.push_back(vector<int>{n, target - n});
        visited.insert(n);
        visited.insert(target - n);
      }
      else {
        set.insert(n);
      }
    }
    return res;
  }



  // Sort + two pointers
  // Time: Sorting O(nlogn), plus O(n) single while loop, so it's O(nlogn)
  // Space: depending on the sorting, O(1) for heapsort, but we assume O(n) for mergesort, or O(logn) for quicksort
  vector<int> TwoSumClosest(vector<int> input, int target) {
    sort(input.begin(), input.end());
    vector<int> res(2);
    int minDiff = INT_MAX;
    int i = 0, j = input.size() - 1;

    while (i < j) {
      int diff = target - (input[i] + input[j]);
      if (diff == 0) {
        res[0] = input[i];
        res[1] = input[j];
        return res;
      }
      else {
        if (abs(diff) < minDiff) {
          minDiff = abs(diff);
          res[0] = input[i];
          res[1] = input[j];
        }

        if (diff > 0)
          i++;
        else
          j--;
      }
    }
    return res;
  }



  // Count 2sum pairs smaller than target
  // For each i,j pair, if sum < target, elements from i to j-1 all form valid pairs
  // Time: O(nlogn) because of sorting, Space: O(1)
  int TwoSumSmaller(vector<int> nums, int target) {
    sort(nums.begin(), nums.end());
    int i = 0, j = nums.size() - 1, count = 0;
    while (i < j) {
      if (nums[i] + nums[j] < target)
        count += j - i++;
      else
        j--;
    }
    return count;
  }



  // Return the largest sum smaller than target
  int TwoSumSmaller2(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int i = 0, j = nums.size() - 1, max = INT_MIN;
    while(i < j) {
      int sum = nums[i] + nums[j];
      if (sum < target && sum > max)
        max = sum;

      if (sum < target) i++;
      else j--;
    }
    return max;
  }



  // Two sum, pick one from each array
  // Hashset a, check b against it
  bool TwoSumTwoArrays(vector<int> a, vector<int> b, int target) {
    unordered_set<int> set;
    for (auto i : a)
      set.insert(i);

    for (auto j : b)
      if (set.find(target - j) != set.end())
        return true;

    return false;
  }



  // Two sum in BST
  // Time: O(n)
  // Space: O(height)
  // Note: we can not use the BST property to go left and right, we have to search both subtree, because tree might contain negative elements
  bool TwoSumBST(TreeNode* root, int target) {
    if (!root) return false;
    unordered_set<int> set;
    return TwoSumBST_helper(root, target, set);
  }

  bool TwoSumBST_helper(TreeNode* root, int target, unordered_set<int>& set) {
    if (!root) return false;
    if (set.count(root->value)) return true;
    set.insert(target - root->value);
    return TwoSumBST_helper(root->left, target, set) ||
           TwoSumBST_helper(root->right, target, set);
  }



  // Return 3 Sum, no duplicates
  // Solution:
  //   1. sort
  //   2. pick i, use two pointers to run TwoSun in the rest elements
  //   3. dedup i as well
  // Time: O(n^2)
  vector<vector<int>> ThreeSum(vector<int> nums, int target) {
    vector<vector<int>> res;
    const int size = nums.size();
    sort(nums.begin(), nums.end());

    for (int k = 0; k < size; ++k) {
      int targetSum = target - nums[k];
      int i = k + 1;
      int j = size - 1;

      while (i < j) {
        if (nums[i] + nums[j] < targetSum)
          i++;
        else if (nums[i] + nums[j] > targetSum)
          j--;
        else {
          res.push_back(vector<int>{nums[k], nums[i], nums[j]});

          int front = nums[i++];
          while (i < j && nums[i] == front) i++; // dedup i

          int back = nums[j--];
          while (i < j && nums[j] == back) j--; // dedup j
        }
      }

      while (k + 1 < size && nums[k + 1] == nums[k]) k++; // dedup n
    }

    return res;
  }



  // Similar to 2 sum 2 arrays
  // Hash a, use double for loop on b and c, check 2 sum against a
  bool ThreeSumThreeArrays(vector<int> a, vector<int> b, vector<int> c, int target) {
    unordered_set<int> set;
    for (auto n : a)
      set.insert(n);

    for (auto i : b)
      for (auto j : c)
        if (set.count(target - i - j))
          return true;
    return false;
  }



  // We look pair by pair
  // First we use double i,j for loops to get the first pair
  // For each (i, j), we look towards the left (in hashmap) to see if we can find a matching pair
  // Note: hashmap should only store the left-most pair of the same value, so that we don't wrongly use the same number twice
  // Time: O(n^2)
  bool FourSum(vector<int> nums, int target) {
    unordered_map<int, int> map; // <2sum, right index of that 2sum pair>
    // pair(j, i) is considered the "right pair", we look to its left to find the other 2sum
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        int sum2 = nums[j] + nums[i];

        if (map.count(target - sum2) && map[target - sum2] < j)
          return true;

        // for all the pairs with the same value, only store the left most pair
        else if (!map.count(sum2))
          map[sum2] = i;
      }
    }
    return false;
  }



  // Two pointers
  // if a - b > target, move a; otherwise, move b
  vector<int> TwoDiff(vector<int> arr, int target) {
    const int size = arr.size();
    int i = 0;
    int j = 1;
    while (i < size && j < size) {
      if (i != j && arr[j] - arr[i] == target) return vector<int>{i, j};
      else if (arr[j] - arr[i] < target) j++;
      else i++;
    }

    i = size - 1;
    j = size - 2;
    while (i >= 0 && j >= 0) {
      if (i != j && arr[j] - arr[i] == target) return vector<int>{i, j};
      else if (arr[j] - arr[i] > target) j--;
      else i--;
    }

    return vector<int>();
  }



  // Longest subarray sum k
  // Global var: maxLen, rolling sum, hash<sum, index>
  // Iterate 0 ~ n-1, 
  //   1) if sum == k, maxLen = i + 1
  //   2) if sum not in hash, record it with index
  //   3) check if sum - k is in the hash, if yes, get its index, and update maxLen with i - index
  //       (meaning: if we get rid of everything before that index, we will have our target sum, so lets update the global maxLen)
  // Time O(n)
  // Space O(n)
  int longestSubArraySumK(vector<int> nums, int k) {
    int maxLen = 0, sum = 0;
    unordered_map<int, int> map;

    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];

      if (sum == k)
        maxLen = i + 1; // 0 ~ i must be the longest so far

      if (!map.count(sum))
        map[sum] = i; // only record the first occurence, because we need "longest subarray"

      int needed = sum - k;
      if (map.count(needed)) {
        int newLen = i - map[needed];
        maxLen = max(maxLen, newLen);
      }
    }

    return maxLen;
  }



  // Solve without division, and in O(n)
  // Build a vector LEFT, records the product of i (not including i)
  // Do the same for RIGHT
  // LEFT * RIGHT is the output
  vector<int> productExceptSelf(vector<int> nums) {
    const int size = nums.size();

    vector<int> left(size, 1);
    for (int i = 1; i < size; ++i)
      left[i] = left[i - 1] * nums[i - 1];

    vector<int> right(size, 1);
    for (int i = size - 2; i >= 0; --i)
      right[i] = right[i + 1] * nums[i + 1];

    vector<int> res(size);
    for (int i = 0; i < size; ++i)
      res[i] = left[i] * right[i];
    return res;
  }



  // Celebrity problem
  int celebrity(vector<vector<int>> input) {
    if (input.empty() || input[0].empty()) return -1;
    const int size = input.size();

    // initialize two person from two ends
    int a = 0;
    int b = size - 1;

    // rule out non-celebrities
    while (a < b)
      if (input[a][b]) a++; // if a knows b, a cannot be celebrity
      else b--;  // if a does not know b, b cannot be celebrity

    // All excluded, only a remains to be investigated
    for (int i = 0; i < size; ++i)
      if (i == a) continue; // cannot check against a himself
      else if (input[a][i] || !input[i][a]) return -1; // if a knows i, or i doesn't know a, then a is not a celebrity

    return a;
  }



  vector<int> getCountArray(vector<int> input) {
    //vector<pair<int, int>> temp;
    //int count = 0;
    //for (auto n : input)
    //  temp.push_back({ n, count++ });

    //sort(temp.begin(), temp.end());

    return vector<int>{};
  }



  // do pair comparisons, split the number into 2 groups: winners and losers - n/2 comparisons
  // find the max from the winners - n/2-1 comparisons
  // find the min from the losers - n/2-1 comparisons
  // Total: n/2 + n/2-1 + n/2-1 = 1.5n - 2
  vector<int> largestAndSmallest(vector<int> input) {
    const int n = input.size();

    for (int i = 0; i < n / 2; ++i)
      if (input[i] < input[n - 1 - i])
        swap(input[i], input[n - 1 - i]);

    int mid = (n - 1) / 2;
    int large = input[0];
    for (int i = 1; i <= mid; ++i)
      large = max(large, input[i]);

    int midNext = n / 2;
    int small = input[midNext];
    for (int i = midNext + 1; i <= n - 1; ++i)
      small = min(small, input[i]);

    return vector<int>{large, small};
  }



  // Least times of comparison
  // Implementation: "world cup" knockout stage
  vector<int> largestAndSecondLargest(vector<int> input) {
    int a = 0, b = 0;
    return vector<int>{a, b};
  }



  // Least swaps to make it ascending
  // Sort, record everyone's "correct" position, gradually swap
  int leastSwaps(vector<int> a) {
    const int size = a.size();
    int res = 0;

    vector<pair<int, int>> vec(size); // value, index
    for (int i = 0; i < size; ++i)
      vec[i] = { a[i], i };

    sort(vec.begin(), vec.end());

    int i = 0;
    while (i < size) {
      // already in the correct position? do nothing
      if (vec[i].second == i) {
        i++;
        continue;
      }

      // otherwise, swap it to the position it belongs it
      int targetPos = vec[i].second;
      swap(vec[i], vec[targetPos]);
      res++;
    }
    return res;
  }



  // Least swap from one[i] to two[i], to make both strictly ascending
  // DP solution
  // index               0    1    2    3
  // one                 1    3    5    4
  // two                 1    2    3    7
  //
  // swap                1    1    2    1
  // fix                 0    0    0    2
  // swap[i] means for the ith element in A and B, the minimum swaps if we swap A[i] and B[i]
  // fix[i] means for the ith element in A and B, the minimum swaps if we do NOT swap A[i] and B[i]
  int leastSwaps2(vector<int>& one, vector<int>& two) {
    int n = one.size();
    vector<int> fix(n, 0), swap(n, 0);
    swap[0] = 1;
    fix[0] = 0;
    for (int i = 1; i < one.size(); ++i) {
      if (one[i - 1] >= one[i] || two[i - 1] >= two[i]) { // must swap
        swap[i] = fix[i - 1] + 1;
        fix[i] = swap[i - 1];
      }
      else if (one[i - 1] >= two[i] || two[i - 1] >= one[i]) { // either swap prev and swap current, or fix both
        swap[i] = swap[i - 1] + 1;
        fix[i] = fix[i - 1];
      }
      else { // don't care
        swap[i] = min(swap[i - 1], fix[i - 1]) + 1;
        fix[i] = min(swap[i - 1], fix[i - 1]);
      }
    }

    return min(swap[n - 1], fix[n - 1]);
  }



  // Naive solution 1: combine all arrays, and sort one big array, O(nklognk)
  // Naive solution 2: Combine 1 and 2, then with 3, etc. iterate through all arrays, O(nk)
  // Another solution: combine 12, 34, etc. then 1234, 5678, etc.
  // Efficient solution: use heap
  // Push all 1st elements into the heap, extra min, then push one more from the array that extracted element is from
  // Time O(nlogk)
  typedef pair<int, pair<int, int>> ppi;
  vector<int> mergeKSortedArrays(vector<vector<int>> arrays) {
    // pair(val, pair(array index, index in array))
    priority_queue<ppi, vector<ppi>, greater<ppi>> minHeap;
    for (int i = 0; i < arrays.size(); ++i)
      if (!arrays[i].empty())
        minHeap.push({ arrays[i][0], { i, 0 } });

    vector<int> out;
    while (!minHeap.empty()) {
      auto curr = minHeap.top();
      minHeap.pop();
      out.push_back(curr.first);

      int i = curr.second.first; // i-th array
      int j = curr.second.second + 1; // j-th element
      if (j < arrays[i].size())
        minHeap.push({ arrays[i][j], {i, j} });
    }
    return out;
  }



  // Use a deque to record the indices, make sure:
  // 1) the front of the deque is always the max value
  //      Because for any incoming a[i], for its lifetime in the sliding window, any smaller numbers in that window DON'T MATTER
  // 2) deque only contains indices from current sliding window
  // eg.
  // --->
  // [1, 2, 3]: gradualy throw away 1, 2, only keep 3 in the queue
  // [3, 2, 1]: incoming 2, we throw away 1 and 2 in the deque, push 2, so it becomes [3, 2]
  //
  // Time space analysis (somewhat complicated)
  // Amortized for each move O(1)
  // Worst case for each move O(k)
  // Time for all moves O(n)
  // Space: easy, O(k)
  vector<int> maxValueOfSizeKSlidingWindows(vector<int> a, int k) {
    vector<int> res;
    deque<int> q;
    for (int i = 0; i < a.size(); ++i) {
      // throw away any smaller values on the right
      // Because for a[i], for its lifetime in the sliding window, any smaller numbers in that window DON'T MATTER
      while (!q.empty() && a[q.back()] <= a[i])
        q.pop_back();

      // even if the left head element is a max (it will surivie the above "throwing" process)
      //    it still needs to go if it moves out of the sliding window
      if (!q.empty() && q.front() <= i - k)
        q.pop_front();

      q.push_back(i);

      // start recording when i is beyond k
      if (i >= k - 1) {
        int val = a[q.front()];
        res.push_back(val);
      }
    }
    return res;
  }



  // Sorted, keep 1 of the dups
  vector<int> arrayDedup(vector<int> nums) {
    int size = nums.size();
    if (size <= 1) return nums;

    // s
    // 1 2 2 3
    //   f
    int slow = 0;
    for (int fast = 1; fast < size; ++fast) {
      if (nums[fast] != nums[fast - 1]) {
        nums[++slow] = nums[fast];
      }
    }

    nums.resize(slow + 1);
    return nums;

    //// Better solution:
    //int slow = 0;
    //for (auto n : nums)
    //  if (slow < 2 || n != nums[slow - 2]) // look back by 2
    //    nums[slow++] = n;

    //nums.resize(slow);
    //return nums;
  }



  // Sorted, keep 2 of the dups
  // For this solution, our slow and fas are not "conventional" slow faster pointers
  // Instead of looking for 2+ number of strings, we use reverse thinking: what happens if we have 3-peat chars?
  // 1 2 2 2 3 3
  //       | |
  //       s f
  // In this case, instead of fast looking back, we make slow look back.
  // If (slow sees a same char), slow stays, move fast.
  // Else, overwrite slow
  vector<int> arrayDedup2(vector<int> nums) {
    int slow = 0;
    for (int fast = 0; fast < nums.size(); fast++)
      if (slow < 2 || nums[fast] > nums[slow - 2])
        nums[slow++] = nums[fast];
    nums.resize(slow);
    return nums;
  }



  // Sorted, remove all duplicates: 122233 -> 1
  // Key: track how many dups we have seen?
  // one 1, three 2s, two 3s -- do something about the 2s and 3s
  vector<int> arrayDedup3(vector<int> nums) {
    int size = nums.size();
    if (size <= 1) return nums;

    int slow = 0, fast = 0;
    int count = 0;
    while (fast < size) {
      if (nums[slow] == nums[fast]) {
        fast++;
        count++;
      }
      else {
        if (count == 1)
          slow++;
        nums[slow] = nums[fast];
        count = 0;
      }
    }

    // Edge case: if last char is unique, we need to include it (slow will not reach there)
    if (count == 1)
      slow++;

    nums.resize(slow);
    return nums;
  }



  // Unsorted, dedup: 12233322 -> 1
  // Use a stack, but implement it as deque so that it's more convenient for output
  // Rules: 1. always push new value regardless
  //        2. if seeing dups (that means the number just pushed into the stack need to be removed), keep skipping dups, then pop the stack
  vector<int> arrayDedup4(vector<int> nums) {
    int size = nums.size();
    if (size <= 1) return nums;

    deque<int> s;
    s.push_back(nums.front());

    int i = 1;
    while (i < size) {
      if (s.empty() || nums[i] != s.back()) { // remember to check for empty stack!
        s.push_back(nums[i]);
      }
      else {
        while (i + 1 < size && nums[i] == nums[i + 1])
          i++;
        s.pop_back();
      }
      i++;
    }

    return vector<int>(s.begin(), s.end());
  }



  // Main logic is to compute the "all" array - find all its element's next great to the right
  // We scan from right to left, and use a stack to save the "next greater" element so far on the right
  // For each curr element, we compare it against stack top;
  // 1. if curr is greater? pop everything smaller, and push curr into the stack top
  // 2. then the stack top is the "next great", or no "next great" if stack is empty
  //
  // Why stack??? because next greater means we look towards the right, and we only care about the CLOSEST greater element
  // So when we scan from right to left, we throw away the FARTHER greater elements, so we use stack!
  vector<int> nextGreater(vector<int> partial, vector<int> all) {
    const int n = all.size();
    stack<int> stack; // stack of values
    vector<int> nextGreater(n); // vector of values
    unordered_map<int, int> map; // simply for book keeping, key: element value, value: index

    for (int i = n - 1; i >= 0; --i) {
      int curr = all[i];
      map[curr] = i;

      // throw away all smaller values in stack
      while (!stack.empty() && curr > stack.top())
        stack.pop();

      // stack top is the "next greater", or not found
      nextGreater[i] = stack.empty() ? -1 : stack.top();
      stack.push(curr);
    }

    vector<int> out;
    for (auto p : partial)
      out.push_back(nextGreater[map[p]]);
    return out;
  }



  // Very similar to Next Greater I problem, excep this time the input array is circular
  // [4, 2, 1, 3] => [-1, 3, 3, 4]
  vector<int> nextGreater2(vector<int> nums) {
    const int size = nums.size();
    stack<int> stack;
    vector<int> nextGreater(nums.size());

    for (int i = size - 1; i >= 0; i--) {
      int curr = nums[i];
      while (!stack.empty() && curr > stack.top())
        stack.pop();

      if (stack.empty()) {
        // because it's a circular array, we need to do a full new search from the begining
        bool found = false;
        for (int j = 0; j < i; j++) {
          if (nums[j] > curr) {
            nextGreater[i] = nums[j];
            found = true;
            break;
          }
        }

        if (!found) nextGreater[i] = -1;
      }
      else {
        nextGreater[i] = stack.top();
      }

      stack.push(curr);
    }
    return nextGreater;
  }



  // Given n, find the smallest larger number with the same digits
  // 1 => none, 12 => 21, 21 => none
  // Observations:
  //   for example 13542, we scan from right to left
  //   we need to find minimum one dip, because if it's always ascending towards left, we will not have a valid solution
  //   once we see a dip, we fill it with the SMALLEST LARGER on the right, then sort the right part
  // 1) 13|542 - detect 5->3 first dip
  // 2) 14|532 - swap 3 with SMALLEST GREATER value on the right, which is 4
  // 3) 14|235 - sort right part
  int nextGreater3(int n) {
    if (n == INT_MAX) return -1; // overflow
    stack<int> stack;  while (n > 0) { stack.push(n % 10); n /= 10; }
    vector<int> nums;  while (!stack.empty()) { nums.push_back(stack.top()); stack.pop(); }
    const int size = nums.size();
    if (size <= 1) return -1;

    // 1) find first dip
    int i = size - 1;
    while (i > 0)
      if (nums[i] > nums[i - 1]) break;
      else i--;
    if (i == 0) return -1; // if all descending, no possible solution

    // 2) find the SMALLEST LARGER on the right
    int curr = nums[i - 1];
    int min = i;
    for (int j = i + 1; j < size; ++j)
      if (nums[j] > curr&& nums[j] < nums[min])
        min = j;
    swap(nums[i - 1], nums[min]);

    // 3) sort the right part
    sort(nums.begin() + i, nums.end());

    // output - watch out for overflow!
    long sum = 0;
    for (auto i : nums) {
      sum = sum * 10 + i;
      if (sum > INT_MAX)
        return -1;
    }
    return (int)sum;
  }



  // Find if there is a subarray sum equal to target
  // Here we need to handle negative values, so we cannot use conventional two pointer method to solve this
  // We use a map
  // Time O(n)
  bool subArraySumToTarget(vector<int> a, int k) {
    if (a.empty()) return false;
    else if (a.size() == 1) return a[0] == k;
    unordered_set<int> set;
    int sum = 0;
    for (auto n : a) {
      sum += n;
      if (sum == k) return true;
      if (set.count(sum - k)) return true;

      set.insert(sum);
    }
    return false;
  }



  // Same as above, but return the number of such subarrays
  // So instead of using a set to track each sum's existence, we use a map to track its occurrences
  int subArraySumToTarget2(vector<int> a, int k) {
    if (a.empty()) return false;
    else if (a.size() == 1) return a[0] == k;
    unordered_map<int, int> map;
    int count = 0;
    int sum = 0;
    for (auto n : a) {
      sum += n;
      if (sum == k) count++;
      if (map.count(sum - k)) count += map[sum - k];

      map[sum]++;
    }
    return count;
  }



  // The smallest subarray with the sum >= k, and return its length
  // Assumption: all nums and k are positive
  // Solution: we use two pointers and maintain a sliding window with its sum floating equal or above k
  int minimumSizeSubarraySum(vector<int> nums, int k) {
    int sum = 0, globalMin = INT_MAX;
    int i = 0, j = 0;
    for (j = 0; j < nums.size(); j++) {
      sum += nums[j];
      if (sum < k) continue;

      while (sum >= k) {
        globalMin = min(globalMin, j - i + 1);
        sum -= nums[i++];
      }
    }
    return globalMin == INT_MAX ? 0 : globalMin;
  }



  // Find two disjoint subarrays with the max absolute difference of their sum, return that diff
  // Input: { 1, -3, 1, -4, 3, 4 }
  // Two subarrays : {-3, 1, -4 }, { 3, 4 }
  // Maximum difference = 13
  int maxSubarraySumDifference(vector<int> nums) {
    const int n = nums.size();
    vector<int> leftMax(n), rightMax(n), leftMin(n), rightMin(n);

    maxSubarraySumLeft(nums, leftMax);
    maxSubarraySumRight(nums, rightMax);

    for (auto n : nums) n *= -1;
    maxSubarraySumLeft(nums, leftMin); for (auto n : leftMin) n *= -1;
    maxSubarraySumRight(nums, rightMin); for (auto n : rightMin) n *= -1;

    // then for each i, the mmax diff = max(max(leftmax - right min), max(leftmin - rightmax))
    int globalMax = INT_MIN;
    for (int i = 0; i < n - 1; ++i) {
      int maxDiff = max(abs(leftMax[i] - rightMin[i]), abs(leftMin[i + 1] - rightMax[i + 1]));
      globalMax = max(globalMax, maxDiff);
    }
    return globalMax;
  }

  // DP helper
  void maxSubarraySumLeft(vector<int> a, vector<int>& left) {
    int currMax = a[0], maxSoFar = a[0];
    left[0] = a[0];
    for (int i = 1; i < a.size(); ++i) {
      currMax = max(currMax + a[i], a[i]); // east mountain again up
      maxSoFar = max(maxSoFar, currMax);
      left[i] = maxSoFar;
    }
  }

  // DP helper
  void maxSubarraySumRight(vector<int> a, vector<int>& right) {
    const int n = a.size();
    int currMax = a[n - 1], maxSofar = a[n - 1];
    right[n - 1] = a[n - 1];
    for (int i = n - 1; i >= 0; --i) {
      currMax = max(currMax + a[i], a[i]);
      maxSofar = max(maxSofar, currMax);
      right[i] = maxSofar;
    }
  }



  // maximum sum subsequence with no adjacent values
  // DP solution
  int maxSumSubsequenceNoAdjacent(vector<int> nums) {
    int incl = nums[0];
    int excl = 0;
    int i;

    for (i = 1; i < nums.size(); i++) {
      // current max excluding i
      int excl_curr = max(incl, excl);

      // current max including i
      incl = excl + nums[i];
      excl = excl_curr;
    }

    // return max of incl and excl
    return max(incl, excl);
  }



  // Split array into two, two sides equal to the same sum
  // Naive solution: split into two, compare sum, move left / right
  // DFS solution: for each number, we have two choices: we take this number into the current group, or we don't take this number
  //     if we take this number, remember to accmmulate the sum and bring it to the next level
  bool partitionEqualSubsetSum(vector<int>& nums) {
    int total = 0;
    for (auto n : nums)
      total += n;

    if (total % 2 != 0) return false; // early termintation

    return canPartition(nums, 0, 0, total);
  }

  bool canPartition(vector<int>& nums, int index, int sum, int total) {
    if (sum * 2 == total)
      return true;

    if (sum > total / 2 || index >= nums.size()) // sum already passed total/2, or numbers are used up? no good.
      return false;

    return canPartition(nums, index + 1, sum, total) ||
           canPartition(nums, index + 1, sum + nums[index], total);
  }

  // Improvement for above with memo
  bool partitionEqualSubsetSum2(vector<int>& nums) {
    int total = 0;
    for (auto n : nums)
      total += n;

    if (total % 2 != 0) return false; // early termintation

    unordered_map<string, bool> map;
    return canPartition2(nums, 0, 0, total, map);
  }

  bool canPartition2(vector<int>& nums, int index, int sum, int total, unordered_map<string, bool>& map) {
    string curr = index + " " + sum; // current state
    if (map.count(curr)) return map[curr]; // already found? return it

    if (sum * 2 == total)
      return true;

    if (sum > total / 2 || index >= nums.size())
      return false;

    bool foundPartition = canPartition2(nums, index + 1, sum, total, map) ||
                          canPartition2(nums, index + 1, sum + nums[index], total, map);

    // store new entry
    map[curr] = foundPartition;
    return foundPartition;
  }



  // Equal sum partitions
  // Given an array of numbers, partition it into multiple subarrays of equal sum
  //   return the smallest possible sum (not the fewest partitions!)
  // Here we use DFS
  // Time: O(n^2)
  int minEqualSumPartition(vector<int> nums) {
    const int size = nums.size();
    int partSum = 0;
    
    // Because we want smallest possible equal sum, we start trying from 1st element only, then first 2 elements, and so on
    for (int i = 0; i < size; ++i) {
      partSum += nums[i]; // sum of the current partition
      if (i == size - 1)
        return partSum;

      if (equalSum_helper(nums, i + 1, partSum))
        return partSum;
    }
    return partSum;
  }

  bool equalSum_helper(vector<int> nums, int index, int partSum) {
    const int size = nums.size();
    if (index == size) return true;

    int sum = 0;
    while (index < size) {
      sum += nums[index++];
      if (sum >= partSum)
        break;
    }
    
    if (sum != partSum) return false; // cannot find the solution (note, it's possible currSum < partSum, e.g. final item is not big enough)
    return equalSum_helper(nums, index, partSum);
  }



  // Asteroids Collision problem
  // For example: [5, -10, 5] ==> output will be [-5, 5], because -10 moves left, 5 and 5 move right
  //              [5, 5, -10] ==> output will be [-10], because -10 will destroy both 5s
  // Consider '-' is moving left, '+' is stationary
  // Output will have to be [-, -, -, ..., +, +, +]
  // Solution:
  // For any + value, always put into the stack
  // For any - value, case 1: stack empty / stack top is minus: push
  //                  case 2: stack top is plus: go through the stack and simulate
  // Time complexity: O(n)
  // Space complexity: O(n)
  vector<int> asteroidCollision(vector<int> asteroids) {
    vector<int> s; // we can use a vector to simulate stack here
    for (int i = 0; i < asteroids.size(); ++i) {
      const int curr = asteroids[i];
      // All positive asteroids, push to the stack
      if (curr > 0) {
        s.push_back(curr);
        continue;
      }

      // Negative ones? two cases
      if (s.empty() || s.back() < 0) // ..., -2] -3
        s.push_back(curr);
      else if (abs(s.back()) <= abs(curr)) {
        if (abs(s.back()) < abs(curr)) --i; // ..., 2] -3 ==> my current -3 is still alive
        s.pop_back(); // ..., 2] gonna have to pop that 2 anyway
      }
      // else ..., 2] -1 ==> do nothing, as -1 will be absorbed
    }
    return s;
  }
};

