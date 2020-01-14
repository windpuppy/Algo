#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

// Design a class that supports all following 4 operations with O(1) time

// Implementation:
// For each value, create a bucket that contains all the keys of that value (using a hashset for those keys, to support O(1) add/delete/find)
// Hold a list of buckets, sorted by the bucket value
class AllOne {

  struct Bucket {
    int value;
    unordered_set<string> keys;
  };

private:
  list<Bucket> buckets;
  unordered_map<string, list<Bucket>::iterator> map;

public:

  AllOne(){}

  // Insert if new, plus one if existing
  void inc(string key) {
    // A new key? Create it with value 0, add to map
    if (!map.count(key)) {
      auto it = buckets.insert(buckets.begin(), { 0, {key} });
      map[key] = it;
    }

    // (Optional) insert the key in the next bucket, update map
    auto curr = map[key], next = curr;
    next++;
    int newVal = curr->value + 1;
    if (next == buckets.end() || next->value > newVal) // (bucket value + 1) does not exist
      next = buckets.insert(next, { newVal, {} });
    next->keys.insert(key);
    map[key] = next;

    // Erase the key from the old bucket
    curr->keys.erase(key);
    if (curr->keys.empty())
      buckets.erase(curr);
  }

  // Delete if value is 1, decrease one otherwise
  // Do nothing if key does not exist
  void dec(string key) {
    // If key doesn't exist, do nothing
    if (!map.count(key)) return;

    // (Optional) insert the key in the previous bucket, update map
    auto curr = map[key], prev = curr;
    prev--;
    map.erase(key);
    if (curr->value > 1) {
      int newVal = curr->value - 1;
      if (curr == buckets.begin() || prev->value < newVal) // (bucket value - 1) does not exist
        prev = buckets.insert(curr, { newVal, {} });
      prev->keys.insert(key);
      map[key] = prev;
    }

    // Erase the key from the old bucket
    curr->keys.erase(key);
    if (curr->keys.empty())
      buckets.erase(curr);
  }

  // Get key of the max value
  string getMaxKey() {
    return buckets.empty() ? "" : *(buckets.rbegin()->keys.begin());
  }

  // Get key of the min value
  string getMinKey() {
    return buckets.empty() ? "" : *(buckets.begin()->keys.begin());
  }

};