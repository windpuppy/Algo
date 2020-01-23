#pragma once
#include <unordered_map>

using namespace std;

class LRUCacheInt {
public:

  LRUCacheInt(int limit) {
    this->limit_ = limit;
  }

  bool get(int key, int& val) {
    if (!map_.count(key))
      return false;

    It it = map_[key];
    promote(it);
    val = nodes_.begin()->second;
    return true;
  }

  void set(int key, int val) {
    // if key is in the cache, just update and promote to head
    if (map_.count(key)) {
      It it = map_[key];
      it->second = val;
      promote(it);
      return;
    }

    // if cache is full, we need to evict one from the tail
    if (nodes_.size() == limit_) {
      int evictKey = nodes_.back().first;
      nodes_.pop_back();
      map_.erase(evictKey);
    }
    nodes_.insert(nodes_.begin(), { key, val });
    map_[key] = nodes_.begin();
  }

private:

  int limit_; // capacity of the cache
  list<pair<int, int>> nodes_; // nodes of <key, value> pair
  typedef list<pair<int, int> >::iterator It;
  unordered_map<int, It> map_;

  void promote(It it) {
    int key = it->first;
    int val = it->second;
    nodes_.erase(it);
    nodes_.insert(nodes_.begin(), { key, val }); // promote it to the head
    map_[key] = nodes_.begin();
  }
};