#pragma once

#include <iostream>
#include <deque>

using namespace std;

// use queue to simulate a stack, nothing special
class StackByQueues
{
  deque<int*> queue; // Data

public:
  StackByQueues() {};
  virtual ~StackByQueues() {
    for (size_t n = 0; n != queue.size(); ++n)
      delete queue[n];
    queue.clear();
  }

  void push(int x) {
    int* val = new int(x);
    queue.push_front(val);
  }

  int* pop() {
    if (queue.empty()) return NULL;

    int* val = new int(*queue.front());
    queue.pop_front();
    return val;
  }

  int* top() {
    if (queue.empty()) return NULL;

    int* val = new int(*queue.front());
    return val;
  }

  bool isEmpty() {
    return queue.empty();
  }

};
