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
  vector<int> data_;
  unordered_map<int, int> map_;

public:
  RandomizedSet() {
    srand(time(NULL));
  }

  // O(1) insert
  // Return false if val already exists, otherwise insert and return true
  bool insert(int val) {
    if (map_.count(val)) return false;

    data_.push_back(val);
    map_[val] = data_.size() - 1;
    return true;
  }

  // O(1) delete
  // Return false if val doesn't exist, otherwise remove it and return true
  bool remove(int val) {
    auto it = map_.find(val);
    if (it == map_.end()) return false;

    // grab the tail item to current index, and update map
    int index = it->second;
    int tail = data_.back();
    data_[index] = tail;
    map_[tail] = index;
    data_.pop_back();

    map_.erase(it); // clean up
    return true;
  }

  // O(1) rand
  int getRandom() {
    int pos = rand() % data_.size();
    return data_[pos];
  }
};