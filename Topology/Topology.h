#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Topological sort:
//
// Steps:
//      1. pick a node with no incoming edges
//      2. remove all out going edges from this node
//      3. find the next node that has no incoming edges
//      4. remove all out going edges from that node
//      5. etc. etc
//
// Data strcuture:
//      1. list of nodes with no incoming edges
//      2. vector of incoming edges
//
// Implementation:
//      1. compute number of incoming edges of each node
//      2. put all nodes with zero incoming edges into the list
//      At each step:
//        a. pop node X, append it to the result list
//        b. for every node X points to, say Y, minus their incoming edges by 1
//        c. if Y has zero incoming edges, push it into the queue

class Topology {

  // This is essentially a topological sorting problem using DFS
  // If the graph has cycle, return false, otherwise return true
  // We mark each node as 0: unmarked, 1: visiting, 2: visited
  // If we see a node: if visited, return ok
  //                   if visiting, return cycle
  //                   otherwise, mark it visiting, then for loop call DFS on its neighbors, then mark it visited
  // Time: O(n)
  bool courseSchedule(int numCourses, vector<vector<int>> prerequisites) {
    vector<vector<int>> graph(numCourses);
    for (auto p : prerequisites)
      graph[p[1]].push_back(p[0]); // here p[0] and p[1] are interchangeable because dependency loop can be reversed
    vector<int> visit(numCourses, 0);
    for (int i = 0; i < numCourses; ++i)
      if (!courseSchedule_dfs(i, graph, visit))
        return false;
    return true;
  }

  bool courseSchedule_dfs(int curr, const vector<vector<int>>& graph, vector<int>& visit) {
    if (visit[curr] == 1) return false; // visiting
    if (visit[curr] == 2) return true; // visited

    visit[curr] = 1; // mark visiting
    for (auto c : graph[curr])
      if (!courseSchedule_dfs(c, graph, visit))
        return false;
    visit[curr] = 2; // mark visited
    return true;
  }



  // Essentially the same as above, except we now need to return the topological sorted order
  // Remember: the first one marked as Visited should be the last one in the returned list
  // Trick: we can reverse the dependency order to achieve this
  vector<int> courseSchedule2(int numCourses, vector<vector<int>> prerequisites) {
    vector<vector<int>> graph(numCourses);
    for (auto p : prerequisites)
      graph[p[0]].push_back(p[1]); // The little trick
    vector<int> visit(numCourses, 0);
    vector<int> res;
    for (int i = 0; i < numCourses; ++i)
      if (!courseSchedule2_dfs(i, graph, visit, res))
        return vector<int>{};
    return res;
  }

  bool courseSchedule2_dfs(int curr, const vector<vector<int>>& graph, vector<int>& visit, vector<int>& res) {
    if (visit[curr] == 1) return false; // visiting
    if (visit[curr] == 2) return true; // visited

    visit[curr] = 1; // mark visiting
    for (auto c : graph[curr])
      if (!courseSchedule2_dfs(c, graph, visit, res))
        return false;
    visit[curr] = 2; // mark visited
    res.push_back(curr);
    return true;
  }



  // Alien Dictionary
  string alienDictionary(vector<string> words) {
    if (words.size() == 0) return "";
    unordered_map<char, int> inEdges;
    unordered_map<char, unordered_set<char>> g;

    // initialize inEdges map
    for (int i = 0; i < words.size(); i++)
      for (int j = 0; j < words[i].size(); j++) {
        char c = words[i][j];
        inEdges[c] = 0;
      }

    // build graph nodes, and their inEdges
    for (int i = 0; i < words.size() - 1; i++) {
      string curr = words[i];
      string next = words[i + 1];
      int len = min(curr.size(), next.size());
      for (int j = 0; j < len; j++) {
        char c1 = curr[j], c2 = next[j];
        if (c1 != c2) {
          if (g[c1].find(next[j]) == g[c1].end()) {
            g[c1].insert(c2);
            inEdges[c2]++;
          }
          break;
        }
      }
    }

    // push all nodes with 0 inEdges into the queue
    queue<char> q;
    for (auto& e : inEdges)
      if (e.second == 0)
        q.push(e.first);

    // start topological sort
    string ans = "";
    while (!q.empty()) {
      char curr = q.front();
      q.pop();
      ans += curr;

      if (g[curr].size() != 0) {
        for (auto& e : g[curr]) {
          inEdges[e]--;
          if (inEdges[e] == 0) {
            q.push(e);
          }
        }
      }
    }

    // REMEMBER TO CHECK FOR CYCLES!
    return ans.length() == inEdges.size() ? ans : "";
  }
};