#pragma once

#include <unordered_map>
#include <map>

using namespace std;

// Design a time based key-value store that supports:
// 1. set(string key, string value, int timestamp)
// 2. get(string key, int timestamp)
// when get is called and if the key has multiple values, return the one with latest timestamp that <= given timestap; if no values, return ""
//
// Here we use a small trick by pushing minus timestamp into the map, for easy lookup with map::lower_bound(int)
// -3  <== lower_bound(-3)
// -2
// -1

class TimeMap {
  unordered_map<string, map<int, string>> m; // <key, map<timestamp, value>>

public:
  TimeMap() {}

  // O(1)
  void set(string key, string value, int timestamp) {
    m[key][-timestamp] = value;
  }

  // O(logn)
  string get(string key, int timestamp) {
    auto i = m.find(key);
    if (i == m.end()) return "";

    auto& inner_map = i->second; // map<time, value>
    auto j = inner_map.lower_bound(-timestamp);
    return j == inner_map.end() ? "" : j->second;
  }
};