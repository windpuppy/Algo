#pragma once
#include <unordered_map>
#include <list>

using namespace std;

// Implementation ideas:
// 1. Lots of insert and delete, what data structure? Vector not good, queue not good, LL not powerful enough, yes, doubly LL!
// 2. Need to have control of the head and tail of the list: head for most recent, tail for least recent
// 3. Need to have an overview of all the nodes: map, for O(1) look up!
//    map<key, Node<Key, value>>

template<class K, class V>
class LRUCache {

public:

	LRUCache(int limit) {
		this->limit_ = limit;
	}

	// Note: even for a get, we still need to move the most recently accessed node to the head
	bool get(K key, V& val) {
		if (!map_.count(key))
			return false;

		It it = map_[key];
		promote(it);
		val = nodes_.begin()->second;
		return true;
	}

	void set(K key, V val) {
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

	int limit_;
	list<pair<K, V>> nodes_;
	typedef typename list<pair<K, V>>::iterator It;
	unordered_map<int, It> map_;

	void promote(It it) {
		auto key = it->first;
		auto val = it->second;
		nodes_.erase(it);
		nodes_.insert(nodes_.begin(), { key, val }); // promote it to the head
		map_[key] = nodes_.begin();
	}

	void evict() {
		auto key = nodes_.back().first;
		nodes_.pop_back();
		map_.erase(key);
	}
};