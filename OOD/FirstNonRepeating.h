#pragma once
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Use doubly linked list to store all non-repeating characters
// doubly LL :  from oldest (left) to newest (right)
// found a repeating char? delete it in LL
// found a non-repeating char? insert it
//
// Data structures used:
// doubly LL: nodes
// hashmap<char, node>: eg. <a,null> <b,null> <c,null> <d,N4> d is the first non-repeating
// case 1: if a char doesn't exist in map? new char
// case 2: if a char exists in map, and its value is not null? it has appeared once, so this new incoming one is a repeating, make it null
// case 3: if a char exists in map, and its value is null? it has appeared more than once

// doubly linked list
struct NodeC {
  char ch;
  NodeC* next;
  NodeC* prev;

  NodeC(char c) {
    this->ch = c;
    this->next = NULL;
    this->prev = NULL;
  }

  void update(char c) {
    this->ch = c;
  }
};



class FirstNonRepeating {
  NodeC* head;
  NodeC* tail;
  unordered_map<char, NodeC*> singled; // first appearance? push node in; second appearance? replace node with NULL
  unordered_set<char> repeated; // a set that contains all the repeated nodes

public:
  FirstNonRepeating() {
    tail = new NodeC(' ');
    tail->next = tail->prev = tail;
    head = tail;
  }

  void read(char ch) {
    if (repeated.find(ch) != repeated.end()) // repeating char, do nothing
      return;
    NodeC* node = singled[ch];
    if (node == NULL) {
      node = new NodeC(ch);
      append(node);
    }
    else
      remove(node);
  }

  char firstNonRepeating() {
    if (head == tail)
      return ' ';
    return head->next->ch;
  }



private:
  void append(NodeC* node) {
    singled[node->ch] = node;
    tail->next = node;
    node->prev = tail;
    node->next = head;
    tail = tail->next;
  }

  void remove(NodeC* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (node == tail)
      tail = node->prev;
    node->prev = node->next = NULL; // isolate
    repeated.insert(node->ch);
    singled.erase(node->ch);
  }
};


