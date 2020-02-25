#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

// Implement a data structure supporting the following operations with O(1) time:
// Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
// Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1.
//   If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
// GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
// GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".

// Implementation:
// For each value, create a bucket that contains all the keys of that value (using a hashset for those keys, to support O(1) add/delete/find)
// Hold a list of buckets, sorted by the bucket value
class AllOne {

  struct Bucket {
    int value;
    unordered_set<string> keys; // we do not care about the order of those keys
  };

private:
  list<Bucket> buckets_;
  unordered_map<string, list<Bucket>::iterator> map_; // given a key, O(1) locate its containing bucket

public:

  AllOne(){}

  // Insert if new, plus one if existing
  void inc(string key) {
    // A new key? Create it with value 0, add to map
    if (!map_.count(key)) {
      auto it = buckets_.insert(buckets_.begin(), { 0, {key} });
      map_[key] = it;
    }

    // Insert the key in the next bucket (create one if it does not exist), update map
    auto curr = map_[key], next = curr;
    next++;
    int newVal = curr->value + 1;
    if (next == buckets_.end() || next->value > newVal) // (bucket value + 1) does not exist
      next = buckets_.insert(next, { newVal, {} });
    next->keys.insert(key);
    map_[key] = next;

    // Erase the key from the old bucket
    curr->keys.erase(key);
    if (curr->keys.empty())
      buckets_.erase(curr);
  }

  // Delete if value is 1, decrease one otherwise
  // Do nothing if key does not exist
  void dec(string key) {
    // If key doesn't exist, do nothing
    if (!map_.count(key)) return;

    // Insert the key in the previous bucket (create one if it does not exist), update map
    auto curr = map_[key], prev = curr;
    prev--;
    map_.erase(key);
    if (curr->value > 1) {
      int newVal = curr->value - 1;
      if (curr == buckets_.begin() || prev->value < newVal) // (bucket value - 1) does not exist
        prev = buckets_.insert(curr, { newVal, {} });
      prev->keys.insert(key);
      map_[key] = prev;
    }

    // Erase the key from the old bucket
    curr->keys.erase(key);
    if (curr->keys.empty())
      buckets_.erase(curr);
  }

  // Get key of the max value
  string getMaxKey() {
    return buckets_.empty() ? "" : *(buckets_.rbegin()->keys.begin());
  }

  // Get key of the min value
  string getMinKey() {
    return buckets_.empty() ? "" : *(buckets_.begin()->keys.begin());
  }

};