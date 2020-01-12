// LinkedIn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "LinkedIn.h"

using namespace std;

int main()
{
  LinkedIn sol;

  // Merge intervals
  {
    vector<vector<int>> intervals{ {1, 3}, {2, 6 }, {8, 10}, {15, 18} };
    auto res = sol.mergeIntervals(intervals);
  }

  // Insert interval
  {
    vector<vector<int>> intervals{ {1, 3}, {3, 5 }, {6, 7}, {8, 10}, {12, 16} };
    vector<int> newInterval{ 4, 8 };
    auto res = sol.insertInterval(intervals, newInterval);
    res = sol.insertInterval2(intervals, newInterval);
  }

  cin.get();
  return 0;
}

