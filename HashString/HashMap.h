#pragma once

#include <vector>
#include <string>
#include <deque>
#include <functional>

using namespace std;

const int DEFAULT_CAP = 16;
const float DEFAULT_LOAD_FACTOR = 0.75f;

struct Node
{
  Node* next;
  string key;
  int value;
  Node(string k, int v) : key(key), value(v), next(NULL) {};
};

class HashMap {

public:

  static const int DEFAULT_CAP;
  static const float DEFAULT_LOAD_FACTOR;

private:
  vector<Node*> m_nodes;
  size_t m_size;
  float m_loadFactor;

public:
  HashMap() {
    HashMap(DEFAULT_CAP, DEFAULT_LOAD_FACTOR);
  }

  HashMap(int cap, float loadFactor) {
    if (cap <= 0)
      throw std::exception("Capacity cannot be <= 0");
    m_nodes.resize(cap); // a vector of NULL
    m_size = 0;
    m_loadFactor = loadFactor;
  }

  virtual ~HashMap() {}

  size_t size() {
    return m_size;
  }

  bool isEmpty() {
    return m_nodes.empty();
  }

  void clear() {
    m_nodes.assign(size(), (Node*)NULL);
  }


  // Hash to get index, traverse LL, average O(1)
  bool containsKey(string key) {
    if (isEmpty())
      return false;

    auto index = getIndex(key); // hash
    auto node = m_nodes[index]; // get bucket

    // iterate linked list
    while (node) {
      if (node->key == key)
        return true;
      node = node->next;
    }
    return false;
  }

  // Traverse nodes, traverse LL, O(n)
  bool containsValue(int value) {
    if (isEmpty())
      return false;

    for (auto& n : m_nodes) {
      while (n) {
        if (n->value == value)
          return true;
        n = n->next;
      }
    }
    return false;
  }

  // Hash to get index, traverse LL
  int get(string key) {
    auto index = getIndex(key);
    auto node = m_nodes[index];

    while (node) {
      if (node->key == key)
        return node->value;
      node = node->next;
    }
    return -1;
  }

  // Insert/Update
  // If key exists, update, return the old value
  // If not exists, insert, return -1
  int put(string key, int value) {
    auto index = getIndex(key);
    auto head = m_nodes[index];
    auto curr = head;

    while (curr) {
      if (curr->key == key) {
        int ret = curr->value;
        curr->value = value;
        return ret;
      }
      curr = curr->next;
    }

    // not exist, append
    auto newNode = new Node(key, value);
    newNode->next = head;
    m_nodes[index] = newNode;
    m_size++;
    //// optional:
    //if (needRehashing()
    //  rehash();
    return -1;
  }

  // If key exists, remove entry from map
  // If not exists, return -1
  int remove(string key) {
    auto index = getIndex(key);
    auto node = m_nodes[index];
    auto prev = node;

    while (node) {
      if (node->key == key) {
        int ret = node->value;
        prev->next = node->next;
        m_size--;
        return ret;
      }
    }

    // not found
    return -1;
  }

private:

  size_t getIndex(string key) {
    auto code = std::hash<string>()(key);
    return code % m_nodes.size();
  }

  bool needRehashing() {
    float ratio = (float)m_size / m_nodes.size();
    return ratio >= m_loadFactor;
  }

  void rehash() {
    // expand m_nodes
    // copy m_nodes to the expanded m_nodes, calling put()
  }
};
