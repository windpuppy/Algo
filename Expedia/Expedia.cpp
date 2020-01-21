// Expedia.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Expedia.h"

#include <iostream>

int main()
{
  Expedia sol;

  // Smallest divisor
  {
    vector<int> nums{ 1, 2, 5, 9 };
    auto res = sol.smallestDivisor(nums, 6);
    res = sol.smallestDivisor2(nums, 6);

    vector<int> nums2{ 2, 3, 5, 7, 11 };
    res = sol.smallestDivisor2(nums2, 11);

    vector<int> nums3{ 19 };
    res = sol.smallestDivisor2(nums3, 5);
  }

  // String compression
  {
    string s("abbbbbbbbbbbb");
    auto res = sol.compress(s); // "ab12"
  }

  // Gas station
  {
    vector<int> gas{ 3, 1, 1 }, cost{ 1,2,2 };
    auto res = sol.gasStation(gas, cost);
  }

  std::cout << "Hello World!\n";
  return 0;
}

