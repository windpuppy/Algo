#pragma once

#include <vector>
#include <unordered_map>
#include <ctime>

// Task: design a data structure that supports O(1) insert, delete, random. Random needs to return a number from the set, with EQUAL probability
// Implementation: use vector and unordered_map
// vector: store data
// unoreded_map: key: data, value: it's index in the vector
// When we insert, we always insert to the back of the vector
// When we delete, instead of deleting from the middle of the vector, we copy the vector's last element to the "to be deleted" index, then remove last element

using namespace std;

class RandomizedSet {
  vector<int> m_data;
  unordered_map<int, int> m_map;

public:
  RandomizedSet() {
    srand(time(NULL));
  }

  // O(1) insert
  // Return false if val already exists, otherwise insert and return true
  bool insert(int val) {
    if (m_map.count(val)) return false;

    m_data.push_back(val);
    m_map[val] = m_data.size() - 1;
    return true;
  }

  // O(1) delete
  // Return false if val doesn't exist, otherwise remove it and return true
  bool remove(int val) {
    auto it = m_map.find(val);
    if (it == m_map.end()) return false;

    int pos = it->second;
    m_data[pos] = m_data.back();
    m_data.pop_back();

    m_map[m_data[pos]] = pos; // update map
    m_map.erase(it);
    return true;
  }

  // O(1) rand
  int getRandom() {
    int pos = rand() % m_data.size();
    return m_data[pos];
  }
};