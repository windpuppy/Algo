#include "Recursion.h"

int main()
{
  Recursion sol;

  // Fibonnaci
  {
    auto res = sol.fibonacci(0); // 0
    res = sol.fibonacci(1); // 1
    res = sol.fibonacci(5); // 5
    cout << endl;
  }

  // Power
  {
    auto res = sol.power(0, 2); // 0
    res = sol.power(2, 0); // 1
    res = sol.power(3, 4); // 81;
    res = sol.power(3, 3); // 27
  }

  // String abbreviation matching
  {
    auto res = sol.stringAbbreviationMatching("lovercom", "3er3");
  }

  // Spiral order traverse 1
  {
    vector<vector<int>> matrix {
      vector<int>{1, 2, 3, 4},
      vector<int>{5, 6, 7, 8},
      vector<int>{9, 10, 11, 12},
      vector<int>{13, 14, 15, 16},
    };
    auto res = sol.spiralTraverse(matrix);
  }

  // Spiral order traverse 2
  {
    vector<vector<int>> matrix{
      vector<int>{1, 2, 3, 4},
      vector<int>{5, 6, 7, 8},
      vector<int>{9, 10, 11, 12}
    };
    auto res = sol.spiralTraverse2(matrix);
  }

  cin.get();
  return 0;
}

