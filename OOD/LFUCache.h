#pragma once

#include <list>
#include <unordered_map>

using namespace std;

// Design LFU cache, which supports both get() and set() with O(1) time
// Note: 1. every get should increase the frequency of this key
//       2. when removing the least frequent used key and multiple keys have the same frequency - use LRU as tie breaker
//
// Implementation:
//
// head --- 1 --- 3 --- 5      frequencies            ===> Iit (more frequent)
//          |     |     |                           ||
//        (2,3) (4,3) (1,2)   (key,value) pair      Jit
//                |                                 (newer)
//              (3,7)
// Vertically, we call each node LRUNode, which contains list<pair<int,int>>, list of key-value pair,
// Horizontally, we store a list<LRUNode>
// both directions are doubly linked list (that's how C++ STL implements list)
// Then we user a global unordered_map<int, pair<Iit, Jit>>, where int is key, Iit and Jit are iterators along both directions
//    with this hashmap, we gain global control of all keys

struct LRUNode {
  int freq;
  list<pair<int, int> > vNodes;
  LRUNode(int f = 0) : freq(f) { }
};

typedef list<LRUNode>::iterator Iit;
typedef list<pair<int, int> >::iterator Jit;

class LFUCache {
private:
  list<LRUNode> m_nodes;
  int m_capacity;
  unordered_map<int, pair<Iit, Jit>> m_map;

public:
  LFUCache(int capacity) : m_capacity(capacity) {}

  // O(1) Get the node, also increment its frequency
  int get(int key) {
    int val = -1;

    if (m_map.find(key) != m_map.end()) {
      m_map[key] = promote(key); // promote the key to the next frequency bucket
      val = m_map[key].second->second;
    }

    return val;
  }

  // O(1) Set the node, also increment its frequency
  void put(int key, int value) {
    if (m_capacity <= 0) return;

    if (m_map.find(key) == m_map.end()) {
      if (m_map.size() == m_capacity)
        evict();
      m_map[key] = insert(key, value);
    }
    else {
      m_map[key] = promote(key);
      m_map[key].second->second = value;
    }
  }



private:

  // O(1) insert a brand new node (freq = 1)
  // Returns its 2D position
  pair<Iit, Jit> insert(int key, int val) {
    Iit i = m_nodes.begin();
    if (i == m_nodes.end() || i->freq != 1) // insert if empty, or the first freq node is not 1 (if 1, just connect below)
      i = m_nodes.insert(i, LRUNode(1));

    Jit j = i->vNodes.insert(i->vNodes.end(), { key, val });
    return { i, j };
  }

  // O(1) remove a node at the lowest frequency, least recent
  void evict() {
    Iit i = m_nodes.begin();
    Jit j = i->vNodes.begin();
    m_map.erase(j->first);

    i->vNodes.erase(j); // remove node
    if (i->vNodes.empty()) // remove empty bucket
      m_nodes.erase(i);
  }

  // O(1) promote a node to the "frequency + 1" place (might or might not exist in the current frequency list)
  // also put it at the bottom of that frequency bucket - because it's the newest!
  pair<Iit, Jit> promote(int key) {
    Iit i; Jit j;
    std::tie(i, j) = m_map[key];
    Iit iNext = next(i);

    int val = j->second;
    int freq = i->freq + 1;

    // erase current node, if no more left in this frequency bucket, erase this bucket as well
    i->vNodes.erase(j);
    if (i->vNodes.empty())
      m_nodes.erase(i);

    // relocate i: if we reach pass the frequency end, or find a new frequency slot is needed?
    if (iNext == m_nodes.end() || iNext->freq != freq)
      i = m_nodes.insert(iNext, LRUNode(freq));
    else i = iNext;

    // relocate j: push to the bottom at the frequency bucket, because it's the newlest
    j = i->vNodes.insert(i->vNodes.end(), { key, val });
    return { i, j };
  }
};