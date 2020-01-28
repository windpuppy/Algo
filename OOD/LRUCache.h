#pragma once
#include <unordered_map>
#include <list>

using namespace std;

// Implementation ideas:
// 1. Lots of insert and delete, what data structure? Vector not good, queue not good, LL not powerful enough, yes, doubly LL!
// 2. Need to have control of the head and tail of the list: head for most recent, tail for least recent
//    head: most recent, tail: least recent
// 3. Need to have an overview of all the nodes: map, for O(1) look up!
//    map<key, Node<Key, value>>

// double linked list
template<class K, class V>
struct NodeT {
  K key;
  V value;
  NodeT* next;
  NodeT* prev;

  NodeT(K key, V value) {
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
  using KvPair = list<pair<K, V>>;

public:
  int m_limit; // capacity of the cache
  int m_size;
  NodeT<K, V>* m_head; // most recent
  NodeT<K, V>* m_tail; // least recent
  unordered_map<K, NodeT<K, V>*> m_map;

  LRUCache(int limit) {
    this->m_limit = limit;
    this->m_size = 0;
    this->m_head = NULL;
    this->m_tail = NULL;
  }

  // Note: even for a get, we still need to move the most recently accessed node to the head
  bool get(K key, V& val) {
    if (m_map.find(key) == m_map.end()) {
      val = -1;
      return false;
    }

    NodeT<K, V>* node = m_map[key];
    remove(node);
    append(node);
    val = node->value;
    return true;
  }

  void set(K key, V val) {
    NodeT<K, V>* node = NULL;

    // 1. if key is in the cache, update it
    if (m_map.find(key) != m_map.end()) {
      node = m_map[key];
      node->update(key, val);
      remove(node);
    }

    // 2. if key is not in the cache
    // 2a. if cache not full? just create the node
    else if (m_size < m_limit) {
      node = new NodeT<K, V>(key, val);
    }

    // 2b. if cache is full? need to erase the tail and replace it with the new node
    else {
      node = m_tail; // find the oldest node (tail) to replace with
      remove(node); // isolate it FIRST
      node->update(key, val); // then update its value
      
    }

    // Whatever we do, we need to move the touched node to head because it's most recent
    append(node);
  }

  

private:
  // not actually a remove, but rather a "disconnect and isolate"
  // because we will be re-using its allocated space to hold the new data
  void remove(NodeT<K, V>* node) {
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

  // made the node a head node
  // watch out: special case of empty list
  void append(NodeT<K, V>* node) {
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

private:

  int limit_;
  list<pair<K, V>> nodes_;
  unordered_map<int, It> map_;

  void promote(list<pair<K, V>>::iterator it) {
    auto key = it->first;
    auto val = it->second;
    nodes_.erase(it);
    nodes_insert(nodes_.begin(), { key, val });
    map_[key] = nodes_.begin();
  }
};