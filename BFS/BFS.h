#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <algorithm>
#include <functional>
#include <utility>
#include <tuple>

using namespace std;

class TreeNode {
public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

class GraphNode {
 public:
  int value;
  vector<GraphNode*> neighbors;
  GraphNode(int v) : value(v) {}
};

struct Cell {
public:
  int i;
  int j;
  int value;
  Cell(int i, int j, int v) : i(i), j(j), value(v) {}
};

class CellComparatorGreater {
public:
  bool operator() (Cell p1, Cell p2) {
    return p1.value > p2.value;
  }
};

class CellComparatorLess {
public:
  bool operator() (Cell p1, Cell p2) {
    return p1.value < p2.value;
  }
};

struct Node {
public:
  int value;
  int listIndex;
  int nodeIndex;
  Node(int v, int li, int ni) :
    value(v), listIndex(li), nodeIndex(ni)
  {}
};

class NodeComparatorGreater {
public:
  bool operator() (Node n1, Node n2) {
    return n1.value > n2.value;
  }
};

class Point3DComparatorGreater {
public:
  bool operator()(vector<int> a, vector<int> b) {
    return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] > b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
  }
};

class BFS
{
public:

  // O(n + klogn)
  // Min heap: keep the k smallest elements
  vector<int> kSmallest_minheap(const vector<int>& nums, int k) {
    vector<int> res;
    if (nums.size() == 0) return res;

    // Min heap
    priority_queue<int, vector<int>, greater<int>> pq;
    for (const auto& a : nums)
      pq.push(a);

    // (if kth smallest instead of k smallest, use n < k - 1 here)
    for (auto n = 0; n < k; ++n) {
      res.push_back(pq.top());
      pq.pop();
    }

    return res;
  }

  // O(k + (n-k)logk)
  // Max heap: throw away the (n-k) largest elements (remember to reverse the output after taking them out of the heap)
  vector<int> kSmallest_maxheap(const vector<int>& nums, int k) {
    vector<int> res;
    if (nums.size() == 0) return res;

    // Max heap
    priority_queue<int> pq;
    for (auto& a : nums) {
      pq.push(a);

      if (pq.size() > k) pq.pop(); // throw away (k - n) largest elements, remaining will be our k smallest elements
    }

    while (!pq.empty()) {
      res.push_back(pq.top());
      pq.pop();
    }

    reverse(res.begin(), res.end());

    return res;
  }

  vector<int> kSmallest_quicksort(vector<int>& array, int k) {
    vector<int> res;
    if (array.size() == 0) return res;

    quickSelect(array, 0, array.size() - 1, k - 1);
    res.assign(array.begin(), array.begin() + k);

    return res;
  }

  void quickSelect(vector<int>& array, int left, int right, int target) {
    if (left >= right) return;
    int mid = partition(array, left, right);

    // Below is slightly different than quick sort
    if (mid == target) return;
    else if (target < mid)
      quickSelect(array, left, mid - 1, target);
    else
      quickSelect(array, mid + 1, right, target);
  }

  // Partion array: pick a pivot, move smaller values to its left, and bigger values to its right
  int partition(vector<int>& array, int left, int right) {
    int pivotIndex = (left + right) / 2;
    int pivotVal = array[pivotIndex];

    // First, swap pivot to the right most
    swap(array[pivotIndex], array[right]);

    // Create and move two bounds
    int lb = left;
    int rb = right;
    while (lb <= rb) { // less equal, to cover all elements
      if (array[lb] < pivotVal) // push left
        lb++;
      else if (array[rb] >= pivotVal) // push right
        rb--;
      else
        swap(array[lb++], array[rb--]);
    }

    swap(array[lb], array[right]); // Move pivot back to the left bound position
    return lb; // Return left bound
  }



  // Time O(n + E)
  // Space O(n) for the unordered_map
  // use a map<Node*, int> to record all visited nodes and their assigned classes, to detect conflict
  bool bipartite(vector<GraphNode*> graph) {
    // Two groups, 0 and 1
    unordered_map<GraphNode*, int> grouped;

    // Need to ierate through all nodes
    for (auto n : graph)
      if (!bipartitie_bfs(n, grouped))
        return false;

    return true;
  }

  bool bipartitie_bfs(GraphNode* node, unordered_map<GraphNode*, int>& grouped) {
    // Already grouped? no need to check
    if (grouped.find(node) != grouped.end()) return true;

    // Only check on new nodes
    queue<GraphNode*> q;
    q.push(node);
    grouped[node] = 0;

    while (!q.empty()) {
      auto curr = q.front(); q.pop();

      // every curr coming out of the queue are guaranteed to have a group previously assigned before being pushed into the queue
      int curGroup = grouped[curr];
      int neiGroup = 1 - curGroup;

      for (auto n : curr->neighbors) {
        // unvisited ?
        if (grouped.find(n) == grouped.end()) {
          grouped[n] = neiGroup;
          q.push(n); // mark this node grouped, won't be processed again in the future
        }
        // visited and there is a conflict?
        else if (grouped[n] != neiGroup)
          return false;
      }
    }
    return true;
  }



  // Time: O(klogk)
  // Space: O(k + n^2), k for heap, n^2 for 2-D map
  // Solution: BFS, using a min heap
  int kthSmallest(vector<vector<int>> matrix, int k) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    if (k > rows* cols) return -1;

    vector<bool> temp(cols, false);
    vector<vector<bool>> visited(rows, temp);

    priority_queue<Cell, vector<Cell>, CellComparatorGreater> minHeap;
    minHeap.push({ Cell(0, 0, matrix[0][0]) });
    visited[0][0] = true;

    // Kth smallest, use k - 1 here!
    for (int n = 0; n < k - 1; ++n) {
      auto curr = minHeap.top();
      minHeap.pop();
      int i = curr.i;
      int j = curr.j;

      // Try right
      j++;
      if (j < cols && !visited[i][j]) { minHeap.push(Cell(i, j, matrix[i][j])); visited[i][j] = true; }

      // Try below
      j--;
      i++;
      if (i < rows && !visited[i][j]) { minHeap.push(Cell(i, j, matrix[i][j])); visited[i][j] = true; }
    }
    return minHeap.top().value;
  }



  // We have to pick one element from a and one from b, find kth smallest sum pair, return the sum
  // Use min heap
  int kthSmallestSumInTwoSortedArrays(vector<int> a, vector<int> b, int k) {
    const int lena = a.size();
    const int lenb = b.size();

    priority_queue<Cell, vector<Cell>, CellComparatorGreater> minHeap;
    minHeap.push(Cell(0, 0, a[0] + b[0]));

    vector<vector<int>> visited(lena, vector<int>(lenb, 0));

    // pop k - 1 times
    for (int n = 0; n < k - 1; ++n) {
      auto curr = minHeap.top();
      minHeap.pop();

      auto i = curr.i;
      auto j = curr.j;

      // check a next
      i++;
      if (i < lena && !visited[i][j]) {
        minHeap.push(Cell(i, j, a[i] + b[j]));
        visited[i][j] = 1;
      }

      // check b next
      i--;
      j++;
      if (j < lenb && !visited[i][j]) {
        minHeap.push(Cell(i, j, a[i] + b[j]));
        visited[i][j] = 1;
      }
    }
    return minHeap.top().value;
  }

  // Use min heap of size k
  // push 3^1 * 5^1 * 7*1 into it
  // keep pushing with adding a mutiplier from either one of 3/5/7
  // IMPORTANT: record visited
  // do it k - 1 times, take top
  int kthSmallest357(int k) {
    long prod = 3 * 5 * 7;

    // min heap
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(prod);

    // visited
    unordered_set<long> visited;

    while (k > 1) {
      prod = pq.top();
      pq.pop();

      if (visited.find(prod * 3) == visited.end()) {
        pq.push(prod * 3);
        visited.insert(prod * 3);
      }

      if (visited.find(prod * 5) == visited.end()) {
        pq.push(prod * 5);
        visited.insert(prod * 5);
      }

      if (visited.find(prod * 7) == visited.end()) {
        pq.push(prod * 7);
        visited.insert(prod * 7);
      }

      k--;
    }
    return pq.top();
  }

  // Same as above
  // Only difference: power starts from 0, not 1!
  int kthSmallest23(int k) {
    long prod = 1; // 2^0 * 3^0

    // min heap
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(prod);

    // visited
    unordered_set<long> visited;
    visited.insert(prod);

    while (k > 1) {
      prod = pq.top();
      pq.pop();

      if (visited.find(prod * 2) == visited.end()) {
        pq.push(prod * 2);
        visited.insert(prod * 2);
      }

      if (visited.find(prod * 3) == visited.end()) {
        pq.push(prod * 3);
        visited.insert(prod * 3);
      }

      k--;
    }
    return pq.top();
  }

  
  // Try to find the closest triplet
  // Solution: take out 3 elements first, update distance
  // We try to bring the triplet closer - so we move forward the smallest element of the three
  // Time O(a+b+c)
  int minimumThreeArrayDistance(vector<int> a, vector<int> b, vector<int> c) {
    int minDist = INT_MAX;
    int i = 0, j = 0, k = 0;
    while (i < a.size() && j < b.size() && k < c.size()) {
      int dist = abs(a[i] - b[j]) + abs(b[j] - c[k]) + abs(a[i] - c[k]);
      minDist = min(minDist, dist);
      if (minDist == 0) break; // early termination

      int minVal = min(a[i], min(b[j], c[k]));
      int maxVal = max(a[i], max(b[j], c[k]));
      if (minVal == a[i]) i++;
      else if (minVal == b[j]) j++;
      else k++;
    }
    return minDist;
  }



  // Common elements of 3 sorted? Move the smallest one
  vector<int> commonElementsInThreeSortedArray(vector<int> a, vector<int> b, vector<int> c) {
    vector<int> res;
    int i = 0, j = 0, k = 0;
    while (i < a.size() && j < b.size() && k < c.size()) {
      if (a[i] == b[j] && b[j] == c[k]) {
        res.push_back(a[i]);
        i++; j++; k++;
      }
      else if (a[i] < b[j]) i++;
      else if (b[j] < c[k]) j++;
      else k++;
    }
    return res;
  }



  // Common elements of k sorted? Just do it two by two
  vector<int> commonElementsInKSortedArray(vector<vector<int>> input) {
    auto res = input[0];
    for (int i = 0; i < input.size(); ++i)
      res = common2_helper(res, input[i]);
    return res;
  }

  vector<int> common2_helper(vector<int> a, vector<int> b) {
    vector<int> res;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
      if (a[i] == b[j]) { res.push_back(a[i]); i++; j++; }
      else if (a[i] > b[j]) j++;
      else i++;
    }
    return res;
  }



  // Pick one element from each array, form a smallest range
  // We need to build a min heap of size N, it always contains N nodes, one from each list
  // every node in the mean heap represents {value, list index, node index}
  // every time we pop the smallest node from the queue, find which list that node comes from, then push the next value from that list back into the heap
  //
  // Time: O(nlogk) - k is number of lists, n is length of list
  // Space:  O(k) - heap size of k
  vector<int> smallestRange(vector<vector<int>> arrays) {
    int minVal = INT_MAX; // lower value of the final range
    int maxVal = INT_MIN; // higher value of the final range
    priority_queue<Node, vector<Node>, NodeComparatorGreater> pq;
    vector<int> res{ 0, INT_MAX };

    // push head element from all arrays,
    for (int n = 0; n < arrays.size(); ++n) {
      auto val = arrays[n].front();
      pq.push(Node(val, n, 0));
      maxVal = max(maxVal, val);
    }

    while (true) {
      minVal = pq.top().value;
      auto i = pq.top().listIndex;
      auto j = pq.top().nodeIndex;

      // update result first
      if (maxVal - minVal < res[1] - res[0]) res = vector<int>{ minVal, maxVal };

      // one of the lists is used up - we terminate
      if (j == arrays[i].size() - 1) return res;

      // otherwise, grab the next node from the min-value list, replace with heap top
      j++;
      int nextVal = arrays[i][j];
      maxVal = max(maxVal, nextVal);
      pq.pop();
      pq.push(Node(nextVal, i, j));
    }
  }



  // Word ladder:
  // transform word a to b, each transform remains in the dictionary
  // Assumptions: a and b are not the same, all words equal length, no dups in dictionary
  // BFS Solution: start from a, traverse all words adjacent to it until we find b
  //               if we traversed all words and still haven't found b, return 0
  int wordLadder(string a, string b, vector<string> list) {
    unordered_set<string> dict(list.begin(), list.end());
    queue<pair<string, int>> q;
    q.push({ a, 1 });

    while (!q.empty()) {
      auto curr = q.front().first;
      auto dist = q.front().second;
      q.pop();

      auto dict2 = dict;
      for (auto it = dict.begin(); it != dict.end(); it++) {
        string w = *it;
        if (curr == w) { // do not jump to yourself
          dict2.erase(w);
        }
        else if (isAdjacent(curr, w)) { // only if one char adjacent, we might have our solution
          if (w == b) return dist + 1;

          dict2.erase(w);
          q.push({ w, dist + 1 });
        }
      }
      dict = dict2; // recover, because a word 2 char away in this loop might be 1 char away in the next loop
    }
    return 0;
  }

  bool isAdjacent(const string& a, const string& b) {
    bool seenDiff = false;
    for (int i = 0; i < a.size(); ++i)
      if (a[i] != b[i] && !seenDiff) seenDiff = true;
      else if (a[i] != b[i]) return false;
    return true;
  }



  long superUglyNumber(int n, vector<int> primes) {
    // min heap
    priority_queue<long, vector<long>, greater<long>> pq;
    long prod = 1;
    pq.push(prod);

    // do we need a visited unordered_set?
    // probably not, because all we get are prime numbers!
    // actually WE DO. because 2 * 7 and 7 * 2 will be dups
    unordered_set<long> visited;

    while (n > 1) {
      prod = pq.top();
      pq.pop();

      // do not break this for loop here, because we need to visit all prime numbers at least once, for this iteration
      for (auto p : primes) {
        long curr = p * prod;
        if (visited.find(curr) == visited.end()) {
          pq.push(p * prod);
          visited.insert(curr);
        }
      }

      n--;
    }
    return pq.top();
  }



  vector<int> kthClosestPointTo000(vector<int> a, vector<int> b, vector<int> c, int k) {
    vector<int> pt{ a[0], b[0], c[0] };
    priority_queue<vector<int>, vector<vector<int>>, Point3DComparatorGreater> pq;
    pq.push(pt);

    // need to dedup the same points
    //unordered_set<vector<int>> visited;
    //visited.insert(pt);

    while (k > 1) {
      auto curr = pq.top();
      pq.pop();

      int i = curr[0];
      int j = curr[1];
      int k = curr[2];

      // try a
      if (i + 1 < a.size()) {
        vector<int> aa{ i + 1, j, k };
        //if (visited.find(aa) == visited.end()) {
        pq.push(aa);
        //visited.insert(aa);
      //}
      }

      // try b
      if (j + 1 < b.size()) {
        vector<int> bb{ i, j + 1, k };
        //if (visited.find(bb) == visited.end()) {
        pq.push(bb);
        //visited.insert(bb);
      //}
      }

      // try c
      if (k + 1 < c.size()) {
        vector<int> cc{ i, j, k + 1 };
        //if (visited.find(cc) == visited.end()) {
        pq.push(cc);
        //visited.insert(cc);
      //}
      }

      k--;
    }

    return pq.top();
  }



  // BFS the graph
  // Store node, store all its neighbors (if not found, create one for it)
  // Time: O(n)
  GraphNode* deepCopyGraph(GraphNode* node) {
    queue<GraphNode*> q;
    q.push(node); // all old nodes

    unordered_map<GraphNode*, GraphNode*> map; // old node, its clone
    GraphNode* newNode = new GraphNode(node->value);
    map[node] = newNode;

    while (!q.empty()) {
      auto curr = q.front();
      q.pop();
      auto vec = curr->neighbors;

      for (int i = 0; i < vec.size(); ++i) {
        auto oldNode = vec[i];
        
        if (map[oldNode] == NULL) { // if not created, create it first
          newNode = new GraphNode(oldNode->value);
          map[oldNode] = newNode;
          q.push(oldNode);
        }

        // append neighbors
        map[curr]->neighbors.push_back(newNode);
      }
    }
    return map[node];
  }

  GraphNode* deepCopyGraph_dfs(GraphNode* node) {
    GraphNode* newNode = new GraphNode(node->value);
    unordered_map<GraphNode*, GraphNode*> map;
    map[node] = newNode;

    for (auto neib : node->neighbors) {
      if (map.find(neib) != map.end())
        map[node]->neighbors.push_back(map[neib]);
      else
        map[node]->neighbors.push_back(deepCopyGraph_dfs(neib));
    }
    return map[node];
  }


  // '0' good, '1' obstacles, 's' src, 'd' dst
  // The nature of BFS: we move ahead one unit in each path at the SAME time
  //    which means the first time we see the destination - that's the shortest path
  int shortestDistanceTwoCells(vector<vector<char>> grid) {
    const int rows = grid.size();
    const int cols = grid[0].size();
    Cell src(0, 0, 0); // i, j, dist
    vector<bool> tmp(cols);
    vector<vector<bool>> visited(rows, tmp);

    // Pre-process: mark all obstacles as "visited"; also locate src, and mark it "visited" as well
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        visited[i][j] = grid[i][j] == '1' ? true : false;
        if (grid[i][j] == 's') {
          src.i = i;
          src.j = j;
          visited[i][j] = true; // also mark src visited
        }
      }

    // start from src
    queue<Cell> q;
    q.push(src);
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      int i = p.i;
      int j = p.j;
      int dist = p.value;

      if (grid[i][j] == 'd') // destination found!
        return dist;

      i--;
      if (i >= 0 && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // up
      i += 2;
      if (i < rows && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // down
      i--; j--;
      if (j >= 0 && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // left
      j += 2;
      if (j < cols && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // right
    }
    return -1; // not found
  }

  

  // 1 - 0 - 2 - 0 - 1
  // |   |   |   |   |
  // 0 - 0 - 0 - 0 - 0
  // |   |   |   |   |
  // 0 - 0 - 1 - 0 - 0
  // 0: empty land, 1: house, 2: obstacle, find an empty land with the shortest combined distance to all the houses
  // BFS solution:
  // We already have the method to find shortest distance from cell A to cell B
  // Here we just iterate all the empty lands, and find the shortest combined distance
  // REMEMBER to break the solution earlier if one of the house is not reachable!
  int shortestDistanceFromAllPoints(vector<vector<int>> grid) {
    const int rows = grid.size();
    const int cols = grid[0].size();

    vector<Cell> houses;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
          if (grid[i][j] == 1)
            houses.push_back(Cell(i, j, 0));

    int globalMin = -1;
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        if (grid[i][j] != 0)
          continue;

        int sum = 0;
        Cell src(i, j, 0);
        for (auto house : houses) {
          int dist = shortestDistanceAToB(grid, src, house);
          if (dist == -1) { sum = -1; break; } // if one house is not reachable, this entire solution is no good
          else sum += dist;
        }

        if (sum != -1) {
          if (globalMin == -1) globalMin = sum;
          else globalMin = min(globalMin, sum);
        }
      }
    return globalMin;
  }

  int shortestDistanceAToB(const vector<vector<int>>& grid, Cell src, Cell dst) {
    const int rows = grid.size();
    const int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) {
        visited[i][j] = grid[i][j] > 0 ? true : false;
      }

    // start from src
    queue<Cell> q;
    q.push(src);
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      int i = p.i;
      int j = p.j;
      int dist = p.value;

      i--;
      if (dst.i == i && dst.j == j) return dist + 1;
      if (i >= 0 && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // up

      i += 2;
      if (dst.i == i && dst.j == j) return dist + 1;
      if (i < rows && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // down

      i--; j--;
      if (dst.i == i && dst.j == j) return dist + 1;
      if (j >= 0 && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // left

      j += 2;
      if (dst.i == i && dst.j == j) return dist + 1;
      if (j < cols && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // right
    }
    return -1; // not found
  }



  // For each cell, record its distance to its closest 0 in a 2D grid
  // Input:   Output :
  // 1 1 1    1 2 1
  // 0 1 0    0 1 0
  // 0 0 0    0 0 0
  vector<vector<int>> closestDistanceToZero(vector<vector<int>> grid) {
    const int rows = grid.size();
    const int cols = grid[0].size();
    vector<vector<int>> res(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j)
        res[i][j] = grid[i][j] == 0 ? 0 : closestDistanceToZero_bfs(grid, Cell(i, j, 0));
    return res;
  }

  int closestDistanceToZero_bfs(const vector<vector<int>>& grid, Cell src) {
    const int rows = grid.size();
    const int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // start from src
    queue<Cell> q;
    q.push(src);
    visited[src.i][src.j] = true;
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      int i = p.i;
      int j = p.j;
      int dist = p.value;

      if (grid[i][j] == 0)
        return dist;

      i--;
      if (i >= 0 && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // up
      i += 2;
      if (i < rows && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // down
      i--; j--;
      if (j >= 0 && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // left
      j += 2;
      if (j < cols && !visited[i][j]) { q.push(Cell(i, j, dist + 1)); visited[i][j] = true; } // right
    }
    return -1; // not found
  }

  // For input string, build the same length output vector to record distance of all chars to the closest c
  // eg. given "geeks" and 'e',  output [1, 0, 0, 1, 2]
  // Solution:
  // Build two arrays, left and right, which represents the shortest distance if we can only see from left / right
  //    for "g e e k s" and 'e' we have
  // left:   M 0 0 1 2
  // right:  1 0 0 M M
  // min:    1 0 0 1 2
  // tip: we can optimize space by re-using left matrix
  vector<int> shortestDistanceToChar(string s, char c) {
    const int size = s.size();

    int prev = -size * 2;
    vector<int> left(size); // what if we can only see left?
    for (int i = 0; i < size; ++i) {
      if (s[i] == c) prev = i;
      left[i] = i - prev;
    }

    prev = size * 2;
    vector<int> right(size); // what if we can only see right?
    for (int i = size - 1; i >= 0; --i) {
      if (s[i] == c) prev = i;
      right[i] = prev - i;
    }

    vector<int> res(size);
    for (int i = 0; i < size; ++i)
      res[i] = min(left[i], right[i]);
    return res;
  }



  // Given a list of words, find closest distance between word a and b (both can appear multiple times)
  int shortestWordDistance(vector<string> words, string a, string b) {
    int i = -1, j = -1;
    int dist = INT_MAX;
    for (int n = 0; n < words.size(); ++n) {
      string curr = words[n];
      if (curr == a) i = n;
      else if (curr == b)j = n;

      if (i >= 0 && j >= 0)
        dist = min(dist, abs(i - j));
    }
    return dist;
  }

  // Follow up from above: what if a and b can be the same word?
  // Solution: add additional check:
  //           if a == b, always update i, j to be the LARGEST pair!
  int shortestWordDistance2(vector<string> words, string a, string b) {
    int i = -1, j = -1;
    int dist = INT_MAX;
    for (int n = 0; n < words.size(); ++n) {
      string curr = words[n];

      if (a == b)
        if (curr == a)
          if (i < j) i = n;
          else j = n;
      else
        if (curr == a) i = n;
        else if (curr == b) j = n;

      if (i >= 0 && j >= 0)
        dist = min(dist, abs(i - j));
    }
    return dist;
  }

  // Yet another follow up to above
  // What if my method will be called millions of times with different parameters? How to optimize it?
  // string distance
  // very similar to above, except input words may have duplicates (but a and b are not the same)
  int stringDistance(vector<string> words, string a, string b) {
    int i = -1, j = -1, dist = INT_MAX;
    for (int n = 0; n < words.size(); ++n) {
      auto curr = words[n];
      if (curr == a) i = n;
      if (curr == b) j = n;
      if (i >= 0 && j >= 0)
        dist = min(dist, abs(i - j));
    }
    return dist == INT_MAX ? -1 : dist;
  }

};



class Helper
{
public:
  static TreeNode* buildTree(const vector<optional<int>>& values, int index = 0)
  {
    if (!values.size() || index == values.size()) return NULL;

    TreeNode* node = new TreeNode(values[index].value());

    int i = index * 2 + 1; // left index
    int j = i + 1; // right index

    if (i < values.size() && values[i].has_value())
      node->left = buildTree(values, i);
    if (j < values.size() && values[j].has_value())
      node->right = buildTree(values, j);
    return node;
  }

  static void printTree(TreeNode* root) {
    vector<vector<optional<int>>> list;
    if (!root) return;

    // LevelOrder traversal
    deque<TreeNode*> queue;
    queue.push_back(root);

    while (!queue.empty()) {

      // if all NULL, we're done with the last level
      auto found = std::find_if(queue.begin(), queue.end(), [&](const TreeNode* n) {return n != NULL; });
      if (found == queue.end())
        break;

      // contain all nodes from current level
      vector<optional<int>> currLevel;

      // size of current level
      auto size = queue.size();

      // traverse current level, prepare for the next level
      for (auto n = 0; n != size; ++n) {
        auto curr = queue.front();
        queue.pop_front();

        if (curr) currLevel.push_back(curr->value);
        else currLevel.push_back(nullopt);

        if (!curr) {
          queue.push_back(NULL);
          queue.push_back(NULL);
        }
        else {
          queue.push_back(curr->left);
          queue.push_back(curr->right);
        }

      }

      list.push_back(currLevel);
    }

    // Print:
    auto width = (int)pow(2, list.size()) + 1;
    for (auto n = 0; n != list.size(); ++n) {
      auto numSpacing = (int)pow(2, list.size() - n - 1);
      string leftSpace(numSpacing, ' ');

      auto numItems = list[n].size();
      auto numMiddleSpacing = n != 0 ? (width - numItems - numSpacing * 2) / (numItems - 1) : 0;
      string middleSpace(numMiddleSpacing, ' ');

      for (auto m = 0; m != list[n].size(); ++m) {
        if (m == 0)
          cout << leftSpace;
        else
          cout << middleSpace;

        auto val = list[n][m];
        if (val.has_value())
          cout << val.value();
        else
          cout << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  static vector<GraphNode*> buildGraph(vector<vector<int>> values) {
    vector<GraphNode*> nodes;
    if (values.empty()) return nodes;

    for (auto n = 0; n != values.size(); ++n) {
      if (values[n].empty()) continue;
      auto node = new GraphNode(values[n][0]);
      nodes.push_back(node);
    }

    for (auto n = 0; n != nodes.size(); ++n) {
      if (values[n].size() == 1) continue; // node has no neighbors

      for (auto k = 1; k != values[n].size(); ++k) {
        nodes[n]->neighbors.push_back(nodes[values[n][k]]);
      }
    }

    return nodes;
  }

private:
 
};
