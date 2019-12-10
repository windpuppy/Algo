#pragma once

#include <iostream>
#include <stack>

using namespace std;

class SortWith2Stacks
{
public:
  // 3        1
  // 1        2
  // 4 become 3
  // 2        4
  // 5        5

  // Implementation:
  // use input as input and final result, buffer as buffer
  // every iteration, put all input into buffer, while recording global min and its occurances
  // then when we put buffer back to input, we skip the global min(s), and put them back to buffer
  // for next iteration, we do not touch those (already sorted) global mins
  // eventually buffer will be reverse sorted, then we put them back to input

  void sort2(stack<int>& input, stack<int>& buffer)
  {
    // when input only contains 1 item, no need to sort
    while (!input.size() != 1)
    {
      int globalMin = INT_MAX;
      int count = 0;

      // iterate remaining input, record global min and its occurrences
      while (!input.empty())
      {
        int curr = input.top();
        if (curr < globalMin) // // new global min, reset count
        {
          globalMin = curr;
          count = 1;
        }
        else if (curr == globalMin) // re-appearing global min, count++
        {
          count++;
        }
        input.pop();
        buffer.push(curr);
      }

      // put the whole buffer (except global mins) back to input
      while (!buffer.empty())
      {
        int curr = buffer.top();
        if (curr < globalMin)
          break; // smaller number found? must be from previous round, stop.
        else if (curr > globalMin)
          input.push(curr);

        buffer.pop();
      }

      // push global min(s) back to buffer
      while (count-- > 0)
        buffer.push(globalMin);
    }

    // finally, move buffer back to input
    while (!buffer.empty())
    {
      input.push(buffer.top());
      buffer.pop();
    }

  }
};
