#pragma once

#include <iostream>


class Node {
public:
  int value;
  Node* next;
  Node(int value) : value(value), next(NULL) {}
};

class StackByLinkedList {
  Node* head;

public:
  int pop() {
    if (!head) return -1;
    Node* curr = head;
    head = head->next;
    curr->next = NULL;
    return curr->value;
  }

  void push(int val) {
    Node* curr = new Node(val);
    curr->next = head;
    head = curr;
  }

  int peek() {
    return head ? head->value : -1;
  }
};
