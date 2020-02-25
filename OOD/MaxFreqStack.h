#pragma once

#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

// Requirement
// MaxFreqStack has two functions:
// push(int x), which pushes an integer x onto the stack.
// pop(), which removes and returns the most frequent element in the stack.
// If there is a tie for most frequent element, the element closest to the top of the stack is removed and returned.
// 
// Solution:
// Hash map freq will count the frequence of elements.
// Hash map map is a map of stack.
// If element x has n frequence, we will push x n times in m[1], m[2] ..m[n]
// maxfreq records the maximum frequence.
// push(x) will push x to map[++freq[x]]
// pop() will pop from the map[maxfreq]

class MaxFreqStack {
  unordered_map<int, int> values_; // <value, freqency of that value>
  unordered_map<int, stack<int>> freqs_; // <freq, values with that freq>
  int maxFreq_ = 0;

public:
  void push(int x) {
    int f = ++values_[x];
    freqs_[f].push(x);
    maxFreq_ = max(maxFreq_, f);
  }

  int pop() {
    int x = freqs_[maxFreq_].top();
    freqs_[maxFreq_].pop();

    int f = values_[x]--; // assign first, then --
    if (freqs_[f].empty())
      maxFreq_--;
    return x;
  }
};