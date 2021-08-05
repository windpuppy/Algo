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
//        (b,3) (d,3) (a,2)   (key,value) pair      Jit
//                |                                 (more recent)
//              (c,7)
// Vertically, we contain a list of LRU nodes with list<pair<int,int>>, ie list of key-value pair. We call such a bucket.
// Horizontally, we store a list of buckets.
// both directions are doubly linked list.
// Then we use a global unordered_map<int, pair<Iit, Jit>> to gain O(1) access of all nodes.
//    where int is key, Iit and Jit are iterators along both directions

typedef pair<string, int> Node; // <key, value>

struct Bucket {
	int freq;
	list<Node> nodes;
	Bucket(int f = 0) : freq(f) { }
};

typedef list<Bucket>::iterator Iit;
typedef list<Node>::iterator Jit;

class LFUCache {
public:
	LFUCache(int limit) : limit_(limit) {}

	// O(1) Get the node, also increment its frequency
	int get(string key) {
		int val = -1;

		if (map_.count(key)) {
			auto it = promote(key); // promote the key to the next frequency bucket
			map_[key] = it;
			val = map_[key].second->second;
		}

		return val;
	}

	// O(1) Set the node, also increment its frequency
	void put(string key, int value) {
		if (limit_ <= 0) return;

		if (!map_.count(key)) { //  need to worry about cache being full
			if (map_.size() == limit_)
				evict();
			map_[key] = insert(key, value);
		}
		else { // no need to worry about cache being full
			map_[key] = promote(key);
			map_[key].second->second = value;
		}
	}

private:

	list<Bucket> buckets_;
	int limit_;
	unordered_map<string, pair<Iit, Jit>> map_;

	// O(1) insert
	// insert a brand new node (freq = 1)
	// returns its 2D position, a 2D iterator
	pair<Iit, Jit> insert(string key, int val) {
		Iit i = buckets_.begin();
		if (i == buckets_.end() || i->freq != 1) // insert if empty, or the first freq node is not 1 (if 1, just connect below)
			i = buckets_.insert(i, Bucket(1));

		Jit j = i->nodes.insert(i->nodes.end(), { key, val });
		return { i, j };
	}

	// O(1) evict
	// remove a node at the lowest frequency
	// if there is a tie, remove the least recent
	// if that frequency bucket becomes empty, remove the bucket as well
	void evict() {
		Iit i = buckets_.begin();
		Jit j = i->nodes.begin();
		map_.erase(j->first);

		i->nodes.erase(j); // remove node
		if (i->nodes.empty()) // remove empty bucket
			buckets_.erase(i);
	}

	// O(1) promote
	// promote a node to its next frequency bucket (that bucket might not exist in the current bucket chain)
	// also put it at the bottom of that frequency bucket - most recent!
	pair<Iit, Jit> promote(string key) {
		Iit i;
		Jit j;
		std::tie(i, j) = map_[key];
		Iit iNext = next(i);

		int val = j->second;
		int freq = i->freq + 1;

		// erase current node, and remove bucket if empty
		i->nodes.erase(j);
		if (i->nodes.empty())
			buckets_.erase(i);

		// relocate i: do we need a new frequency bucket? (either at the end, or in the middle)
		i = iNext != buckets_.end() && iNext->freq == freq
			? iNext
			: buckets_.insert(iNext, Bucket(freq));

		// relocate j: push to the bottom at the frequency bucket, because it's the most recent
		j = i->nodes.insert(i->nodes.end(), { key, val });
		return { i, j };
	}
};
