#pragma once
#include <map>

using namespace std;

// double linked list
struct Node {
  int key;
  int value;
  Node* next;
  Node* prev;

  Node(int key, int value) {
    this->key = key;
    this->value = value;
    this->next = NULL;
    this->prev = NULL;
  }

  void update(int key, int value) {
    this->key = key;
    this->value = value;
  }
};



class LRUCacheInt {
public:
  int limit; // capacity of the cache
  int size;
  Node* head; // most recent
  Node* tail; // least recent
  map<int, Node*> map;


  LRUCacheInt(int limit) {
    this->limit = limit;
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;
  }

  void set(int key, int value) {
    Node* node = NULL;

    // 1. if key is in the cache, update and move it to the head
    if (map.find(key) != map.end()) {
      node = map[key];
      node->update(key, value);
      remove(node);
    }

    // 2. if key is not in the cache, and cache is full, replace tail with new node and move it to head
    else if (size == limit) {
      node = tail;
      node->update(key, value);
      remove(node);
    }

    // 3. if key is not in the cache, and we have space, just append
    else {
      node = new Node(key, value);
    }

    append(node);
  }

  bool get(int key, int& value) {
    if (map.find(key) == map.end())
      return false;

    Node* node = map[key];
    remove(node);
    append(node);
    value = value;
    return true;
  }



private:
  // remove and isolate
  Node* remove(Node* node) {
    map.erase(node->key);
    size--;

    if (node->prev)
      node->prev->next = node->next;
    if (node->next)
      node->next->prev = node->prev;
    if (node == head)
      head = head->next;
    if (node == tail)
      tail = tail->prev;

    node->next = node->prev = NULL; // isolate it
    return node;
  }

  // append to head
  Node* append(Node* node) {
    map[node->key] = node;
    size++;

    if (!head)
      head = tail = node;
    else {
      node->next = head;
      node->prev = node;
      head = node;
    }
    return node;
  }
};