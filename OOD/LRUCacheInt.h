#pragma once
#include <unordered_map>

using namespace std;

// Implementation ideas:
// 1. Lots of insert and delete, what data structure? Vector not good, queue not good, LL not powerful enough, yes, doubly LL!
// 2. Need to have control of the head and tail of the list: head for most recent, tail for least recent
// 3. Need to have an overview of all the nodes: map, for O(1) look up!
//    map<key, Node<Key, value>>

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
		if (nodes_.size() == limit_)
			evict();
		nodes_.insert(nodes_.begin(), { key, val });
		map_[key] = nodes_.begin();
	}

private:

	int limit_; // capacity of the cache
	list<pair<int, int>> nodes_; // nodes of <key, value> pair
	typedef list<pair<int, int>>::iterator It;
	unordered_map<int, It> map_;

	void promote(It it) {
		int key = it->first;
		int val = it->second;
		nodes_.erase(it);
		nodes_.insert(nodes_.begin(), { key, val }); // promote it to the head
		map_[key] = nodes_.begin();
	}

	void evict() {
		int key = nodes_.back().first;
		nodes_.pop_back();
		map_.erase(key);
	}
};