#pragma once

#include "../Common/Common.h"

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class DFS
{
public:

  // DFS solution
  // Time: O(2^n) - total number of nodes
  // Space O(n) - n extra space for result, logn recursion stack can be ignored because O(n) dominates
  vector<string> subsets(string input) {
    if (input.empty()) return vector<string>{""};
    string out;
    vector<string> res;
    subsets_dfs(input, 0, out, res);
    return res;
  }

  void subsets_dfs(const string& input, int index, string& out, vector<string>& res) {
    if (index == input.size()) {
      res.push_back(out);
      return;
    }

    // We pick 'a'
    out += input[index];
    subsets_dfs(input, index + 1, out, res);
    out.pop_back();

    // We don't pick 'a'
    subsets_dfs(input, index + 1, out, res);
  }

  // BFS solution:
  // Time: O(2^n)
  // Space: O(2^(n+1))
  vector<string> subsets_bfs(string input) {
    if (input.empty()) return vector<string>{""};
    vector<string> res;
    queue<string> q;
    q.push("");
    while (!q.empty()) {
      string curr = q.front();
      q.pop();
      res.push_back(curr);

      for (auto c : input)
        if (curr.empty() || curr.back() < c)
          q.push(curr + c);
    }
    return res;
  }

  // Bitwise solution
  // Time: O(2^n * n)
  // Space: O(n)
  vector<string> subsets_bitwise(string input) {
    if (input.empty()) return vector<string>{""};
    vector<string> res;
    const int size = input.size();
    const int len = pow(2, size);

    for (int i = 0; i < len; ++i) {
      string out;
      int b = i;
      for (int j = 0; j < size; ++j) {
        if (b & 1)
          out += input[j];
        b >>= 1;
      }
      res.push_back(out);
    }
    return res;
  }



  // All sorted subsets, input contains duplicates, but ouput needs to be unique
  // e.g. 122 => 1, 2, 122, 22, 12, []
  //
  //              /          \
  // for 1       1           {}
  //          /     \       /   \
  // for 2   12       1     2    {}
  //        / \   |  / \   / \   / \
  // for 2 122 12 |(12) 1 22 2 (2) {}
  //              |
  //            dedup "2" at this point
  // Time: O(2^n)
  vector<string> subsets2(string input) {
    if (input.empty()) return vector<string>{""};
    string out;
    vector<string> res;
    sort(input.begin(), input.end()); // Sort for easier dedup later
    subsets2_dfs(input, 0, out, res);
    return res;
  }

  void subsets2_dfs(const string& input, int index, string& out, vector<string>& res) {
    // Base case
    const int size = input.length();
    if (index == size) {
      res.push_back(out);
      return;
    }

    // We pick 'a'
    out += input[index]; // "eat"
    subsets2_dfs(input, index + 1, out, res);
    out.pop_back(); // "spit"

    // dedup - skip repeating chars
    while (index < size - 1 && input[index] == input[index + 1])
      index++;

    // We don't pick 'a'
    subsets2_dfs(input, index + 1, out, res);
  }



  // All subsets of k size
  vector<string> subsetsOfK(string input, int k) {
    const int size = input.length();
    if (size == 0 && k == 0) return vector<string>{""};
    else if (size == k) return vector<string>{input};
    else if (size < k) return vector<string>();

    string out;
    vector<string> res;
    subsetsOfK_dfs(input, 0, k, out, res);
    return res;
  }

  void subsetsOfK_dfs(const string& input, int index, int k, string& out, vector<string>& res) {
    if (index == input.length()) {
      if (k == out.length())
        res.push_back(out);
      return;
    }

    // 1. do pick the current char
    if (out.size() <= k - 1) { // pruning
      out += input[index];
      subsetsOfK_dfs(input, index + 1, k, out, res);
      out.pop_back();
    }

    // 2. do not pick the current char
    if (out.size() <= k) // pruning
      subsetsOfK_dfs(input, index + 1, k, out, res);

    // Note: 1 and 2 above are inter-changeable
  }



  // same as above, just with n instead of vector<int> as input
  // all subsets of size k, for integers 1 ~ n
  vector<vector<int>> subsetsOfK_nums(int n, int k) {
    vector<vector<int>> res;
    if (n == 0 || k == 0 || n < k) return res;

    vector<int> nums(n);
    for (int i = 0; i < nums.size(); ++i)
      nums[i] = i + 1;
    if (n == k) {
      res.push_back(nums);
      return res;
    }

    vector<int> out;
    subsetsOfK_nums_dfs(nums, 0, k, out, res);
    return res;
  }

  void subsetsOfK_nums_dfs(const vector<int>& nums, int index, int k, vector<int>& out, vector<vector<int>>& res) {
    if (index == nums.size()) {
      if (k == out.size())
        res.push_back(out);
      return;
    }

    // case 1: adding the number
    if (out.size() <= k - 1) { // pruning
      out.push_back(nums[index]);
      subsetsOfK_nums_dfs(nums, index + 1, k, out, res);
      out.pop_back();
    }

    // case 2: not adding the current number
    if (out.size() <= k) // pruning
      subsetsOfK_nums_dfs(nums, index + 1, k, out, res);
  }



  // All sorted subsets of K, input contains duplicates!
  // Same as subsets2 (dedup)
  // same as subsets of k (k size)
  vector<string> subsetsOfK2(string input, int k) {
    sort(input.begin(), input.end()); // sort for easier dedup later
    const int size = input.length();
    if (size == 0 && k == 0) return vector<string>{""};
    else if (size < k) return vector<string>();
    else if (size == k) return vector<string>{input};

    string out;
    vector<string> res;
    subsetsOfK2_dfs(input, 0, k, out, res);
    return res;
  }

  void subsetsOfK2_dfs(const string& input, int index, int k, string& out, vector<string>& res) {
    const int size = input.size();
    if (index == size) {
      if (k == out.length())
        res.push_back(out);
      return;
    }

    // 1. do pick the current char
    if (out.size() <= k - 1) { // pruning
      out += input[index]; // "eat"
      subsetsOfK2_dfs(input, index + 1, k, out, res);
      out.pop_back(); // "spit"
    }

    // dedup - skip repeating chars
    while (index < size - 1 && input[index] == input[index + 1])
      index++;

    // 2. do not pick the current char
    if (out.size() <= k) // pruning
      subsetsOfK2_dfs(input, index + 1, k, out, res);
  }



  // Go down each level, pass number of left and right parentheses used, also pass n
  // Time O(2^(2n) * n) - n levels, at each level there are 2n split
  // Space O(n)
  vector<string> validParentheses(int n) {
    string out;
    vector<string> res;
    validParentheses_dfs(n, 0, 0, out, res); // use numLeft, numRight for left and right parentheses used
    return res;
  }

  void validParentheses_dfs(int n, int numLeft, int numRight, string& out, vector<string>& res) {
    // Base case
    if (numLeft + numRight == n * 2) {
      res.push_back(out);
      return;
    }

    // 1. add '('
    if (numLeft < n) {
      out += '(';
      validParentheses_dfs(n, numLeft + 1, numRight, out, res);
      out.pop_back();
    }

    // 2. add ')'
    if (numLeft > numRight) { // if equal, we cannot add ')'
      out += ')';
      validParentheses_dfs(n, numLeft, numRight + 1, out, res);
      out.pop_back();
    }
  }



  // All valid parentheses of i pairs of (), m pairs of <>, and n pairs of {}
  // At each level, need to check if level is even (add opening brackets), or odd (add closing brackets)
  vector<string> validParentheses2(int l, int m, int n) {
    vector<int> remain{ l, l, m, m, n, n };
    int targetLength = (l + m + n) * 2;
    stack<int> stack;
    string out;
    vector<string> res;

    validParentheses2_dfs(remain, targetLength, stack, out, res);
    return res;
  }

  void validParentheses2_dfs(vector<int>& remain, int targetLength, stack<int>& stack, string& out, vector<string>& res) {
    if (out.size() == targetLength) {
      res.push_back(out);
      return;
    }

    for (int i = 0; i < targetLength; ++i) {
      // even positions
      if (i % 2 == 0) { // (, <, {
        if (remain[i] > 0) { // if we can take it, take it; otherwise do nothing
          auto c = brackets_[i];

          stack.push(i);
          remain[i]--;
          out += c;
          validParentheses2_dfs(remain, targetLength, stack, out, res);
          stack.pop();
          remain[i]++;
          out.pop_back();
        }
      }
      // odd positions
      else { // ), >, }
        if (!stack.empty() && stack.top() == i - 1) { // need to match here
          auto c = brackets_[i];

          stack.pop();
          remain[i]--;
          out += c;
          validParentheses2_dfs(remain, targetLength, stack, out, res);
          stack.push(i - 1);
          remain[i]++;
          out.pop_back();
        }
      }
    }
  }



  // All valid parentheses of i pairs of (), m pairs of <>, and n pairs of {}
  // This one with priority {} over <> over (), which means higher brackets can enclose lower ones, but not vice versa
  //
  // The only difference between valid parentheses #3 and #2 is,
  //     in #3, for even i positions, we check if (remain[i] > 0 && (stack.empty() || stack.top() > i)) instead of just if (remain[i] > 0)
  vector<string> validParentheses3(int l, int m, int n) {
    vector<int> remain{ l, l, m, m, n, n };
    int targetLength = (l + m + n) * 2;
    stack<int> stack;
    string out;
    vector<string> res;

    validParentheses3_dfs(remain, targetLength, stack, out, res);
    return res;
  }

  void validParentheses3_dfs(vector<int>& remain, int targetLength, stack<int>& stack, string& out, vector<string>& res) {
    if (out.size() == targetLength) {
      res.push_back(out);
      return;
    }

    for (int i = 0; i < targetLength; ++i) {
      // even positions
      if (i % 2 == 0) {
        if (remain[i] > 0 && (stack.empty() || stack.top() > i)) { // if we can take it, take it; otherwise do nothing
          auto c = brackets_[i];

          stack.push(i);
          remain[i]--;
          out += c;
          validParentheses3_dfs(remain, targetLength, stack, out, res);
          stack.pop();
          remain[i]++;
          out.pop_back();
        }
      }
      // odd positions
      else {
        if (!stack.empty() && stack.top() == i - 1) { // check for matching
          auto c = brackets_[i];

          stack.pop();
          remain[i]--;
          out += c;
          validParentheses3_dfs(remain, targetLength, stack, out, res);
          stack.push(i - 1);
          remain[i]++;
          out.pop_back();
        }
      }
    }
  }



  // Remove the minimum number of invalid parantheses to make the input a valid string.
  // Return ALL possible results.
  // Example 1: "()())()" -> "()()()", "(())()"
  // Example 2: "(a)())()" -> "(a)()()", "(a())()"
  // Example 3: ")(" -> ""
  // Approach:
  //   We first pre-procee the entire string to work out how many invalid parentheses that we need to remove (including left and right), say "count"
  //   Then we use DFS to gradually work our way down until count == 0
  //   During DFS, we build the string from scratch, and for each char in the input string
  //     1. if the char is '(' or ')', we can either add it or not add it
  //     2. if the char is a letter, we have to add it
  // Time: O(2^n)
  vector<string> removeInvalidParentheses(string input) {
    if (input.empty()) return vector<string>{""};
    int count = preProcess(input);
    string out;
    unordered_set<string> res;
    remove_dfs(input, 0, count, out, res);
    return vector<string>(res.begin(), res.end());
  }

  int preProcess(const string& str) {
    int left = 0, right = 0;
    for (auto c : str) {
      if (c == '(')
        left++;
      else if (c == ')') {
        if (left > 0) left--;
        else right++;
      }
    }
    return left + right; // number of changes needed
  }

  void remove_dfs(const string& input, int i, int count, string& out, unordered_set<string>& res) {
    if (count < 0) return; // are we changing more than we need? no need.

    if (i == input.length()) {
      if (count == 0 && isValid(out))
        res.insert(out);
      return;
    }

    char c = input[i];
    int len = out.length();

    if (c == '(' || c == ')') {
      remove_dfs(input, i + 1, count - 1, out, res); // no add
      out += c;
      remove_dfs(input, i + 1, count, out, res); // add
    }
    else {
      out += c;
      remove_dfs(input, i + 1, count, out, res); // have to add
    }

    out.resize(len);
  }

  bool isValid(const string& s) {
    int count = 0;
    for (char c : s) {
      if (c == '(') count++;
      if (c == ')' && count-- == 0) return false;
    }
    return count == 0;
  }



  // 4 levels for 4 different type of coins
  // at each level, maximum 99 splits
  // No need to worry about duplications
  // Small trick: check if money left < 0, break the for loop as pruning
  // Time O(k^n) - k is target, n is the type of coins
  // Space O(n)
  vector<vector<int>> coinCombinations(vector<int> coins, int target) {
    vector<int> out(coins.size());
    vector<vector<int>> res;
    coinCombinations_dfs(coins, target, 0, out, res);
    return res;
  }

  void coinCombinations_dfs(const vector<int>& coins, int moneyLeft, int index, vector<int>& out, vector<vector<int>>& res) {
    if (index == coins.size() - 1) {
      // Only consider this a valid solution if the remaining money can be represented by the final coin type
      if (moneyLeft % coins.back() == 0) {
        out[index] = moneyLeft / coins.back();
        res.push_back(out);
      }
      return;
    }

    // The type of coint at this level: coins[index]
    for (int n = 0; n * coins[index] <= moneyLeft; ++n) {
      out[index] = n; // # of this coin (ie. coin[index]) used for this solution
      int moneyLeftToFill = moneyLeft - n * coins[index];

      if (moneyLeftToFill < 0) break; // pruning

      coinCombinations_dfs(coins, moneyLeftToFill, index + 1, out, res);
    }
  }



  // Given 24, return all its factor combinations
  // Start with factor 2, product 1, and gradually recurse up
  // Notes:
  // 1) we can repeatedly use the same factor, eg 12 = [2,2,3]
  // 2) 1 is not a factor
  // 3) target itself is a factor
  vector<vector<int>> factorCombinations(int target) {
    vector<vector<int>> res;
    vector<int> out;
    factorCombinations_dfs(2, 1, target, out, res); // start with factor 2, product 1
    return res;
  }

  void factorCombinations_dfs(int currFactor, int currProduct, int target, vector<int>& out, vector<vector<int>>& res) {
    if (currFactor > target || currProduct > target) // overflow
      return;

    if (currProduct == target) { // valid solution
      res.push_back(out);
      return;
    }

    // starting from currFactor, not currFactor + 1 because we can use it multiple times
    // ending <= target not < target, because target itself is also a factor!
    for (int n = currFactor; n <= target; n++) {
      int newProduct = n * currProduct;
      if (newProduct > target) break; // overflow

      if (target % n == 0) {
        out.push_back(n);
        factorCombinations_dfs(n, newProduct, target, out, res);
        out.pop_back();
      }
    }
  }



  // for "abc" we will have 3 levels
  // however it does not mean 1 level for a/b/c, it means one level for each position
  // level 0 - swap 3 chars to 0th position in turn: Abc,            Bac,             Cba           (upper case means fixed)
  // level 1 - swap 3 chars to 1th position in turn: aBc, aCb        bAc, bCa         cBa, cAb
  // level 2 - swap 3 chars to 0th position in turn: ... ...
  // At each level i, we swap different letters to i position
  //
  // Time analysis:
  // When going down each level, we have one less letter to fix, so for each letter it's O(n!). In total, it's O(n! * n)
  // Time: O(n! * n)
  // Space: O(n)
  vector<string> permutations(string input) {
    if (input.empty()) return vector<string>{""};
    vector<string> res;
    permutations_dfs(input, 0, res);
    return res;
  }

  // note: i start from level, NOT zero!!!!!
  void permutations_dfs(string input, size_t level, vector<string>& res) {
    if (level == input.size()) {
      res.push_back(input);
      return; // this is actually optional, but write it to be clear
    }

    // Note: START FROM LEVEL, NOT 0!
    for (size_t i = level; i != input.size(); ++i) {
      swap(input[level], input[i]);
      permutations_dfs(input, level + 1, res);
      swap(input[level], input[i]);
    }
  }



  //                    a1   b   c   a2
  //           /         |         |         \
  //       a1|bca2     b|a1ca2    c|a1ba2    a2|a1bc
  //       / | | \    / | | \    / | | \   (grayed out)
  //    a2(bc)
  //     /
  //    b
  //   /
  //  c
  // 1) A new Set in each recursion, means when we go down a tree branch, we do pick up repeated chars
  // 2) A Set being used in a for loop, means when we go horizontal in a layer, we do NOT pick up repeated chars (the grayed out part, pruning)
  // Time: O(n! * n)
  // Space: O(n^2) - one hashset per level
  vector<string> permutations2(string input) {
    if (input.empty()) return vector<string>{""};
    vector<string> res;
    permutations2_dfs(input, 0, res);
    return res;
  }

  // using a set for horizontal dedup
  void permutations2_dfs(string input, int index, vector<string>& res) {
    if (index == input.size()) {
      res.push_back(input);
      return;
    }

    unordered_set<char> set;
    for (int i = index; i < input.size(); ++i) {
      if (!set.count(input[i])) {
        set.insert(input[i]);
        swap(input[i], input[index]);
        permutations2_dfs(input, index + 1, res);
        swap(input[i], input[index]);
      }
    }
  }



  // Given a string with no dups, return a list with all permutations of its subsets
  // Navie solution: get all subsets, get all permutations
  vector<string> permutationOfSubsets_naive(string input) {
    vector<string> res;

    auto ss = subsets(input);
    for (auto s : ss) {
      auto perms = permutations(s);
      res.insert(res.end(), perms.begin(), perms.end());
    }
    return res;
  }

  // Better solution: just like all permutations, but we print every single node!
  // Because every state in the recursion tree is a valid result
  vector<string> permutationOfSubsets(string input) {
    vector<string> res;
    permutationOfSubsets_helper(input, 0, res);
    return res;
  }

  void permutationOfSubsets_helper(string input, int index, vector<string>& res) {
    res.push_back(input.substr(0, index));
    for (int i = index; i < input.size(); ++i) {
      swap(input[i], input[index]);
      permutationOfSubsets_helper(input, index + 1, res);
      swap(input[i], input[index]);
    }
  }



  // Given a string, determine if any of its permutation can form a palindrome. e.g. "aab" => true
  bool palindromePermutation(string input) {
    unordered_set<char> set;
    for (auto c : input)
      if (!set.count(c)) set.insert(c);
      else set.erase(c);
    return set.size() <= 1;
  }



  // Same as above, but return all palindromes. e.g. "aabb" => "abba" "baab"
  // Need to create a set to dedup
  // Time: O(n! * n)
  // Space: O(n^2) - one hashset per level
  vector<string> palindromePermutation2(string input) {
    if (input.empty()) return {};
    vector<string> res;
    palindrome_helper(input, 0, res);
    return res;
  }

  void palindrome_helper(string input, int level, vector<string>& res) {
    if (level == input.size()) {
      if (isPalinedrome(input))
        res.push_back(input);
      return;
    }

    unordered_set<char> set;
    for (int i = level; i < input.size(); ++i) {
      if (!set.count(input[i])) {
        set.insert(input[i]);
        swap(input[level], input[i]);
        palindrome_helper(input, level + 1, res);
        swap(input[level], input[i]);
      }
    }
  }

  bool isPalinedrome(string s) {
    if (s.empty()) return true;
    int l = 0, r = s.size() - 1;
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
  }



  // Given [2,3,6,7] and 7, return ways of combinations ([7], [2,2,3])
  // 1) Inupt can have dups
  // 2) Any number can be use multiple times
  // Return a list of unique combinations, and in each combination the numbers need to be sorted in non-descending order.
  vector<vector<int>> combinationSum(vector<int>& nums, int target) {
    vector<vector<int>> result;
    vector<int> out;
    sort(nums.begin(), nums.end()); // sort for dedup
    //nums.erase(std::unique(nums.begin(), nums.end()), nums.end()); // dedup
    combinationSum_dfs(nums, 0, target, out, result);
    return result;
  }

  // if input [1, 2, 3], 1 can be used unlimited times
  void combinationSum_dfs(const vector<int>& nums, int index, int target, vector<int>& out, vector<vector<int>>& res) {
    if (target <= 0) {
      if (target == 0)
        res.push_back(out);
      return;
    }

    const int size = nums.size();
    for (int i = index; i < size; i++) {
      if (nums[i] > target) return; // pruning

      out.push_back(nums[i]);
      combinationSum_dfs(nums, i, target - nums[i], out, res); // i instead of i+1, because we are allowed to use the same number unlimited times
      out.pop_back();

      while (i + 1 < size && nums[i] == nums[i + 1]) //dedup
        i++;
    }
  }



  // All unique combinations, and each input can only be used once
  // For each out output combination, numbers need to be sorted in non-descending order
  // e.g. if input is  [1, 1, 2, 3], both 1s can be used, but only once each
  vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
    vector<vector<int>> result;
    vector<int> out;
    sort(nums.begin(), nums.end()); // sort for dedup
    //sorted.erase(std::unique(nums.begin(), nums.end()), nums.end()); // dedup
    combinationSum2_dfs(nums, 0, target, out, result);
    return result;
  }

  void combinationSum2_dfs(const vector<int>& nums, int index, int target, vector<int>& out, vector<vector<int>>& res) {
    if (target <= 0) {
      if (target == 0)
        res.push_back(out);
      return;
    }

    const int size = nums.size();
    for (int i = index; i < size; i++) {
      if (nums[i] > target) return; // pruning

      out.push_back(nums[i]);
      combinationSum2_dfs(nums, i + 1, target - nums[i], out, res); // i+1 instead of i, because we are only allowed to use each number once
      out.pop_back();

      while (i + 1 < size && nums[i] == nums[i + 1]) //dedup, IMPORTANT!
        i++;
    }
  }



  vector<string> telephonePad(int number) {
    unordered_map<char, string> dict;
    dict.insert({ '0', "" });
    dict.insert({ '1', "" });
    dict.insert({ '2', "abc" });
    dict.insert({ '3', "def" });
    dict.insert({ '4', "ghi" });
    dict.insert({ '5', "jkl" });
    dict.insert({ '6', "mno" });
    dict.insert({ '7', "pqrs" });
    dict.insert({ '8', "tuv" });
    dict.insert({ '9', "wxyz" });

    string digits = std::to_string(number);
    vector<char> out(digits.size());
    vector<string> res;
    telephonePad_dfs(dict, digits, 0, out, res);

    if (res.empty()) return vector<string>{""};
    return res;
  }

  // Fixed level, use out[], same as coins
  void telephonePad_dfs(const unordered_map<char, string>& dict, const string& digits, int index, vector<char>& out, vector<string>& res) {
    // base case just like the classical subset 1 problem - take all
    if (index == digits.length()) {
      res.push_back(string(out.begin(), out.end()));
      return;
    }

    char num = digits[index];
    string chars = dict.at(num);
    for (int n = 0; n < chars.size(); ++n) {
      out[index] = chars[n];
      telephonePad_dfs(dict, digits, index + 1, out, res);
    }
  }

  // BFS solution for above
  vector<string> telephonePad_bfs(int number) {
    unordered_map<char, string> dict;
    dict.insert({ '0', "" });
    dict.insert({ '1', "" });
    dict.insert({ '2', "abc" });
    dict.insert({ '3', "def" });
    dict.insert({ '4', "ghi" });
    dict.insert({ '5', "jkl" });
    dict.insert({ '6', "mno" });
    dict.insert({ '7', "pqrs" });
    dict.insert({ '8', "tuv" });
    dict.insert({ '9', "wxyz" });

    string digits = std::to_string(number);
    deque<string> q;
    string s = dict.at(digits[0]);
    if (s.empty())
      q.push_back(""); // for 0 and 1
    else
      for (char c : s) // for other digits
        q.push_back(string(1, c));

    for (int i = 1; i < digits.size(); ++i) {
      string curr = dict.at(digits[i]);
      int size = q.size();
      while (size-- > 0) {
        string prev = q.front();
        q.pop_front();

        if (curr.empty()) // for 0 and 1
          q.push_back(prev);
        else
          for (char c : curr) // for other digits
            q.push_back(prev + c);
      }
    }
    return vector<string>(q.begin(), q.end());
  }



  // Get ALL valid ways of placing the queens
  // Time: O(n!)
  vector<vector<int>> nQueens(int n) {
    if (n == 1) return vector<vector<int>>{vector<int>{0}}; // We can place a queen in a 1x1 grid!
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<int>> result;
    nQueens_dfs(board, 0, result);
    return result;
  }

  void nQueens_dfs(vector<vector<int>>& board, int col, vector<vector<int>>& result) {
    const int n = board.size();
    if (col >= n) { // base case = if we reach here, we've placed all the queens, success!
      saveQueenResult(board, result);
      return;
    }

    // For current column, try each row one by one
    for (int i = 0; i < n; ++i) { 
      if (isQueenSafe(board, i, col)) {
        board[i][col] = 1; // place
        nQueens_dfs(board, col + 1, result);
        board[i][col] = 0; // backtrack
      }
    }
  }

  // Because we are placing the queens col by col from left to right, this function only checks threats from the left
  bool isQueenSafe(const vector<vector<int>>& board, int row, int col) {
    const int n = board.size();
    for (int i = 0; i < col; ++i) if (board[row][i]) return false; // look left
    // no need to look up: current column is always safe (bc. it's a new column)
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) if (board[i][j]) return false; // upper left diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--) if (board[i][j]) return false; // lower left diagonal
    return true;
  }

  void saveQueenResult(const vector<vector<int>>& board, vector<vector<int>>& result) {
    const int size = board.size();
    result.push_back({});
    for (int i = 0; i < size; ++i)
      for (int j = 0; j < size; ++j)
        if (board[i][j] == 1) { result.back().push_back(j); break; }
  }



  // DFS solution
  // We traverse the entire 2D grid
  // We only traverse the UNVISITED '1's, and skip '0's
  // If we see a new unvisited '1' - automatic new island, and we DFS to exhaust all its lands
  //
  // Time: O(m x n) - now this is special, because we only visit each cell once
  // Space: O(1) - because we operate on the original grid
  int numIslands(vector<vector<char>> grid, bool dfs = true) {
    if (grid.empty() || grid[0].empty()) return 0;
    const int rows = grid.size();
    const int cols = grid[0].size();

    int count = 0;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        if (grid[i][j] == '1') {
          count++;
          if (dfs)
            numIslands_dfs(grid, i, j);
          else
            numIslands_bfs(grid, i, j);
        }
    return count;
  }

  // The DFS recursive function
  void numIslands_dfs(vector<vector<char>>& grid, int i, int j) {
    const int rows = grid.size();
    const int cols = grid[0].size();
    if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == '0')
      return;

    grid[i][j] = '0';
    // now we check for its 4 neighbors
    numIslands_dfs(grid, i, j - 1);
    numIslands_dfs(grid, i, j + 1);
    numIslands_dfs(grid, i - 1, j);
    numIslands_dfs(grid, i + 1, j);
  }

  // BFS method: use (i,j) as a seed and exhaust all its neighbors
  void numIslands_bfs(vector<vector<char>>& grid, int i, int j) {
    queue<pair<int, int>> q;
    q.push({ i, j });

    auto explore = [&](vector<vector<char>>& grid, int i, int j, queue<pair<int, int>>& q) {
      if (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size() && grid[i][j] == '1') {
        q.push({ i, j });
        grid[i][j] = '0';
      }
    };

    while (!q.empty()) {
      i = q.front().first;
      j = q.front().second;
      q.pop();

      explore(grid, i, j - 1, q); // left
      explore(grid, i, j + 1, q); // right
      explore(grid, i - 1, j, q); // up
      explore(grid, i + 1, j, q); // down
    }
  }



  // DFS solution
  // Each level is one stop, we have k level (k + 1 flights)
  // Time: O(n^(k+1))
  // Space: O(k+1), the recursion stack
  int cheapestFlightsWithKStops(int n, vector<vector<int>> flights, int src, int dst, int k) {
    unordered_map<int, vector<pair<int, int>>> map; // src, (dst, price): a map contains all flights out of current city
    for (auto f : flights)
      map[f[0]].push_back({ f[1], f[2] });
    vector<int> visited(n, 0);
    visited[src] = 1;
    int res = INT_MAX;
    cheapest_dfs(src, dst, k + 1, 0, map, visited, res);
    return res == INT_MAX ? -1 : res;
  }

  void cheapest_dfs(int src, int dst, int kMoreFlights, int cost, unordered_map<int, vector<pair<int, int>>> map, vector<int>& visited, int& res) {
    if (src == dst) { res = cost; return; }
    if (kMoreFlights == 0) return;

    for (const auto& f : map[src]) {
      int curr = f.first;
      int price = f.second;
      if (visited[curr]) continue; // pruning: do not visit the same city twice
      if (cost + price > res) continue; // pruning: do not continue if cost is already overboard
      visited[curr] = 1;
      cheapest_dfs(curr, dst, kMoreFlights - 1, cost + price, map, visited, res);
      visited[curr] = 0;
    }
  }

  // BFS solution
  // Time: O(n^(k+1))
  // Space: O(n^(k+1))
  int cheapestFlightsWithKStops_bfs(int n, vector<vector<int>> flights, int src, int dst, int k) {
    unordered_map<int, vector<pair<int, int>>> map; // src, (dst, price): a map contians all flights out of current city
    for (auto f : flights)
      map[f[0]].push_back({ f[1], f[2] });
    int res = INT_MAX;
    queue<pair<int, int>> q;
    q.push({ src, 0 }); // current city, cost so far
    int steps = 0;

    while (!q.empty()) {
      int size = q.size();
      while (size--) {
        int curr = q.front().first;
        int cost = q.front().second;
        q.pop();

        // if reached dst, done; else, explore neighbors
        if (curr == dst)
          res = min(res, cost);
        else
          for (auto f : map[curr])
            if (cost + f.second < res) // pruning by cost
              q.push({ f.first, cost + f.second });
      }
      
      if (steps++ > k) break; // IMPORTANT
    }
    return res == INT_MAX ? -1 : res;
  }

  // DP solution (Bellman-Ford algorithm)
  //         dst
  //  k   0   1   2
  //  0   0  inf inf
  //  1   0  100  500
  //  2   0  100  200
  // M[k][d]: from src to d, with up to k flights
  // Initialize: k = 0: 0, inf inf; ( 0 stops can only get me to city 0 but nowhere else)
  //             dst = 0: all zeros ( any stops to city 0 is zero price)
  // Induction rule: M[k][d] = min(M[k-1][d], {M[k-1][x] + cost[x][d]}
  //                 meaning, do we just use the price to city d with k-1 stops,
  //                          or it's cheaper to reach city x with k-1 stops first, then from x to d
  int cheapestFlightsWithKStops_dp(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> tmp(n, 1e9);
    vector<vector<int>> M(k + 2, tmp);
    M[0][src] = 0;
    for (int i = 1; i <= k + 1; i++) {
      M[i][src] = 0;
      for (const auto& f : flights) {
        int from = f[0];
        int to = f[1];
        int cost = f[2];
        M[i][to] = min(M[i][to], M[i - 1][from] + cost);
      }
    }
    auto res = M[k + 1][dst];
    return res >= 1e9 ? -1 : res;
  }



  // Check if a word can be brokend into words that come from the dictionary
  // DFS solution: not very efficient
  //               for "abcde", we checked a|bcde, then a|b|cde, but we will also check ab|cde, so "cde" part will be checked multiple times
  bool wordBreak(string word, vector<string>& dict) {
    unordered_set<string> set(dict.begin(), dict.end());
    return wordBreak_dfs(word, set);
  }

  bool wordBreak_dfs(const string& word, const unordered_set<string>& set) {
    const int size = word.size();
    if (size == 0) return true;

    for (int i = 1; i <= size; ++i)
      if (set.find(word.substr(0, i)) != set.end())
        if (wordBreak_dfs(word.substr(i, size - i), set))
          return true;
    return false;
  }

  // Word break DP solution
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
  bool wordBreak_dp(string word, vector<string>& dict) {
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
  // Give string "catsanddog", dictionary {cat, cats, sand, and, dog} ... find all sentences
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

  vector<string> append(const vector<string>& prefixes, const string& word) {
    vector<string> res;
    for (const auto& p : prefixes)
      res.push_back(p + " " + word);
    return res;
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

      // get ans for left
      string left = s.substr(0, i);
      vector<string> left_ans = append(wordBreak2_dfs(left, set, map), right);

      ans.insert(ans.end(), left_ans.begin(), left_ans.end());
    }

    map[s] = ans; // memorize and return
    return map[s];
  }



  // Given a string of digits, return all possible IP addresses. (note, we will need to insert dots)
  // 4 levels in this DFS recursion tree - 4 sections of the IP address, so in this solution, remainSections is our "level"
  // At each level, we try 1 ~ 3 digits per section, and we need to do pruning for
  //   1) any section of '0X' or '0XX' (but just '0' is okay)
  //   2) any section's value > 255
  // Base case:
  //   When saving each result, we need to check if the entire string is being used up. If not, then it's not a valid result
  //
  // Time : O(3^4) - 4 levels, 3 split per level - can we say O(1)?
  // Space: O(1) - actually O(4), recursion tree height
  vector<string> restoreIpAddress(string input) {
    vector<string> res;
    if (input.size() < 4) return res;
    string out;
    restoreIp_dfs(input, 0, 4, out, res);
    return res;
  }

  void restoreIp_dfs(string& input, int index, int remainSections, string& out, vector<string>& res) {
    const int size = input.size();
    if (remainSections == 0) {
      if (index == size)
        res.push_back(out);
      return;
    }

    // Pruning / optimization: if we have more remaining digits than we can consume (remaining parts * 3), prune this branch
    int remainDigits = size - index;
    if (remainDigits > remainSections * 3)
      return;

    // for each section, we can have 1/2/3 digits
    for (int i = 1; i <= 3; ++i) {
      if (index > size - 1) break;  // out of bound
      if (i != 1 && input[index] == '0') break; // we allow "0." as a section, but not "01." or "001."

      auto substring = input.substr(index, i);
      auto val = stoi(substring);

      if (val <= 255) {
        auto newString = out + substring;
        newString += remainSections == 1 ? "" : "."; // final section will not have '.' at the end
        restoreIp_dfs(input, index + i, remainSections - 1, newString, res);
      }
    }
  }



  // Keep distance for idential elements, e.g. {2, 3, 1, 2, 1, 3}
  vector<int> keepDistance(int k) {
    vector<int> nums(k);
    for (int i = 0; i < k; ++i) nums[i] = i + 1;
    vector<int> res(k * 2, 0); // pre-fill zeros!
    return keepDistance_dfs(nums, 0, res) ? res : vector<int>{};
  }

  bool keepDistance_dfs(vector<int> nums, int level, vector<int>& res) {
    if (level == nums.size()) {
      return true;
    }

    int emptyIndex = findFirstEmpty(res, level); // find left

    for (int i = level; i < nums.size(); ++i) {
      swap(nums[level], nums[i]); // eat

      int otherIndex = emptyIndex + nums[level] + 1; // find right
      if (otherIndex < res.size() && res[otherIndex] == 0) {
        res[emptyIndex] = nums[level]; // fill
        res[otherIndex] = nums[level]; // fill
      }

      if (keepDistance_dfs(nums, level + 1, res))
        return true;

      res[emptyIndex] = 0; // vacate
      res[otherIndex] = 0; // vacate

      swap(nums[level], nums[i]); // spit
    }
    return false;
  }

  int findFirstEmpty(vector<int> a, int level) {
    if (level == 0) return 0; // level 0, can always fill
    for (int i = level; i < a.size(); i++)
      if (a[i] == 0) return i;
    return 0;
  }



  // Generate randome maze
  // Key questin: we can't jump 1 cell at a time. We have to jump 2 at a time. Why?
  struct Dir {
    int di;
    int dj;
  public:
    Dir(int i, int j) : di(i), dj(j) {};
    int moveI(int i, int times) { return i + di * times; }
    int moveJ(int j, int times) { return j + dj * times; }
  };

  vector<vector<int>> generateRandomMaze(int n) {
    vector<vector<int>> maze(n, vector<int>(n, 1)); // fill with walls
    maze[0][0] = 0;
    vector<Dir> defaultDirs{ Dir(-1, 0), Dir(1, 0), Dir(0, -1), Dir(0, 1) };
    generate_dfs(maze, 0, 0, defaultDirs);
    return maze;
  }
  
  // DFS function
  // From current (i,j), get a random direction and follow that direction to do DFS and backtrack
  // Take a step of 2, if land a valid wall (ie. unvisited), break it through
  void generate_dfs(vector<vector<int>>& m, int i, int j, const vector<Dir>& defaultDirs) {
    auto dirs = defaultDirs;
    randomDirection(dirs);
    for (auto d : dirs) {
      int nextI = d.moveI(i, 2);
      int nextJ = d.moveJ(j, 2);
      
      if (isWall(m, nextI, nextJ)) {
        m[d.moveI(i, 1)][d.moveJ(j, 1)] = 0; // clear landing spot
        m[nextI][nextJ] = 0; // break through wall
        generate_dfs(m, nextI, nextJ, defaultDirs);
      }
    }
  }

  void randomDirection(vector<Dir>& dirs) {
    const int size = dirs.size();
    for (int i = 0; i < size; ++i) {
      int j = rand() % (size - 1);
      auto tmp = dirs[i]; dirs[i] = dirs[j]; dirs[j] = tmp;
    }
  }

  bool isWall(const vector<vector<int>>& m, int i, int j) {
    return (i >= 0 && i < m.size() && j >= 0 && j < m[0].size() && m[i][j] == 1);
  }



  // Optimal account balancing - minimum transfer to sort out the inter-debts within a group of people
  //
  // DFS solution:
  // First we build accounts for everyone, + means being owed by the group,  - means owing to the group, if we have a 0? remove that guy first.
  // Data structure? vector not map! because we don't care who owes who, we just need to "flat" that vector
  // During DFS recursion:
  //    if start == account length, all accounts used up, update res with count
  //    if not, then we iterate all REMAINING accounts
  //        remember to only compare two accounts of opposite signs
  //        remember to backtrack - ie. recover the current account     
  int optimalAccountBalancing(vector<vector<int>>& transactions) {
    int res = INT_MAX;
    unordered_map<int, int> map;
    for (auto t : transactions) {
      map[t[0]] -= t[2];
      map[t[1]] += t[2];
    }
    vector<int> accounts;
    for (auto a : map)
      if (a.second != 0) accounts.push_back(a.second);

    optimal_helper(accounts, 0, 0, res);
    return res;
  }

  void optimal_helper(vector<int>& a, int index, int count, int& res) {
    const int n = a.size();
    while (index < n && a[index] == 0) ++index;
    if (index == n) {
      res = min(res, count);
      return;
    }

    // current account: index
    // remaining account i, where i [index+1, n-1]
    // try all combinations!
    // NOTE: only try the combination if both are oppostie signs, why? if both with pos/neg accounts, no point merging them!
    for (int i = index + 1; i < n; ++i) {
      if (a[i] * a[index] < 0) {
        a[i] += a[index];
        optimal_helper(a, index + 1, count + 1, res);
        a[i] -= a[index]; // backtrack
      }
    }
  }



  // Given "2-1-1", it can be (2-1)-1, or 2-(1-1), so we return [0, 2]
  // Valid signs are +, -, *.
  // Time: O(2^(n/2))
  // Space: ???
  vector<int> differentWaysToAddParentheses(string input) {
    if (input.empty()) return {};
    unordered_map<string, vector<int>> map; // a hashmap created for memo purpuse, <string, list of answers from that string>
    vector<int> res = ways_helper(input, map);
    sort(res.begin(), res.end());
    return res;
  }

  vector<int> ways_helper(const string& input, unordered_map<string, vector<int>>& map) {
    if (map.count(input)) return map[input];
    vector<int> res;

    if (input.size() == 1) {
      // single character? must be a number!
      res.push_back(stoi(input));
    } else {
      // input is num-char-num-char-num... format
      // we break at every sign position, and run DFS recursion on left and right part
      // we rely on the memo to avoid re-computing the same string that has been previously computed
      for (int i = 1; i <= input.length() - 2; i += 2) {
        // 1. get left and right part of the string, NOT including the current sign
        string left = input.substr(0, i);
        string right = input.substr(i + 1);

        // 2. run DFS, get all possible answers from left and right
        vector<int> leftRes = ways_helper(left, map);
        vector<int> rightRes = ways_helper(right, map);

        // 3. iterate through all combinations of the left and right answers, add them to the final answer list
        for (auto a : leftRes)
          for (auto b : rightRes)
            res.push_back(compute_helper(a, b, input[i]));
      }
    }

    // IMPORTANT: memo!
    map[input] = res;
    return res;
  }

  int compute_helper(int a, int b, char sign) {
    if (sign == '+')
      return a + b;
    else if (sign == '-')
      return a - b;
    else
      return a * b;
  }

private:
  const vector<char> brackets_{ '(', ')', '<', '>', '{', '}' };

};
