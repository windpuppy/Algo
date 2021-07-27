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
//        (2,3) (4,3) (1,2)   (key,value) pair      Jit
//                |                                 (newer)
//              (3,7)
// Vertically, we contain a list of LRU nodes with list<pair<int,int>>, ie list of key-value pair. We call such a bucket.
// Horizontally, we store a list of buckets.
// both directions are doubly linked list.
// Then we use a global unordered_map<int, pair<Iit, Jit>> to gain O(1) access of all nodes.
//    where int is key, Iit and Jit are iterators along both directions

typedef pair<int, int> Node; // <key, value>

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
	int get(int key) {
		int val = -1;

		if (map_.count(key)) {
			map_[key] = promote(key); // promote the key to the next frequency bucket
			val = map_[key].second->second;
		}

		return val;
	}

	// O(1) Set the node, also increment its frequency
	void put(int key, int value) {
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
	unordered_map<int, pair<Iit, Jit>> map_;

	// O(1) insert a brand new node (freq = 1)
	// Returns its 2D position
	pair<Iit, Jit> insert(int key, int val) {
		Iit i = buckets_.begin();
		if (i == buckets_.end() || i->freq != 1) // insert if empty, or the first freq node is not 1 (if 1, just connect below)
			i = buckets_.insert(i, Bucket(1));

		Jit j = i->nodes.insert(i->nodes.end(), { key, val });
		return { i, j };
	}

	// O(1) remove a node at the lowest frequency, least recent
	void evict() {
		Iit i = buckets_.begin();
		Jit j = i->nodes.begin();
		map_.erase(j->first);

		i->nodes.erase(j); // remove node
		if (i->nodes.empty()) // remove empty bucket
			buckets_.erase(i);
	}

	// O(1) promote a node to the "frequency + 1" place (might or might not exist in the current frequency list)
	// also put it at the bottom of that frequency bucket - because it's the newest!
	pair<Iit, Jit> promote(int key) {
		Iit i;
		Jit j;
		std::tie(i, j) = map_[key];
		Iit iNext = next(i);

		int val = j->second;
		int freq = i->freq + 1;

		// erase current node, if no more left in this frequency bucket, erase this bucket as well
		i->nodes.erase(j);
		if (i->nodes.empty())
			buckets_.erase(i);

		// relocate i: do we need a new frequency slot? (either at the end, or in the middle)
		i = iNext != buckets_.end() && iNext->freq == freq
			? iNext
			: buckets_.insert(iNext, Bucket(freq));

		// relocate j: push to the bottom at the frequency bucket, because it's the newlest
		j = i->nodes.insert(i->nodes.end(), { key, val });
		return { i, j };
	}
};