#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <cmath>

using namespace std;

class TreeNode {
public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v, TreeNode* l = NULL, TreeNode* r = NULL) : value(v), left(l), right(r) {}
};

class ListNode {
public:
  int value;
  ListNode* next;
  ListNode(int v) : value(v), next(NULL) {}
};

class Lyft {
public:

  // Asteroids Collision problem
  // For example: [5, -10, 5] ==> output will be [-5, 5], because -10 moves left, 5 and 5 move right
  //              [5, 5, -10] ==> output will be [-10], because -10 will destroy both 5s
  // Consider '-' is moving left, '+' is stationary
  // Output will have to be [-, -, -, ..., +, +, +]
  // Solution:
  // For any + value, always put into the stack
  // For any - value, case 1: stack empty / stack top is minus: push
  //                  case 2: stack top is plus: go through the stack and simulate
  // Time complexity: O(n)
  // Space complexity: O(n)
  vector<int> asteroidCollision(vector<int> asteroids) {
    vector<int> s; // user vector to simulate a stack
    for (int i = 0; i < asteroids.size(); ++i) {
      const int a = asteroids[i];

      // All positive asteroids, push to the stack
      if (a > 0) {
        s.push_back(a);
        continue;
      }

      // Negative ones? two cases
      if (s.empty() || s.back() < 0) // ..., -2] -3
        s.push_back(a);
      else if (abs(s.back()) <= abs(a)) {
        if (abs(s.back()) < abs(a)) // ..., 2] -3 ==> my current -3 is still alive
          --i;
        s.pop_back(); // ..., 2] gonna have to pop that 2 anyway
      }
      // else ..., 2] -1 ==> do nothing, as -1 will be absorbed
    }
    return s;
  }



  // Solve without division, and in O(n)
  // Build a vector LEFT, records the product of i (not including i)
  // Build a vector RIGHT, and do the same
  // LEFT * RIGHT is the output
  // Time: O(n), Space: O(n)
  vector<int> productExceptSelf(vector<int>& nums) {
    const int size = nums.size();
    vector<int> left(size, 1);
    for (int i = 1; i < size; ++i)
      left[i] = left[i - 1] * nums[i - 1];

    vector<int> right(size, 1);
    for (int i = size - 2; i >= 0; --i)
      right[i] = right[i + 1] * nums[i + 1];

    vector<int> res(size);
    for (int i = 0; i < size; ++i)
      res[i] = left[i] * right[i];
    return res;
  }



  // Measure water aka the "Die Hard" problem
  // Measure water z, with buckets of x and y capacities
  // Note: you can have x and y collectively hold z amount of water at the end
  // This is a BFS solution
  bool canMeasureWater(int x, int y, int z) {
    if (z < 0 || x + y < z) return false;
    unordered_set<int> visited;
    queue<int> q;
    q.push(0);
    vector<int> options{ x, y, -x, -y };

    while (!q.empty()) {
      const int size = q.size();
      for (int i = 0; i < size; ++i) {
        int curr = q.front(); q.pop();
        if (curr == z) return true; // solution found

        for (auto o : options) {
          int next = curr + o;
          if (next == z) return true; // solution found
          if (next < 0 || next > x + y) continue; // invalid
          if (visited.count(next)) continue; // visited
          q.push(next);
          visited.insert(next);
        }
      }
    }
    return false; // if we reach here, that means a dead cycle is detected (all scenarios are pushed into the "visited" set
  }




  // Given a binary tree, find the largest subtree that is a BST
  // Note: a subtree means it has to include all its descendents
  // Return the number of nodes of that subtree
  // Time: O(n)
  int largestBSTSubtree(TreeNode* root) {
    // content of vector:
    // [0] min, [1] max, [2] number of nodes
    auto res = largest_helper(root);
    return res[2];
  }

  vector<int> largest_helper(TreeNode* root) {
    if (!root) return { INT_MAX, INT_MIN, 0 };

    auto l = largest_helper(root->left);
    auto r = largest_helper(root->right);

    int val = root->value;
    if (val > l[1] && val < r[0])
      return { min(val, l[0]), max(val, r[1]), l[2] + r[2] + 1 };
    else
      return { INT_MIN, INT_MAX, max(l[2], r[2]) };
  }



  // Convert a BST to a Circular, doubly LinkedList
  // Time: O(n)
  TreeNode* treeToDoublyList(TreeNode* root) {
    if (!root) return root;
    vector<TreeNode*> vec;
    inorder(root, vec);

    auto prev = vec[0];
    for (int i = 1; i < vec.size(); ++i) {
      auto curr = vec[i];
      connect(prev, curr);
      prev = curr;
    }
    connect(vec.back(), vec.front());
    return vec.front();
  }

  void inorder(TreeNode* root, vector<TreeNode*>& vec) {
    if (!root) return;
    inorder(root->left, vec);
    vec.push_back(root);
    inorder(root->right, vec);
  }

  void connect(TreeNode* a, TreeNode* b) {
    a->right = b;
    b->left = a;
  }



  // Convert a sorted LinkedList to a height balanced BST, ie. max diff of any left/right subtree is 1
  TreeNode* sortedListToBST(ListNode* head) {
    if (!head) return NULL;
    if (!head->next) return new TreeNode(head->value);

    
    auto slow = head, fast = head, prev = head; // fast/slow pointer to find the midpoint
    while (fast && fast->next) {
      prev = slow;
      slow = slow->next;
      fast = fast->next->next;
    }
    prev->next = NULL; // break two halves 

    TreeNode* root = new TreeNode(slow->value);
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(slow->next);

    return root;
  }



  // Given a positive integer n, find the min number of perfect squares that sum up to n
  // DP solution
  // Time: O(sqrt(n))
  int perfectSquares(int n) {
    if (n == 0) return 0;
    vector<int> dp(n + 1, 0);

    for (int i = 0; i <= n; ++i) {
      dp[i] = i;
      for (int j = 2; j <= sqrt(i); ++j) {
        dp[i] = min(dp[i], 1 + dp[i - j * j]);
      }
    }

    return dp[n];
  }



  // Given a read4 API, use it to read N characters
  // Note: this method will be called many times
  // Thoughts: we might call it to read 6 chars, which means first 4 will come from read4(), next 2 will come from another read4()
  //   so what about the extra 2 chars we read from the second read4?
  char buf4[4];
  int i4 = 0, n4 = 0;
  int read4(char* buf);
  int readNCharactersWithRead4(char* buf, int n) {
    int i = 0;
    while (i < n) {   // pointer for the whole file
      if (i4 >= n4) { // pointer for read4
        i4 = 0;
        n4 = read4(buf4);
        if (n4 == 0) break;
      }
      buf[i++] = buf4[i4++];
    }
    return i;
  }
};
