#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;

// Example:
// Operation: AutocompleteSystem(["i love you", "island", "ironman", "i love leetcode"], [5, 3, 2, 2])
// The system have already tracked down the following sentences and their corresponding times :
// "i love you" : 5 times
// "island" : 3 times
// "ironman" : 2 times
// "i love leetcode" : 2 times
// Now, the user begins another search :
//
// Operation: input('i')
// Output : ["i love you", "island", "i love leetcode"]
//
// Operation: input(' ')
// Output : ["i love you", "i love leetcode"]
// Explanation :
//   There are only two sentences that have prefix "i ".
//
// Operation: input('a')
// Output : []
// Explanation :
//   There are no sentences that have prefix "i a".
//
// Operation : input('#')
// Output : []
// Explanation :
//   The user finished the input, the sentence "i a" should be saved as a new entry in the system.

struct TrieNode {
	unordered_map<char, TrieNode*> children;
	string path; int freq; // Both only have values assigned to them at the node where a sentence ends.
	TrieNode() : path(""), freq(0) {}
};

typedef pair<string, int> Entry;

class AutoComplete {
	TrieNode* root_;
	TrieNode* curr_;
	string path_; // accummulated path as user input chars, and reset to "" when a sentence ends

	// max heap frequency, with a tie breaker on string
	struct comp {
		bool operator() (Entry& a, Entry& b) {
			if (a.second != b.second) return a.second < b.second;
			else return a.first > b.first;
		}
	};
	priority_queue<Entry, vector<Entry>, comp> maxHeap_;

public:
	AutoComplete(vector<string>& sentences, vector<int>& times)
		: root_(NULL), curr_(NULL), path_("") {
		root_ = new TrieNode();
		curr_ = root_;

		// Build the Trie tree
		for (int i = 0; i < sentences.size(); ++i)
			addSentence(sentences[i], times[i]);
	}

	vector<string> input(char c) {
		// end of the sentence? push the current path into the tree, then reset everything
		if (c == '#') {
			addSentence(path_, 1);
			path_.clear();
			curr_ = root_;
			return {};
		}

		// Try progress to the next TrieNode, if failed, return {}
		path_ += c;
		if (curr_ && curr_->children.count(c))
			curr_ = curr_->children[c];
		else {
			curr_ = NULL;
			return {};
		}

		// DFS search all possible nodes below, with the help of PQ to rank the "hot degree"
		maxHeap_ = priority_queue<Entry, vector<Entry>, comp>(); //  IMPORTANT: clear all previous entries
		build_pq_dfs(curr_);

		// gather results
		vector<string> res;
		while (!maxHeap_.empty() && res.size() != 3) {
			res.push_back(maxHeap_.top().first);
			maxHeap_.pop();
		}
		return res;
	}




private:
	// Insert sentence to the tree
	void addSentence(string& s, int times) {
		TrieNode* t = root_;
		for (char c : s) {
			if (t->children.count(c) == 0)
				t->children[c] = new TrieNode();
			t = t->children[c];
		}

		// Only do this once the entire string is traversed
		t->freq += times;
		t->path = s;
	}

	// Build PQ from the tree
	void build_pq_dfs(TrieNode* t) {
		if (!t->path.empty())
			maxHeap_.push({ t->path, t->freq });

		for (auto c : t->children)
			build_pq_dfs(c.second);
	};

};