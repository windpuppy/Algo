#pragma once

#include <iostream>
#include <stack>

struct StackNode {
  int value;
  int min;
  StackNode* next;
  StackNode(int v) {
    value = v;
    next = NULL;
  }
};

// Implementation notes:
// Simulate a stack with linked list. Top of the stack is the head.
// Node structure has an extra field - min.
// When pushing in a new element, compare it's value vs head, update the min
// That way we guarantee the node at the top of the stack has a global min value in its .min property

class StackWithMin {
  StackNode* head;

public:
  StackWithMin() { head = NULL; }

  ~StackWithMin() {
    while (head) {
      StackNode* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(int d) {
    auto node = new StackNode(d);
    node->next = head;
    if (!head) // brand new node, must be min
      node->min = d;
    else
      node->min = d < head->min ? d : head->min;
    head = node;
  }

  void pop() {
    if (!head) return;
    StackNode* temp = head;
    head = head->next;
    delete temp;
  }

  int top() {
    if (!head) return -1;
    return head->value;
  }

  int min() {
    if (!head) return -1;
    return head->min;
  }
};
