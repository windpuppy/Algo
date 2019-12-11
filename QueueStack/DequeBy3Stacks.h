#pragma once

#include <iostream>
#include <stack>
#include <deque>
using namespace std;

// Implementation details:
// Use left and right deque to simulate a whole deque, buffer as buffer
// The idea is when either of the left or right becomes empty, we need to call the move() method
//    to move half of the left/right to the other side, such as
//    1, 2, 3, 4 --- 5, 6, 7, 8
//    if it becomes
//    1, 2, 3, 4
//    we need to make it like this
//    1, 2 --- 3, 4
//
// Steps:
// 1 and 2 to buffer, 3 and 4 to right, buffer (1 and 2) to left

class DequeBy3Stacks
{
  stack<int> left;
  stack<int> right;
  stack<int> buffer;

public:

  void push_front(int val) {
    left.push(val);
  }

  void push_back(int val) {
    right.push(val);
  }

  void pop_front() {
    move(left, right);
    if (!right.empty()) right.pop();
  }

  void pop_back() {
    move(right, left);
    if (!left.empty()) left.pop();
  }

  int front() {
    move(right, left);
    return left.empty() ? -1 : left.top();
  }

  int back() {
    move(left, right);
    return right.empty() ? -1 : right.top();
  }

  size_t size() {
    return left.size() + right.size();
  }
  
  bool empty() {
    return left.empty() && right.empty();
  }

private:
  // Move half src to dst, if dst not empty
  void move(stack<int>& src, stack<int>& dst) {
    if (!dst.empty()) return;

    // 1st half src to buffer
    int halfSize = src.size() / 2;
    for (int n = 0; n < halfSize; ++n) {
      buffer.push(src.top());
      src.pop();
    }

    // 2jd half src to dst
    while (!src.empty()) {
      dst.push(src.top());
      src.pop();
    }


    // buffer to src
    while (!buffer.empty()) {
      src.push(buffer.top());
      buffer.pop();
    }
  }


};
