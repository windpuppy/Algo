#pragma once

#include <vector>
#include <string>

using namespace std;

class Lyft {
public:

  // Asteroids Collision problem
  // For example: [5, -10, 5] ==> output will be [-5, 5], because -10 moves left, 5 and 5 move right
  //              [5, 5, -10] ==> output will be [-10], because -10 will destroy both 5s
  // Consider '-' is moving left, '+' is stationary
  // Output will have to be [-, -, -, ..., +, +, +]
  // Solution:
  // For any + value, always put into the stack
  // For any - value, case 1: stack empty / stack top is minus: push
  //                  case 2: stack top is plus: go through the stack and simulate
  // Time complexity: O(n)
  // Space complexity: O(n)
  vector<int> asteroidCollision(vector<int> asteroids) {
    vector<int> s; // user vector to simulate a stack
    for (int i = 0; i < asteroids.size(); ++i) {
      const int a = asteroids[i];

      // All positive asteroids, push to the stack
      if (a > 0) {
        s.push_back(a);
        continue;
      }

      // Negative ones? two cases
      if (s.empty() || s.back() < 0) // ..., -2] -3
        s.push_back(a);
      else if (abs(s.back()) <= abs(a)) {
        if (abs(s.back()) < abs(a)) // ..., 2] -3 ==> my current -3 is still alive
          --i;
        s.pop_back(); // ..., 2] gonna have to pop that 2 anyway
      }
      // else ..., 2] -1 ==> do nothing, as -1 will be absorbed
    }
    return s;
  }



  // Solve without division, and in O(n)
  // Build a vector LEFT, records the product of i (not including i)
  // Build a vector RIGHT, and do the same
  // LEFT * RIGHT is the output
  // Time: O(n), Space: O(n)
  vector<int> productExceptSelf(vector<int>& nums) {
    const int size = nums.size();
    vector<int> left(size, 1);
    for (int i = 1; i < size; ++i)
      left[i] = left[i - 1] * nums[i - 1];

    vector<int> right(size, 1);
    for (int i = size - 2; i >= 0; --i)
      right[i] = right[i + 1] * nums[i + 1];

    vector<int> res(size);
    for (int i = 0; i < size; ++i)
      res[i] = left[i] * right[i];
    return res;
  }



};
