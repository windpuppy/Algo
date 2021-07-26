#include "Recursion.h"

int main()
{
  Recursion sol;



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

