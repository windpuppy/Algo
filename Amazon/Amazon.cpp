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

  cin.get();
  return 0;
}

