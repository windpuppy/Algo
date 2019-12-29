#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class TreeNode {
public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

class Amazon {
public:
  // An array of logs, string is either "letter log" or "digi log"
  // letter log: "let1 art can", "let2 own kit dig"
  // digi log: "dig1 8 1 5 1", "dig2 3 6"
  // Reorder those logs so that letter logs are in front of digi logs
  //     also 1. letter logs are lexicographically ordered based on their content (use identifier for tie breaker)
  //          2. digi logs in their original order
  // Implementation:
  // For letter logs: move identifier to the end for sorting purpose, then move it back
  // Time: O(nlogn)
  // Space: O(n)
  vector<string> reorderLogFiles(vector<string>& logs) {
    vector<string> letterLogs, digiLogs;
    for (auto& s : logs) {
      int i = s.find_first_of(" ");
      if (isdigit(s[i + 1]))
        digiLogs.push_back(s);
      else
        letterLogs.push_back(s.substr(i + 1) + " " + s.substr(0, i));
    }

    sort(letterLogs.begin(), letterLogs.end());

    for (auto& s : letterLogs) {
      int i = s.find_last_of(" ");
      s = s.substr(i + 1) + " " + s.substr(0, i);
    }

    for (auto& s : digiLogs) letterLogs.push_back(s);
    return letterLogs;
  }



  // Check if S is a subtree of T
  // Note: we are checking subtree, not if "S is part of T". These two are fundamentally different
  bool isSubtree(TreeNode* t, TreeNode* s) {
    if (!t) return false;
    if (isIdentical(t, s)) return true;

    return isSubtree(t->left, s) || isSubtree(t->right, s);
  }

  bool isIdentical(TreeNode* a, TreeNode* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    if (a->value != b->value) return false;

    return isIdentical(a->left, b->left) && isIdentical(a->right, b->right);
  }

  
  
  // Most common word
  // Given a paragraph and a list of banned word, find the most common word (guaranteed to exist, and in lower case)
  // We can first push all banned word into a set for quicker lookup, but a little trick enables us to share one single map
  string mostCommonWord(string p, vector<string>& banned) {
    unordered_map<string, int> map;
    for (int i = 0; i < p.size();) {
      string word = "";
      while (i < p.size() && isalpha(p[i])) word.push_back(tolower(p[i++]));
      while (i < p.size() && !isalpha(p[i])) i++;
      map[word]++;
    }

    for (auto b : banned) map[b] = 0;

    string res = "";
    int count = 0;
    for (auto x : map)
      if (x.second > count) {
        res = x.first;
        count = x.second;
      }
    return res;
  }

  

  // Search in a 2D matrix that is row & column wise sorted (target might or might not exist)
  // e.g.
  // [1,   3,  5,  7],
  // [10, 11, 16, 20],
  // [23, 30, 34, 50]
  // Time: O(logmn), Space: O(1)
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    int left = 0, right = rows * cols - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      int i = mid / cols;
      int j = mid % cols;
      int val = matrix[i][j];

      if (target == val) return true;
      else if (target < val) right = mid - 1;
      else left = mid + 1;
    }

    return false;
  }



  // Search in a 2D matrix that is row & column wise sorted (target might or might not exist)
  // [1,   4,  7, 11],
  // [2,   5,  8, 12],
  // [3,   6,  9, 16],
  // [10, 13, 14, 17],
  // [18, 21, 23, 26]
  // Solution: we can either start at the bottom-left or top-right corner
  // Time: O(m + n)
  bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    int i = rows - 1, j = 0;
    while (i >= 0 && j < cols)
      if (matrix[i][j] == target)
        return true;
      else if (matrix[i][j] > target) // go up
        i--;
      else // go right
        j++;
    return false;
  }

};