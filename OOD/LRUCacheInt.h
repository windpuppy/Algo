#pragma once
#include <unordered_map>

using namespace std;

// doubly linked list
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
  int m_limit; // capacity of the cache
  int m_size;
  Node* m_head; // most recent
  Node* m_tail; // least recent
  unordered_map<int, Node*> m_map;


  LRUCacheInt(int limit) {
    this->m_limit = limit;
    this->m_size = 0;
    this->m_head = NULL;
    this->m_tail = NULL;
  }

  void set(int key, int val) {
    Node* node = NULL;

    // 1. if key is in the cache, update and move it to the head
    if (m_map.find(key) != m_map.end()) {
      node = m_map[key];
      node->update(key, val);
      remove(node);
    }

    // 2. if key is not in the cache
    // 2a. if cache not full? just create the node
    else if (m_size < m_limit) {
      node = new Node(key, val);
    }

    // 2b. if cache is full? need to erase the tail and replace it with the new node
    else {
      node = m_tail; // find the oldest node (tail) to replace with
      remove(node); // isolate it FIRST
      node->update(key, val); // then update its value
    }

    append(node);
  }

  bool get(int key, int& val) {
    if (m_map.find(key) == m_map.end())
      return false;

    Node* node = m_map[key];
    remove(node);
    append(node);
    val = node->value;
    return true;
  }



private:
  // remove and isolate
  void remove(Node* node) {
    m_map.erase(node->key);
    m_size--;

    if (node->prev)
      node->prev->next = node->next;
    if (node->next)
      node->next->prev = node->prev;
    if (node == m_head)
      m_head = m_head->next;
    if (node == m_tail)
      m_tail = m_tail->prev;

    node->next = node->prev = NULL; // isolate it
  }

  // append to head
  void append(Node* node) {
    m_map[node->key] = node;
    m_size++;

    if (!m_head)
      m_head = m_tail = node;
    else {
      node->next = m_head;
      m_head->prev = node;
      m_head = node;
    }
  }
};