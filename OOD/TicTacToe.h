#pragma once

#include <vector>

using namespace std;

// Time: O(1), Space: O(n)
// More feature to add: check player 1, 2, 1, 1 order
class TicTacToe {
private:
	vector<int> rowJudge; // judge rows
	vector<int> colJudge; // judge cols
	int diag1, diag2; // judge diag, anti-diag
	vector<vector<bool>> visted;

public:
	TicTacToe(int n) : rowJudge(n), colJudge(n), diag1(0), diag2(0) {
		visted = vector<vector<bool>>(n, vector<bool>(n, false));
	}

	// Input: row, col, player (1 or 2)
	// Output: if there is a winner, winner player
	//         0 to continue
	//         -1 for invalid move
	int move(int row, int col, int player) {
		const int size = rowJudge.size();
		if (row < 0 || row > size - 1 || col < 0 || col > size - 1 || visted[row][col] ||
			(player != 1 && player != 2))
			return -1;
		
		visted[row][col] = true;
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