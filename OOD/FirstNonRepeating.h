#pragma once
#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

// Design a class to implement two API calls:
// 1) read(char ch), to read a char
// 2) firstNonRepeating(), to return the first non-repeating char in this stream
// Both needs to have O(1) time
// e.g. read:              a b c a c c b
//      firstNonRepeating: a a a b b b null

// Use doubly linked list to store all non-repeating characters
// doubly LL :  from oldest (left) to newest (right)
// found a repeating char? delete it in LL
// found a non-repeating char? insert it
//
// Data structures used:
// doubly LL: to contain all UNIQUE chars
// hashmap<unique char, node>: for O(1) access to all unique chars
// case 1: if a historically repeated char comes in, do nothing
// case 2: if a unique char comes in, append it to the nodes
// case 3: if a re-appearing char comes in, remove it from the node and node dictionary, add to the historical repeated char set

class FirstNonRepeating {
public:
	FirstNonRepeating() {
		unique_.push_back(' ');
	}

	void read(char ch) {
		// already in repeated group, do nothing
		if (repeated_.count(ch))
			return;

		// not in repeated group? two cases

		// 1) brand new char
		if (!uniqueMap_.count(ch)) {
			unique_.push_back(ch);
			uniqueMap_[ch] = --unique_.end();
		}
		// 2) flipping an unique char into repeated
		else {
			unique_.erase(uniqueMap_[ch]);
			uniqueMap_.erase(ch);
			repeated_.insert(ch);
		}
	}

	char firstNonRepeating() {
		if (unique_.size() == 1)
			return ' ';
		auto it = unique_.begin();
		advance(it, 1);
		return *it;
	}

private:
	list<char> unique_;
	unordered_map<char, list<char>::iterator> uniqueMap_;
	unordered_set<char> repeated_;
};


