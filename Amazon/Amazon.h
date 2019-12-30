#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

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



  // Rotting oranges
  // 0: empty cell, 1: fresh orange, 2: rotten orange
  // Every minute, any fresh orange adjacent to rotten orange becomes rotten, return the minimum minutes that no fresh oranges are left
  // This is essentially a BFS problem, we first push all rotten oranges into the queue, and "rot" their neighbors
  // Time: O(mn), Space: O(mn)
  int rottingOranges(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    const int rows = grid.size();
    const int cols = grid[0].size();
    int minutes = 0;
    int freshOranges = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        if (grid[i][j] == 2)
          q.push({ i, j });
        else if (grid[i][j] == 1)
          freshOranges++;

    while (!q.empty()) {
      const int size = q.size();
      int before = freshOranges;
      for (int k = 0; k < size; ++k) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        orangeHelper(grid, i - 1, j, q, freshOranges);
        orangeHelper(grid, i + 1, j, q, freshOranges);
        orangeHelper(grid, i, j - 1, q, freshOranges);
        orangeHelper(grid, i, j + 1, q, freshOranges);
      }
      if (freshOranges < before)
        minutes++;
    }
    return freshOranges == 0 ? minutes : -1; // only return minutes if all fresh oranges are rotten
  }

  void orangeHelper(vector<vector<int>>& grid, int i, int j, queue<pair<int, int>>& q, int& freshOranges) {
    const int rows = grid.size(), cols = grid[0].size();
    if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] != 1) return;
    grid[i][j] = 2;
    freshOranges--;
    q.push({ i, j });
  }



  // Prison cells after N days
  // Cell state change rule: if i-1 and i+1 both occupied or vacant, i becomes occupied next day; otherwise i becomes vacent next day
  // (which implies first and last cells become vacant from day 2, and remain vacant because they don't have 2 neighbors)
  // Idea: check if there is a cycle
  vector<int> prisonAfterNDays(vector<int>& c, int N) {
    if (c.empty() || N <= 0) return c;
    unordered_set<string> set;
    int count = 0;
    bool hasCycle = false;
    for (int i = 0; i < N; ++i) {
      auto next = nextDay(c);

      string s = "";
      for (auto n : next) s += to_string(n);
      if (!set.count(s)) {
        set.insert(s);
        count++;
      }
      else {
        hasCycle = true;
        break;
      }
      c = next;
    }

    if (hasCycle) {
      N = N % count;
      for (int i = 0; i < N; ++i)
        c = nextDay(c);
    }
    return c;
  }

  vector<int> nextDay(vector<int>& cells) {
    vector<int> ret(cells.size(), 0);
    for (int i = 1; i < cells.size() - 1; ++i)
      ret[i] = cells[i - 1] == cells[i + 1] ? 1 : 0;
    return ret;
  }



  // Given a list of words, find out all the concatenated words (ie. words can be entirely represented by some others in the dictionary)
  vector<string> concatenatedWords(vector<string>& words) {
    vector<string> res;
    if (words.empty()) res;
    auto wordComp = [&](const string& a, const string& b) { return a.size() < b.size(); };
    sort(words.begin(), words.end(), wordComp);
    unordered_set<string> dict;
    
    for (auto& word : words) {
      if (wordBreak(word, dict))
        res.push_back(word); // no need to insert this word. why? if we have bob+cat=bobcat, "bob" and "cat" will enable "bobcatdog" later on
      else
        dict.insert(word);
    }
    return res;
  }

  // A DP helper, ×ó´ó¶ÎÓÒÐ¡¶Î
  // Use book M, M[i] represents can "the substring from the begining to the i-th character" be composed by words from the dict
  // Left: check M; Right: manual work
  bool wordBreak(string& word, unordered_set<string>& dict) {
    if (word.empty()) return false;
    vector<bool> M(word.size() + 1, false); // plus 1, because we reserve M[0] for empty string, for convenience
    M[0] = true;

    for (int i = 1; i <= word.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        string right = word.substr(j, i - j);
        bool rightMatch = dict.count(right) != 0;

        if (M[j] && rightMatch) { // eg. bob | c, left BIG (use M), right SMALL (manual check)
          M[i] = true;
          break;
        }
      }
    }
    return M.back();
  }
};