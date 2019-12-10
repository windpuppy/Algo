#pragma once
#include <map>

using namespace std;

// double linked list
template<class K, class V>
struct Node {
  K key;
  V value;
  Node* next;
  Node* prev;

  Node(K key, V value) {
    this->key = key;
    this->value = value;
    this->next = NULL;
    this->prev = NULL;
  }

  void update(K key, V value) {
    this->key = key;
    this->value = value;
  }
};



template<class K, class V>
class LRUCache {
public:
  int limit; // capacity of the cache
  int size;
  Node<K, V>* head; // most recent
  Node<K, V>* tail; // least recent
  map<K, Node<K, V>*> map;


  LRUCache(int limit) {
    this->limit = limit;
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;
  }

  void set(K key, V value) {
    Node<K, V>* node = NULL;

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
      node = new Node<K, V>(key, value);
    }

    append(node);
  }

  bool get(K key, V& value) {
    if (map.find(key) == map.end())
      return false;

    Node<K, V>* node = map[key];
    remove(node);
    append(node);
    value = value;
    return true;
  }



private:
  // remove and isolate
  Node<K, V>* remove(Node<K, V>* node) {
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
  Node<K, V>* append(Node<K, V>* node) {
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