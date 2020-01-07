#pragma once

#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

// Requirement
// MaxFreqStack has two functions:
// push(int x), which pushes an integer x onto the stack.
// pop(), which removes and returns the most frequent element in the stack.
// If there is a tie for most frequent element, the element closest to the top of the stack is removedand returned.
// 
// Solution:
// Hash map freq will count the frequence of elements.
// Hash map map is a map of stack.
// If element x has n frequence, we will push x n times in m[1], m[2] ..m[n]
// maxfreq records the maximum frequence.
// push(x) will push x to map[++freq[x]]
// pop() will pop from the map[maxfreq]

class MaxFreqStack {
  unordered_map<int, int> m_freq; // <val, freq>
  unordered_map<int, stack<int>> m_map; // <freq, elements with that freq>
  int m_maxFreq = 0;

public:
  void push(int x) {
    int f = ++m_freq[x];
    m_map[f].push(x);
    m_maxFreq = max(m_maxFreq, f);
  }

  int pop() {
    int x = m_map[m_maxFreq].top();
    m_map[m_maxFreq].pop();

    if (m_map[m_freq[x]--].empty()) m_maxFreq--;
    return x;
  }
};