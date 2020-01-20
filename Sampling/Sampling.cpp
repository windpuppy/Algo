#include "Sampling.h"

int main()
{
  Sampling sol;

  {
    vector<int> values;
    for (int i = 1; i <= 100; ++i) values.push_back(i);
    auto res = sol.ninetyFivePercentile(values);
    res = sol.ninetyFivePercentile_cheat(values);
  }

  cin.get();
  return 0;
}

