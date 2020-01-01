#pragma once

#include <vector>

using namespace std;

// Time: O(1), Space: O(n)
class TicTacToe {
private:
  vector<int> rowJudge; // judge rows
  vector<int> colJudge; // judge cols
  int diag1, diag2; // judge diag, anti-diag
  int total; // the winning requirement

public:
  TicTacToe(int n) : rowJudge(n), colJudge(n), diag1(0), diag2(0),total(n) {}

  // player will be 1 or 2
  // if there is a winner, return the player; otherwise return 0
  int move(int row, int col, int player) {
    int add = player == 1 ? 1 : -1;

    rowJudge[row] += add;
    colJudge[col] += add;
    if (row == col) diag1 += add;
    if (row + col == total - 1) diag2 += add;

    if (abs(rowJudge[row]) == total ||
      abs(colJudge[col]) == total ||
      abs(diag1) == total ||
      abs(diag2) == total)
      return player;

    return 0;
  }

};