#include "Topology.h"

#include <iostream>

using namespace std;

int main()
{
  Topology sol;

  // Course schedule 1 & 2
  {
    // 1 --> 0 --> 2 --> 3 --> 4
    // |     |----------->
    // |----------------->
    vector<vector<int>> prerequisites{
      {1,0},
      {0,2},
      {2,3},
      {1,3},
      {0,3},
      {3,4}
    };
    auto res = sol.courseSchedule(5, prerequisites); // true
    res = sol.courseSchedule_topo(5, prerequisites); // true

    auto res2 = sol.courseSchedule2(5, prerequisites); // 4,3,2,0,1 (not unique)
    res2 = sol.courseSchedule2_topo(5, prerequisites); // 4,3,2,0,1 (not unique)
  }

  // Alien dictionary
  {
    vector<string> words{ "wrt", "wrf", "er", "ett", "rttt" };
    auto res = sol.alienDictionary(words); // "wertf"
  }

  cin.get();
  return 0;
}

