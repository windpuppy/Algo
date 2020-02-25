#pragma once

#include <vector>

using namespace std;

// Time: O(1), Space: O(n)
class TicTacToe {
private:
  vector<int> rowJudge; // judge rows
  vector<int> colJudge; // judge cols
  int diag1, diag2; // judge diag, anti-diag

public:
  TicTacToe(int n) : rowJudge(n), colJudge(n), diag1(0), diag2(0) {}

  // player will be 1 or 2
  // if there is a winner, return the player; otherwise return 0
  int move(int row, int col, int player) {
    const int size = rowJudge.size();
    int add = player == 1 ? 1 : -1;

    rowJudge[row] += add;
    colJudge[col] += add;
    if (row == col) diag1 += add;
    if (row + col == size - 1) diag2 += add;

    if (abs(rowJudge[row]) == size ||
        abs(colJudge[col]) == size ||
        abs(diag1) == size ||
        abs(diag2) == size)
      return player;

    return 0;
  }
};