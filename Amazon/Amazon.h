#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class TreeNode {
public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

class Amazon {
public:
  // An array of logs, string is either "letter log" or "digi log"
  // letter log: "let1 art can", "let2 own kit dig"
  // digi log: "dig1 8 1 5 1", "dig2 3 6"
  // Reorder those logs so that letter logs are in front of digi logs
  //     also 1. letter logs are lexicographically ordered based on their content (use identifier for tie breaker)
  //          2. digi logs in their original order
  // Implementation:
  // For letter logs: move identifier to the end for sorting purpose, then move it back
  // Time: O(nlogn)
  // Space: O(n)
  vector<string> reorderLogFiles(vector<string>& logs) {
    vector<string> letterLogs, digiLogs;
    for (auto& s : logs) {
      int i = s.find_first_of(" ");
      if (isdigit(s[i + 1]))
        digiLogs.push_back(s);
      else
        letterLogs.push_back(s.substr(i + 1) + " " + s.substr(0, i));
    }

    sort(letterLogs.begin(), letterLogs.end());

    for (auto& s : letterLogs) {
      int i = s.find_last_of(" ");
      s = s.substr(i + 1) + " " + s.substr(0, i);
    }

    for (auto& s : digiLogs) letterLogs.push_back(s);
    return letterLogs;
  }



  // Check if S is a subtree of T
  // Note: we are checking subtree, not if "S is part of T". These two are fundamentally different
  bool isSubtree(TreeNode* t, TreeNode* s) {
    if (!t) return false;
    if (isIdentical(t, s)) return true;

    return isSubtree(t->left, s) || isSubtree(t->right, s);
  }

  bool isIdentical(TreeNode* a, TreeNode* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    if (a->value != b->value) return false;

    return isIdentical(a->left, b->left) && isIdentical(a->right, b->right);
  }

  
  
  // Most common word
  // Given a paragraph and a list of banned word, find the most common word (guaranteed to exist, and in lower case)
  // We can first push all banned word into a set for quicker lookup, but a little trick enables us to share one single map
  string mostCommonWord(string p, vector<string>& banned) {
    unordered_map<string, int> map;
    for (int i = 0; i < p.size();) {
      string word = "";
      while (i < p.size() && isalpha(p[i])) word.push_back(tolower(p[i++]));
      while (i < p.size() && !isalpha(p[i])) i++;
      map[word]++;
    }

    for (auto b : banned) map[b] = 0;

    string res = "";
    int count = 0;
    for (auto x : map)
      if (x.second > count) {
        res = x.first;
        count = x.second;
      }
    return res;
  }

  

  // Group anagrams
  // Given a list of strings, group anagrams together
  // Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
  // Output:
  // [["ate", "eat", "tea"],
  //  ["nat", "tan"],
  //  ["bat"]]
  // Time: O(m * n)
  // Space: O(m * n)
  vector<vector<string>> groupAnagrams(vector<string>& words) {
    unordered_map<string, vector<string>> map;

    auto countSort = [&](string& w) {
      vector<int> counter(26, 0);
      for (char c : w) counter[c - 'a']++;
      w.clear();
      for (int i = 0; i < 26; ++i)
        if (counter[i] != 0)
          w += string(counter[i], 'a' + i);
    };

    for (string& w : words) {
      string tmp = w;
      //sort(w.begin(), w.end()); // Improvement: use counting sort if input words are all lowercases
      countSort(w);
      map[w].push_back(tmp);
    }
    vector<vector<string>> res;
    for (auto& m : map)
      res.push_back(m.second);
    return res;
  }


  // Search in a 2D matrix that is row & column wise sorted (target might or might not exist)
  // e.g.
  // [1,   3,  5,  7],
  // [10, 11, 16, 20],
  // [23, 30, 34, 50]
  // Time: O(logmn), Space: O(1)
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    int left = 0, right = rows * cols - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      int i = mid / cols;
      int j = mid % cols;
      int val = matrix[i][j];

      if (target == val) return true;
      else if (target < val) right = mid - 1;
      else left = mid + 1;
    }

    return false;
  }



  // Search in a 2D matrix that is row & column wise sorted (target might or might not exist)
  // [1,   4,  7, 11],
  // [2,   5,  8, 12],
  // [3,   6,  9, 16],
  // [10, 13, 14, 17],
  // [18, 21, 23, 26]
  // Solution: we can either start at the bottom-left or top-right corner
  // Time: O(m + n)
  bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    const int rows = matrix.size();
    const int cols = matrix[0].size();
    int i = rows - 1, j = 0;
    while (i >= 0 && j < cols)
      if (matrix[i][j] == target)
        return true;
      else if (matrix[i][j] > target) // go up
        i--;
      else // go right
        j++;
    return false;
  }



  // Rotting oranges
  // 0: empty cell, 1: fresh orange, 2: rotten orange
  // Every minute, any fresh orange adjacent to rotten orange becomes rotten, return the minimum minutes that no fresh oranges are left
  // This is essentially a BFS problem, we first push all rotten oranges into the queue, and "rot" their neighbors
  // Time: O(mn), Space: O(mn)
  int rottingOranges(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    const int rows = grid.size();
    const int cols = grid[0].size();
    int minutes = 0;
    int freshOranges = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        if (grid[i][j] == 2)
          q.push({ i, j });
        else if (grid[i][j] == 1)
          freshOranges++;

    while (!q.empty()) {
      const int size = q.size();
      int before = freshOranges;
      for (int k = 0; k < size; ++k) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        orangeHelper(grid, i - 1, j, q, freshOranges);
        orangeHelper(grid, i + 1, j, q, freshOranges);
        orangeHelper(grid, i, j - 1, q, freshOranges);
        orangeHelper(grid, i, j + 1, q, freshOranges);
      }
      if (freshOranges < before)
        minutes++;
    }
    return freshOranges == 0 ? minutes : -1; // only return minutes if all fresh oranges are rotten
  }

  void orangeHelper(vector<vector<int>>& grid, int i, int j, queue<pair<int, int>>& q, int& freshOranges) {
    const int rows = grid.size(), cols = grid[0].size();
    if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] != 1) return;
    grid[i][j] = 2;
    freshOranges--;
    q.push({ i, j });
  }



  // Prison cells after N days
  // Cell state change rule: if i-1 and i+1 both occupied or vacant, i becomes occupied next day; otherwise i becomes vacent next day
  // (which implies first and last cells become vacant from day 2, and remain vacant because they don't have 2 neighbors)
  // Idea: check if there is a cycle
  vector<int> prisonAfterNDays(vector<int>& c, int N) {
    if (c.empty() || N <= 0) return c;
    unordered_set<string> set;
    int count = 0;
    bool hasCycle = false;
    for (int i = 0; i < N; ++i) {
      auto next = nextDay(c);

      string s = "";
      for (auto n : next) s += to_string(n);
      if (!set.count(s)) {
        set.insert(s);
        count++;
      }
      else {
        hasCycle = true;
        break;
      }
      c = next;
    }

    if (hasCycle) {
      N = N % count;
      for (int i = 0; i < N; ++i)
        c = nextDay(c);
    }
    return c;
  }

  vector<int> nextDay(vector<int>& cells) {
    vector<int> ret(cells.size(), 0);
    for (int i = 1; i < cells.size() - 1; ++i)
      ret[i] = cells[i - 1] == cells[i + 1] ? 1 : 0;
    return ret;
  }



  // Given a list of words, find out all the concatenated words (ie. words can be entirely represented by some others in the dictionary)
  vector<string> concatenatedWords(vector<string>& words) {
    vector<string> res;
    if (words.empty()) res;
    auto wordComp = [&](const string& a, const string& b) { return a.size() < b.size(); };
    sort(words.begin(), words.end(), wordComp);
    unordered_set<string> dict;
    
    for (auto& word : words) {
      if (wordBreak(word, dict))
        res.push_back(word); // no need to insert this word. why? if we have bob+cat=bobcat, "bob" and "cat" will enable "bobcatdog" later on
      else
        dict.insert(word);
    }
    return res;
  }

  // A DP helper, 左大段右小段
  // Use book M, M[i] represents can "the substring from the begining to the i-th character" be composed by words from the dict
  // Left: check M; Right: manual work
  bool wordBreak(string& word, unordered_set<string>& dict) {
    if (word.empty()) return false;
    vector<bool> M(word.size() + 1, false); // plus 1, because we reserve M[0] for empty string, for convenience
    M[0] = true;

    for (int i = 1; i <= word.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        string right = word.substr(j, i - j);
        bool rightMatch = dict.count(right) != 0;

        if (M[j] && rightMatch) { // eg. bob | c, left BIG (use M), right SMALL (manual check)
          M[i] = true;
          break;
        }
      }
    }
    return M.back();
  }



  // Min value on a max path
  // Travel from top left to bottom right, find the max sum path, return the min value along that path
  // Assumption: all grid values >= 0
  // BFS + PQ
  int minValueOnMaxPath(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return -1;
    const int rows = grid.size();
    const int cols = grid[0].size();
    int res = grid[0][0];
    priority_queue<pair<int, pair<int, int>>> pq; // <grid[i][j], <i, j>>, max heap
    pq.push({ grid[0][0], {0, 0} });
    grid[0][0] = -1;

    auto helper = [&](vector<vector<int>>& g, int i, int j, priority_queue<pair<int, pair<int, int>>>& q) {
      if (i >= 0 && i < rows && j >= 0 && j < cols && g[i][j] != -1) {
        q.push({ g[i][j], {i, j} });
        g[i][j] = -1;
      }
    };

    while (!pq.empty()) {
      auto curr = pq.top(); pq.pop();
      int i = curr.second.first, j = curr.second.second;
      res = min(res, curr.first);

      if (i == rows - 1 && j == cols - 1) return res;

      helper(grid, i - 1, j, pq);
      helper(grid, i + 1, j, pq);
      helper(grid, i, j - 1, pq);
      helper(grid, i, j + 1, pq);
    }
    return -1; // will not reach here anyway
  }



  // Given a set of sticks of different lengths, cost of connecting two sticks = x + y. What's the minimum cost to connect all?
  // Observation: Earlier participanats will have a bigger influcence on the final cost!
  //     so we need to join two shorted sticks from the remaining pool at any time.
  // Solution: BFS + min heap, not just a simple sorting!
  //     e.g. [3,4,5,6], 3+4 = 7, next step should be 5+6, not 7+5
  //     intuition: 3+4=7, but 7 need to be pushed back into the PQ
  int minimumCostConnectSticks(vector<int>& nums) {
    if (nums.empty()) return 0;
    priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());
    int cost = 0;
    while (pq.size() >= 2) {
      int a = pq.top(); pq.pop();
      int b = pq.top(); pq.pop();
      cost += a + b;
      pq.push(a + b);
    }
    return cost;
  }



  // Just like the above sticks problem, now we merge k CONSECUTIVE piles of stone at one time.
  // First we need to think about this, not any number of piles can be merged into 1 by merging k piles at a time.
  //    After each merge, we will have k-1 less piles, so only if (n-1)%(k-1)==0, we can merge all into one pile.
  // M[i][j] represents the minimal cost to merge i ~ j piles (not necessarily into 1), until we cannot merge further
  //    Note, after merging i ~ j, we will have (j-i) % (k-1) + 1 piles
  //
  // Time: O(n^3/k), Space: O(n^2)
  int minimumCostMergeStones(vector<int>& nums, int k) {
    const int n = nums.size();
    if (k * n == 0 || (n - 1) % (k - 1) != 0) return -1;

    // build prefix sum
    vector<int> preSum(n + 1, 0);
    for (int i = 1; i <= n; ++i)
      preSum[i] = preSum[i-1] + nums[i-1];

    // M initialization: all M[i][i] = 0, all, M[i][i+k-1] = their sum, rest INT_MAX
    vector<vector<int>> M(n, vector<int>(n, 0));
    for (int j = 0; j < n; ++j)
      for (int i = j - k + 1; i >= 0; --i) {
        int cost = INT_MAX;

        // 左大段右小段！！
        // 左大段：查表，不一定最终能merge成一堆
        // 右小段：查表，肯定能最终merge成一堆
        for (int m = j; m > i; m -= k - 1) {
          // Here, we let the right part [mid, j] merge into 1 pile (guaranteed we can!)
          //       we let the left part [i, mid-1]) merge as further as possible (not guaranteed into 1 pile)
          // In most situations, we will be left with a few piles on the left, and 1 pile on the left
          cost = min(cost, M[i][m-1] + M[m][j]);
          M[i][j] = cost;
        }

        // For [i,j] in some cases if left and right can further merge into 1 pile, we need to do an additional merge
        if ((j - i) % (k - 1) == 0)
          M[i][j] += preSum[j+1] - preSum[i];
      }
    return M[0][n-1];
  }



  // Smallest prime palindrome >= n
  int primePalindrome(int n) {
    int e = 1, o = 1;
    int curr = 0;
    string s = "";
    while (true) {
      s = generatePalindrome(to_string(e), true);
      int even = stoi(s);
      s = generatePalindrome(to_string(o), false);
      int odd = stoi(s);
      curr = min(even, odd);

      if (curr >= n && isPrime(curr)) break;

      if (even < odd) e++;
      else o++;
    }
    return curr;
  }

  bool isPrime(int n) {
    if (n == 1) return false;
    for (int i = 2; i*i <= n; ++i)
      if (n % i == 0) return false;
    return true;
  }

  string generatePalindrome(string half, bool even) {
    if (even) return half + string(half.rbegin(), half.rend());
    else return half + string(half.rbegin() + 1, half.rend());
  }



  // Definition of a critical connection: if we remove that connection, 1 or more server nodes will become unreachable.
  // Intuition: any connection on a cycle is not a critical connection, because even if we remove it, all nodes are still reachable.
  //            so, if we find all cycles, remove their connections, the remaining connections are critical connections
  // So how to find cycles?
  // Implementation: we record a timestamp for each node we visit. For each node, we then check its neighbors (except for the node's parent) then return the smallest timestamp found
  //            if the returned timestamp is equal or smaller than the current node's, then the current node is in a cycle
  //            otherwise the current node is not in a cycle, so current node to that neighbor is a CRITICAL CONNECTION
  // Note: we do not use the visited vector here, instead we use timestamp[n], because our timer starts at 1, so if a timestamp == 0, it's not visited
  vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);
    for (auto c : connections) { // undirectional graph!
      graph[c[0]].push_back(c[1]);
      graph[c[1]].push_back(c[0]);
    }

    int timer = 0;
    vector<int> time(n, 0);
    vector<vector<int>> res;
    critical_dfs(graph, -1, 0, timer, time, res);
    return res;
  }

  void critical_dfs(vector<vector<int>>& graph, int prev, int curr, int& timer, vector<int>& time, vector<vector<int>>& res) {
    time[curr] = ++timer;
    int currTime = time[curr]; // IMPORTANT! because time[curr] can get modified during dfs recursion

    for (auto n : graph[curr]) {
      if (n == prev) continue; // skip the node where we "come from"

      if (time[n] == 0) // n is unvisited
        critical_dfs(graph, curr, n, timer, time, res);
      time[curr] = min(time[curr], time[n]);
      if (currTime < time[n])
        res.push_back({ curr, n });
    }
  }
};