#pragma once
#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

// Design a class to implement two API calls:
// 1) read(char ch), to read a char
// 2) firstNonRepeating(), to return the first non-repeating char in this stream
// Both needs to have O(1) time
// e.g. read:              a b c a c c b
//      firstNonRepeating: a a a b b b null

// Use doubly linked list to store all non-repeating characters
// doubly LL :  from oldest (left) to newest (right)
// found a repeating char? delete it in LL
// found a non-repeating char? insert it
//
// Data structures used:
// doubly LL: to contain all UNIQUE chars
// hashmap<char, node>: eg. <a,null> <b,null> <c,null> <d,N4> d is the first non-repeating
// case 1: if a char doesn't exist in map? new char
// case 2: if a char exists in map, and its value is not null? it has appeared ONCE, so this new incoming one is a repeating, make it null
// case 3: if a char exists in map, and its value is null? it has appeared more than once

class FirstNonRepeating {
public:
  FirstNonRepeating() {
    nodes_.push_back(' ');
  }

  void read(char ch) {
    if (repeated_.count(ch)) // repeating char, do nothing
      return;

    if (!singled_.count(ch)) {
      nodes_.push_back(ch);
      singled_[ch] = --nodes_.end();
    }
    else {
      nodes_.erase(singled_[ch]);
      singled_.erase(ch);
      repeated_.insert(ch);
    }
  }

  char firstNonRepeating() {
    if (nodes_.size() == 1)
      return ' ';
    auto it = nodes_.begin();
    advance(it, 1);
    return *it;
  }

private:
  list<char> nodes_;
  unordered_map<char, list<char>::iterator> singled_;
  unordered_set<char> repeated_;
};


