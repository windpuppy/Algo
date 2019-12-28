#include  "BinarySearch.h"

int* fn() {
  int n = 10;
  return &n;
}



int main()
{
  int* p = fn();
  auto a = *p;

  BinarySearch sol;

  // Classical binary search
  {
    vector<int> values({3, 4, 5, 6, 9, 16});
    auto res = sol.binarySearch(values, 5);
  }

  // Search in sorted matrix
  {
    vector<int> a{ 1, 2, 3, 4 };
    vector<int> b{ 5, 6, 7, 8 };
    vector<int> c{ 9, 10, 11, 12 };
    vector<vector<int>> matrix{ a, b, c };
    auto res = sol.binarySearchSortedMatrix(matrix, 7);
  }
  
  // Closest in sorted array
  {
    vector<int> array{ 3, 4, 5, 6, 6, 12, 16 };
    auto res = sol.findClosest(array, 10);
  }

  // First occurrence
  {
    vector<int> array{ 1, 2, 2, 2, 2, 3, 4 };
    auto res = sol.firstOccurrence(array, 2);
  }

  // Last occurrence
  {
    vector<int> array{ 1, 2, 2, 2, 2, 3, 4 };
    auto res = sol.lastOccurrence(array, 2);
  }

  // K closest
  {
    vector<int> array{ 1, 2, 3 };
    auto res = sol.kClosest(array, 2, 1);
    vector<int> array2{ 1, 3, 3, 6, 9, 9, 12, 15 };
    res = sol.kClosest(array2, 0, 3);
    vector<int> array3{ 1 };
    res = sol.kClosest(array3, 0, 1);
  }

  // Smallest element larget than target
  {
    // See my LC submission online
  }
  
  // Shift position
  {
    auto res = sol.shiftPosition(vector<int>{3, 4, 5, 1, 2});
    res = sol.shiftPosition(vector<int>{4, 5, 1, 2, 3});
    res = sol.shiftPosition(vector<int>{1, 2, 3, 4, 5});
  }

  cin.get();
  return 0;
}

