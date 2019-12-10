#pragma once

#include <iostream>

class Node {
public:

  int value;
  Node* next;
public:
  Node(int value) { this->value = value; }
};

class QueueByLinkedList {
public:
  Node* head;
  Node* tail;

  // Pop from front
  int pop() {
    if (!head) return -1;
    Node* curr = head;
    head = head->next;
    if (head == NULL) tail = NULL; // when head meets tail (ie. single element)
    curr->next = NULL;
    return curr->value;
  }

  // Push from tail
  void push(int val) {
    Node* curr = new Node(val);
    tail->next = curr;
  }

  int front() {
    if (!head) return -1;
    return head->value;
  }

};
