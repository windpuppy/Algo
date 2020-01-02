#pragma once

#include <vector>
#include <stack>


// Input: [[1,1],2,[1,1]]
// Output: [1, 1, 2, 1, 1]
// By calling next(), it repeatedly reads the next integer until hasNext() returns false


 // This is the interface that allows for creating nested lists.
 // You should not implement it, or speculate about its implementation
 class NestedInteger {
 public:
   // Return true if this NestedInteger holds a single integer, rather than a nested list.
   bool isInteger() const {};

   // Return the single integer that this NestedInteger holds, if it holds a single integer
   // The result is undefined if this NestedInteger holds a nested list
   int getInteger() const {};

   // Return the nested list that this NestedInteger holds, if it holds a nested list
   // The result is undefined if this NestedInteger holds a single integer
   const vector<NestedInteger>& getList() const {};
 };

using namespace std;

class NestedIterator {
  stack<NestedInteger> stack;

public:
  // Push the entire vector of NestedInteger into the stack, vector front => stack top
  NestedIterator(vector<NestedInteger>& nestedList) {
    for (int i = nestedList.size() - 1; i >= 0; --i)
      stack.push(nestedList[i]);
  }

  // Job: other than return a boolean, it also makes sure at the top of the stack, the NestedInteger is always a real integer.
  // If not, that means the top of the stack is a nested list - we pop it, push all its components back into the stack, recursively until we see a real integer
  bool hasNext() {
    while (!stack.empty()) {
      NestedInteger curr = stack.top();
      if (curr.isInteger()) return true;

      // Do the following when !curr.isInteger()
      stack.pop();
      auto nums = curr.getList();
      for (int i = nums.size() - 1; i >= 0; --i)
        stack.push(nums[i]);
    }
    return false;
  }

  // next() is always called after hasNext(), which means when next() is being called:
  // 1. the stack is not empty
  // 2. the stack top is a real integer
  int next() {
    int num = stack.top().getInteger();
    stack.pop();
    return num;
  }
};