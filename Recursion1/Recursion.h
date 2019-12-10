#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Recursion
{
public:
  // Time O(2^n)
  // Space O(n)
  //
  // Time analysis:
  // recursion tree, at each level it splits into two
  // Time at each level spent: 1, 2, 4, 8, 16, ..., 2^(n-1)
  // so it's a magnitude of 2^n
  int fibonacci(int k) {
    if (k <= 0) return 0;
    else if (k == 1) return 1;
    return fibonacci(k - 1) + fibonacci(k - 2);
  }

  // Time O(logb) - O(1) at each level
  // Space O(logb) - recursion call stack
  //
  // recursion tree: logb levels, because we split the problem into 2 at each level
  long power(int a, int b) {
    if (a == 0) return 0;
    else if (b == 0) return 1;
    else {
      long halfRes = power(a, b / 2);
      halfRes *= halfRes;
      if (b % 2 == 1) halfRes *= a;
      return halfRes;
    }
  }

  // Time O(b)
  // Space O(b) - recursion call stack
  //
  // recursion tree: b levels, because we reduce b by 1 at a time
  long power_naive(int a, int b) {
    return b == 0 ? 1 : a * power_naive(a, b - 1);
  }



  // book can be abbreviated to 4, b3, b2k
  // Given a string and its abbrev, check if they can match
  bool stringAbbreviationMatching(string word, string pattern) {
    return match_recur(word, pattern, 0, 0);
  }

  bool match_recur(string& s, string& t, int si, int ti) {
    int slen = (int)s.length();
    int tlen = (int)t.length();

    // The ONLY base case that returns true
    // when both s and t run out, we have a match
    if (si == slen && ti == tlen)
      return true;

    // if either of them runs out, no match
    if (si >= slen || ti >= tlen)
      return false;

    // case 1: if current t is not a digit - easier case - keep matching
    if (!isdigit(t[ti]))
      return s[si] == t[ti] ? match_recur(s, t, si + 1, ti + 1) : false;

    // case 2: if current t is a digit - tougher case
    // need to handle multiple digits
    int num = 0;
    while (ti < tlen && isdigit(t[ti]))
      num = num * 10 + t[ti++] - '0';
    return match_recur(s, t, si + num, ti); // e.g. book skip "oo", pattern skip "2"
  }




  // 1 - - |
  // | o o |
  // | o o |
  // | - - -
  // starting from 1, we go right 3 times, down 3 times, up 3 times
  // then call recursion for the inner matrix, of size - 2
  // Guaranteed - square matrix
  vector<int> spiral(vector<vector<int>>& matrix) {
    vector<int> res;
    const int size = matrix.size();
    spiral_recur(matrix, size, res);
    return res;
  }

  void spiral_recur(const vector<vector<int>>& matrix, int newSize, vector<int>& res) {
    // base case 1: even size matrix
    if (newSize == 0) return;

    // base case 2: odd size matrix
    int offset = (matrix.size() - newSize) / 2;
    if (newSize == 1) {
      res.push_back(matrix[offset][offset]);
      return;
    }

    // go right
    for (int j = 0; j < newSize - 1; ++j) res.push_back(matrix[offset][offset + j]);
    // go down
    for (int i = 0; i < newSize - 1; ++i) res.push_back(matrix[offset + i][offset + newSize - 1]);
    // go left
    for (int j = newSize - 1; j >= 1; --j) res.push_back(matrix[offset + newSize - 1][offset + j]);
    // go up
    for (int i = newSize - 1; i >= 1; --i) res.push_back(matrix[offset + i][offset]);

    // next (inner) square
    spiral_recur(matrix, newSize - 2, res);
  }

  

  // Rectangular matrix, not neccesarily square
  vector<int> spiral2(vector<vector<int>>& matrix) {
    vector<int> res;
    const int height = matrix.size();
    const int width = matrix[0].size();
    spiral_recur2(matrix, height, width, res);
    return res;
  }

  void spiral_recur2(const vector<vector<int>>& matrix, int newHeight, int newWidth, vector<int>& res) {
    // cases 1: either dim is zero
    if (newHeight == 0 || newWidth == 0) return;

    int off1 = (matrix.size() - newHeight) / 2;
    int off2 = (matrix[0].size() - newWidth) / 2;

    // case 2: single row
    if (newHeight == 1) {
      for (int j = 0; j < newWidth; ++j)
        res.push_back(matrix[off1][off2 + j]);
      return;
    }

    // case 3: single column
    if (newWidth == 1) {
      for (int i = 0; i < newHeight; ++i)
        res.push_back(matrix[off2 + i][off2]);
      return;
    }

    // go right
    for (int j = 0; j < newWidth - 1; ++j) res.push_back(matrix[off1][off2 + j]);
    // go down
    for (int i = 0; i < newHeight - 1; ++i) res.push_back(matrix[off1 + i][off2 + newWidth - 1]);
    // go left
    for (int j = newWidth - 1; j >= 1; --j) res.push_back(matrix[off1 + newHeight - 1][off2 + j]);
    // go up
    for (int i = newHeight - 1; i >= 1; --i)res.push_back(matrix[off1 + i][off2]);

    // next (inner) square
    spiral_recur2(matrix, newHeight - 2, newWidth - 2, res);
  }


  
};
