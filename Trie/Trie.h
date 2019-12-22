#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Trie {
public:

  // 2D grid, see if we can find the word
  // We can only move up, down, left and right
  // Time complexity: O(m*n*4^k) - recursion tree is height k, each node has 4 splits (4 directions), iterate through m*n grid
  // Space complexity: O(k) - recursion tree, k levels
  bool wordSearch(vector<vector<char>> board, string word) {
    if (board.empty() || board[0].empty()) return false;
    if (word.size() > board.size()* board[0].size()) return false; // early termintation
    for (int i = 0; i < board.size(); ++i)
      for (int j = 0; j < board[0].size(); ++j)
        if (wordSearch_dfs(board, word, 0, i, j))
          return true;
    return false;
  }

  bool wordSearch_dfs(vector<vector<char>>& board, string& word, int index, int i, int j) {
    if (index == word.size()) return true;
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index]) return false;
    char tmp = board[i][j];
    board[i][j] = ' ';
    bool found = wordSearch_dfs(board, word, index + 1, i, j - 1) ||
      wordSearch_dfs(board, word, index + 1, i, j + 1) ||
      wordSearch_dfs(board, word, index + 1, i - 1, j) ||
      wordSearch_dfs(board, word, index + 1, i + 1, j);
    board[i][j] = tmp;
    return found;
  }

  // Find all solutions (need to dedup!)
  vector<string> wordSearch2(vector<vector<char>> board, vector<string> words) {
    vector<string> res;
    if (board.empty() || board[0].empty()) return res;
    unordered_set<string> set;
    for (auto word : words) {
      for (int i = 0; i < board.size(); ++i)
        for (int j = 0; j < board[0].size(); ++j)
          if (wordSearch_dfs(board, word, 0, i, j) && set.find(word) == set.end()) {
            res.push_back(word);
            set.insert(word);
          }
    }
    return res;
  }

};