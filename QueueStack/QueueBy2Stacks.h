#pragma once

#include <iostream>
#include <stack>

using namespace std;

// Implementation notes:
// use two stacks, s1 for data, s2 for cache
// top of s1 is the queue head
//
// Content in the stack:
// (queue head)
// item 1
// item 2
// item 3
// (queue end)
//
// only tricky operation: push
// when we push, we first put the entire s1 into s2, add new element to the bottom of s1 (simulated queue end), then put s2 back into s1

class QueueBy2Stacks
{
  stack<int> s1; // Data
  stack<int> s2; // Cache

public:
  QueueBy2Stacks() {};
  virtual ~QueueBy2Stacks() { while (!s1.empty()) s1.pop(); }

  void pop()
  {
    if (!s1.empty()) s1.pop();
  }

  int front()
  {
    if (s1.empty()) return -1;
    return s1.top();
  }

  void push(int element)
  {
    // Cache entire s1 into s2
    while (!s1.empty()) {
      s2.push(s1.top());
      s1.pop();
    }
    // Add element
    s2.push(element);
    // Put s2 back into s1
    while (!s2.empty()) {
      s1.push(s2.top());
      s2.pop();
    }
  }

  int size()
  {
    return (int)s1.size();
  }

  bool isEmpty()
  {
    return s1.empty();
  }

  void printStack(int n)
  {
    for (auto i = 0; i < n; ++i)
    {
      cout << front() << endl;
      pop();
    }
  }

};
