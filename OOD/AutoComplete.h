#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;

// Example:
// Operation: AutocompleteSystem(["i love you", "island", "ironman", "i love leetcode"], [5, 3, 2, 2])
// The system have already tracked down the following sentencesand their corresponding times :
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
//   Operation : input('#')
//   Output : []
//   Explanation :
//   The user finished the input, the sentence "i a" should be saved as a historical sentence in system.And the following input will be counted as a new search.

struct TrieNode {
  unordered_map<char, TrieNode*> children;
  string path;
  int count; // hot degree
  TrieNode() : path(""), count(0) {}
};

class AutoComplete {
  TrieNode* m_root;
  TrieNode* m_curr;
  string m_path; //track the accummulative user input path

  // max heap on hot degree, with a tie breaker on string
  struct comp {
    bool operator() (pair<string, int>& a, pair<string, int>& b) {
      if (a.second != b.second) return a.second < b.second;
      else return a.first > b.first;
    }
  };
  priority_queue<pair<string, int>, vector<pair<string, int>>, comp> m_maxHeap;

public:
  AutoComplete(vector<string>& sentences, vector<int>& times)
    : m_root(NULL), m_curr(NULL), m_path("") {
    m_root = new TrieNode();
    m_curr = m_root;
    
    // Build the Trie tree
    for (int i = 0; i < sentences.size(); ++i)
      addSentence(sentences[i], times[i]);
  }

  vector<string> input(char c) {
    // // end of the sentence? push the current path into the tree, then reset everything
    if (c == '#') {
      addSentence(m_path, 1);
      m_path.clear();
      m_curr = m_root;
      return {};
    }

    // Try progress to the next TrieNode, if failed, return {}
    m_path += c;
    if (m_curr && m_curr->children.count(c))
      m_curr = m_curr->children[c];
    else {
      m_curr = NULL;
      return {};
    }

    // DFS search all possible nodes below, with the help of PQ to rank the "hot degree"
    m_maxHeap = priority_queue<pair<string, int>, vector<pair<string, int>>, comp>(); //  IMPORTANT: clear all previous entries
    build_pq_dfs(m_curr);

    // gather results
    vector<string> res;
    while (!m_maxHeap.empty() && res.size() != 3) {
      res.push_back(m_maxHeap.top().first);
      m_maxHeap.pop();
    }
    return res;
  }




private:
  // Insert sentence to the tree
  void addSentence(string& s, int times) {
    TrieNode* t = m_root;
    for (char c : s) {
      if (t->children.count(c) == 0)
        t->children[c] = new TrieNode();
      t = t->children[c];
    }

    // Only do this once the entire string is traversed
    t->count += times;
    t->path = s;
  }

  // Build PQ from the tree
  void build_pq_dfs(TrieNode* t) {
    if (!t->path.empty())
      m_maxHeap.push({ t->path, t->count });

    for (auto c : t->children)
      build_pq_dfs(c.second);
  };
  
};