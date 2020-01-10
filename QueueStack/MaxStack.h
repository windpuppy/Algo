#pragma once

#include <iostream>
#include <map>
#include <list>
#include <vector>

using namespace std;

// doubly linked list for data
// ordered map for values --> iterators mapping
class MaxStack {

  list<int> data; // head of the list: stack top
  map<int, vector<list<int>::iterator>> m;

public:
  MaxStack() {}

  // O(logn)
  void push(int x) {
    data.insert(data.begin(), x);
    m[x].push_back(data.begin());
  }

  // O(logn)
  int pop() {
    // deal with data
    int x = *data.begin();
    data.erase(data.begin()); 

    // deal with map
    m[x].pop_back();
    if (m[x].empty()) m.erase(x); // important!

    return x;
  }

  // O(1)
  int top() {
    return *data.begin();
  }

  // O(1)
  int peekMax() {
    return m.rbegin()->first;
  }

  // O(logn)
  int popMax() {
    // deal with data
    int x = m.rbegin()->first;
    data.erase(m[x].back());

    // deal with map
    m[x].pop_back();
    if (m[x].empty()) m.erase(x);

    return x;
  }
  
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */