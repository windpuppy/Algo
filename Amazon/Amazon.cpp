#include <iostream>

#include "Amazon.h"

using namespace std;

int main()
{
  Amazon sol;

  // Reorder data logs
  {
    vector<string> logs{ "let2 art zero", "let1 art zero", "dig1 8", "let3 art can" };
    auto res = sol.reorderLogFiles(logs);
  }

  // Search in 2D matrix
  {
    vector<vector<int>> matrix{ {-1, 3} };
    auto res = sol.searchMatrix2(matrix, 3);
  }

  // Rotten oranges
  {
    vector<vector<int>> grid{ {2, 1, 1},{1, 1, 0},{0, 1, 1 } };
    auto res = sol.rottingOranges(grid);
  }

  // Prison cells after N days
  {
    vector<int> cells{ 1, 0, 0, 1, 0, 0, 1, 0 };
    auto res = sol.prisonAfterNDays(cells, 1000000000);
  }

  cin.get();
  return 0;
}

