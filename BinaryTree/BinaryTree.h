#pragma once

#include "../Common/Common.h"

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <deque>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <map>
#include <set>

using namespace std;

class BinaryTree
{
public:
  // Pre-order traversal - recursive
  vector<int> preOrder(TreeNode* root) {
    vector<int> res;
    preOrder_recur(root, res);
    return res;
  }

  void preOrder_recur(TreeNode* root, vector<int>& res) {
    if (!root) return;
    res.push_back(root->value);
    preOrder_recur(root->left, res);
    preOrder_recur(root->right, res);
  }



  // In-order traversal - recursive
  vector<int> inOrder(TreeNode* root) {
    vector<int> res;
    inOrder_recur(root, res);
    return res;
  }

  void inOrder_recur(TreeNode* root, vector<int>& res) {
    if (!root) return;
    inOrder_recur(root->left, res);
    res.push_back(root->value);
    inOrder_recur(root->right, res);
  }



  // Post-order traversal - recursive
  vector<int> postOrder(TreeNode* root) {
    vector<int> res;
    postOrder_recur(root, res);
    return res;
  }

  void postOrder_recur(TreeNode* root, vector<int>& res) {
    if (!root) return;
    postOrder_recur(root->left, res);
    postOrder_recur(root->right, res);
    res.push_back(root->value);
  }



  // Pre-order traversal - iterative
  // remember to use stack
  // remember to push right first, then left
  vector<int> preOrder_iter(TreeNode* root) {
    vector<int> values;
    if (!root) return values;

    stack<TreeNode*> s;
    s.push(root);

    while (!s.empty()) {
      auto curr = s.top(); s.pop();
      values.push_back(curr->value);

      // push right first, then left.
      if (curr->right) s.push(curr->right);
      if (curr->left) s.push(curr->left);
    }
    return values;
  }



  // In-order traversal - iterative
  // remember to use stack
  // remember to keep going left first (that measn we cannot push root in the stack first)
  // in additional to checking stack.empty(), we also check curr != null (for keep going left)
  vector<int> inOrder_iter(TreeNode* root) {
    vector<int> values;
    if (!root) return values;

    stack<TreeNode*> s;
    auto curr = root;

    while (curr || !s.empty()) {
      if (curr) { // keep going down left and keep pushing
        s.push(curr);
        curr = curr->left;
      }
      else {
        // coming back up from left? pop, print, go right
        curr = s.top(); s.pop();
        values.push_back(curr->value);
        curr = curr->right;
      }
    }

    return values;
  }



  // Post-order traversal - iterative
  // Use Stack
  // Use curr and prev pointers, to decide which direction we go next by checking the relationship between prev and curr
  vector<int> postOrder_iter(TreeNode* root) {
    vector<int> values;
    if (!root) return values;

    stack<TreeNode*> s;
    s.push(root);
    TreeNode* curr = NULL;
    TreeNode* prev = NULL;

    while (!s.empty()) {
      curr = s.top(); // peek

      // Case 1: on our way down
      if (!prev || curr == prev->left || curr == prev->right) {

        if (curr->left) s.push(curr->left); // 1.1: go further down, check left first
        else if (curr->right) s.push(curr->right); // 1.2: no left, but what about right?
        else { s.pop(); values.push_back(curr->value); } // 1.3: I am a leaf?
      }

      // Case 2: on our way up , need to visit right - up from left, with right valid
      else if (prev == curr->left && curr->right) {
        s.push(curr->right);
      }

      // Case 3: on our way up, need to go further up - up from right, or up from left with no right
      else {
        s.pop();
        values.push_back(curr->value);
      }

      prev = curr;
    }

    return values;
  }

  // If we do a PreOrder with going right before left, and reverse the output, that's out PostOrder
  // Code is exactly like preOrder_iter(), except we go right first
  vector<int> postOrder_iter_cheat(TreeNode* root) {
    vector<int> values;
    if (!root) return values;

    stack<TreeNode*> stack;
    stack.push(root);

    while (!stack.empty()) {
      TreeNode* curr = stack.top(); stack.pop();
      values.push_back(curr->value);

      if (curr->left) stack.push(curr->left);
      if (curr->right) stack.push(curr->right);
    }

    std::reverse(values.begin(), values.end());
    return values;
  }



  // Level-order traversal
  // Time O(n)
  // Space O(n)
  vector<vector<optional<int>>> levelOrder(TreeNode* root) {
    vector<vector<optional<int>>> res;
    if (!root) return res;
    deque<TreeNode*> q;
    q.push_back(root);

    while (!q.empty()) {
      // if all NULL, we're done with the last level
      auto found = std::find_if(q.begin(), q.end(), [&](const TreeNode* n) {return n != NULL; });
      if (found == q.end())
        break;

      // contain all nodes from current level
      vector<optional<int>> currLevel;

      // size of current level
      auto size = q.size();

      // traverse current level, prepare for the next level
      for (auto n = 0; n != size; ++n) {
        auto curr = q.front(); q.pop_front();

        if (curr) currLevel.push_back(curr->value);
        else currLevel.push_back(nullopt);

        if (!curr) {
          q.push_back(NULL);
          q.push_back(NULL);
        }
        else {
          q.push_back(curr->left);
          q.push_back(curr->right);
        }
      }
      res.push_back(currLevel);
    }
    return res;
  }



  // Level-order traversal, but only return the last level
  vector<int> levelOrder2(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      res.clear();
      const int size = q.size();
      for (int i = 0; i < size; ++i) {
        auto curr = q.front(); q.pop();
        res.push_back(curr->value);
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
      }
    }
    return res;
  }



  //     1
  //    / \
  //   2   5
  //  / \   \
  // 3   4   6
  //
  // 1 - 2 - 3 - 4 - 5 - 6
  //
  // Steps:
  // 1) if root has left and right, connect its entire right subtree to the last node of the left subtree
  // 2) then move the entire left subtree to root's right
  // 3) root keeps going right, repeat 1) and 2), until it reaches the final right leaf
  TreeNode* flattenBinaryTreeToLinkedList(TreeNode* root) {
    auto backup = root;

    while (root) {
      if (root->left && root->right) {
        auto t = root->left;
        while (t->right) // first, grab the "right-est" of left (4)
          t = t->right;
        t->right = root->right; // and connect the root's right to it (5 connects to 4)
      }

      //     1
      //    / \
      //   2   5
      //  / \   \
      // 3   4   6
      //      \
      //       5
      //        \
      //         6

      if (root->left) {
        root->right = root->left;
        root->left = NULL;
      }

      //     1
      //      \
      //       2
      //      / \
      //     3   4
      //          \
      //           5
      //            \
      //             6

      root = root->right;
    }
    return backup;
  }

  // A recursive approach for above
  // Inorder traverse the binary tree.
  // At each stage, pass on the address of last node in the flattened LL for the caller to connect below its right
  TreeNode* flattenBinaryTreeToLinkedList2(TreeNode* root) {
    TreeNode* head = NULL;
    flatten_helper(root, head);
    return root; // here root, head are the same
  }

  void flatten_helper(TreeNode* root, TreeNode*& head) {
    if (!root) return;
    flatten_helper(root->right, head);
    flatten_helper(root->left, head);
    root->left = NULL;
    root->right = head;
    head = root;
  }



  // Zigzag traversal of a binary tree
  // The key is to flip the order at each level
  // so that at even level, we push from front(R, then L), pop from back
  //     and at odd level, we push from back(L, then R), pop from front
  vector<vector<int>> zigzagTraversal(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;
    deque<TreeNode*> dq;
    dq.push_front(root);
    bool reverse = false;

    while (!dq.empty()) {
      const int size = dq.size();
      vector<int> level;

      for (int i = 0; i < size; ++i) {
        if (reverse) {
          auto curr = dq.back(); dq.pop_back();
          level.push_back(curr->value);

          if (curr->right) dq.push_front(curr->right);
          if (curr->left) dq.push_front(curr->left);
        }
        else {
          auto curr = dq.front(); dq.pop_front();
          level.push_back(curr->value);

          if (curr->left) dq.push_back(curr->left);
          if (curr->right) dq.push_back(curr->right);
        }
      }

      res.push_back(level);
      reverse = !reverse;
    }
    return res;
  }



  // Naive solution - two recursive methods
  // First, use recursion to get min max position (relative to the root)
  // Second, use recursion to get vertical lines, from min -> max
  // Time O(n^2) - it is O(w*n) where w is the width of the tree, worst case is complete tree, so O(n^n)
  vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;

    int min = 0, max = 0;
    helper_findMinMax(root, min, max, 0);

    res.resize(max - min + 1);
    for (int line = min; line <= max; line++)
      helper_scanVertical(root, line, min, 0, res);

    return res;
  }

  void helper_findMinMax(TreeNode* root, int& min, int& max, int offset) {
    if (!root) return;
    if (offset < min) min = offset;
    else if (offset > max) max = offset;

    // when offset is between (min, max)
    helper_findMinMax(root->left, min, max, offset - 1);
    helper_findMinMax(root->right, min, max, offset + 1);
  }

  void helper_scanVertical(TreeNode* root, int line, int minLine, int offset, vector<vector<int>>& res) {
    if (!root) return;
    else if (offset == line)
      res[line - minLine].push_back(root->value);

    // if not on current line, go left and right
    helper_scanVertical(root->left, line, minLine, offset - 1, res);
    helper_scanVertical(root->right, line, minLine, offset + 1, res);
  }



  // A more efficient implementation using map
  // Time: O(nlogn)
  // map in STL is implemented as O(logn) insertion
  vector<vector<int>> verticalOrder2(TreeNode* root) {
    map<int, set<pair<int, int>>> values; // map<x, set[y, value]>
    traverse(root, 0, 0, values);
    vector<vector<int>> res;
    for (const auto& v : values) {
      res.push_back({});
      for (auto p : v.second)
        res.back().push_back(p.second);
    }
    return res;
  }

  void traverse(TreeNode* root, int x, int y, map<int, set<pair<int, int>>>& values) {
    if (!root) return;
    values[x].insert({ y, root->value });
    traverse(root->left, x - 1, y + 1, values);
    traverse(root->right, x + 1, y + 1, values);
  }



  // Top view of binary tree
  // Very similar to vertical order, except we take the first element of each vertical scan
  // Time: O(nlogn)
  vector<int> topView(TreeNode* root) {
    map<int, set<pair<int, int>>> values; // map<x, set[y, value]>
    traverse(root, 0, 0, values);
    vector<int> res;
    for (const auto& v : values)
      res.push_back(v.second.begin()->second);
    return res;
  }



  // Right view of binary tree
  // Essentially level order, take last node of each level
  // Time: O(n)
  vector<int> rightView(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> q;
    q.push(root);
    vector<int> res;

    while (!q.empty()) {
      int size = q.size();
      for (int i = 0; i < size; ++i) {
        auto curr = q.front();
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
        if (i == size - 1)
          res.push_back(curr->value);
      }
    }
    return res;
  }



  // Border view of binary tree
  // Border view: left border (top down), leaf nodes, then right border (bottom up, not including root again)
  vector<int> borderView(TreeNode* root) {
    if (!root) return {};
    vector<int> res{ root->value };
    traverseBorder(root->left, true, false, res);
    traverseBorder(root->right, false, true, res);
    return res;
  }

  void traverseBorder(TreeNode* root, bool lb, bool rb, vector<int>& res) {
    if (!root) return;
    if (lb) res.push_back(root->value); // pre-order-ish push left bound

    bool noLeft = !root->left, noRight = !root->right;

    if (!lb && !rb && noLeft && noRight) res.push_back(root->value); // in-order-ish push bottom leaves

    traverseBorder(root->left, lb, rb && noRight, res); // left child must be lb if curr is lb
    traverseBorder(root->right, lb && noLeft, rb, res); // right child could also be lb if curr is lb AND curr has no left child

    if (rb) res.push_back(root->value); // post-order-ish push right bound
  }



  // Get height of binary tree
  // Time O(n), total number of nodes
  // Space O(height), worst case being O(n)
  int height(TreeNode* root) {
    if (!root) return 0;

    int l = height(root->left);
    int r = height(root->right);
    return max(l, r) + 1;
  }

  // Get height of binary tree - iterative
  // level order concept, pop current level nodes, push next level nodes
  // Time O(n)
  int height_iter(TreeNode* root) {
    if (!root) return 0;
    deque<TreeNode*> q;
    q.push_back(root);
    int height = 0;

    while (!q.empty()) {
      height++;
      int count = q.size();
      while (count > 0) {
        TreeNode* curr = q.front(); q.pop_front();
        if (curr->left) q.push_back(curr->left);
        if (curr->right) q.push_back(curr->right);
        count--;
      }
    }
    return height;
  }

  

  // naitve solution: recursively find height
  // Time O(nlogn): height is logn, time spent at each level is O(n)
  // Worst case can be O(n^2), obviously
  bool isBalanced(TreeNode* root) {
    if (!root) return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (abs(leftHeight - rightHeight) > 1) return false;

    return isBalanced(root->left) && isBalanced(root->right);
  }



  // A more efficient approach than above
  // If we find an unbalanced node at any level, bubble up -1 all the way
  // Time O(n), total number of nodes
  // Space O(height), worst case being O(n)
  bool isBalanced2(TreeNode* root) {
    if (!root) return true;

    return height_with_balance_check(root) != -1;
  }

  // If we find an unbalanced node at any level, bubble up -1 all the way
  int height_with_balance_check(TreeNode* root) {
    if (!root) return 0;

    int leftHeight = height_with_balance_check(root->left);
    if (leftHeight == -1) return -1; // Left not balanced? Return -1.

    int rightHeight = height_with_balance_check(root->right);
    if (rightHeight == -1) return -1; // Right not balanced? Return -1.

    return abs(leftHeight - rightHeight) > 1
      ? -1
      : max(leftHeight, rightHeight) + 1;
  }



  // Check if a binary tree is completed
  // NOte: We are allowed to push NULL into the queue
  // First time seeing bubble? Set the flag to true; Then seeing a valid node? Return false;
  // Otherwise keep pushing children into the queue
  bool isCompleted(TreeNode* root) {
    if (!root) return true;
    queue<TreeNode*> q;
    q.push(root);
    bool bubblSeen = false;

    while (!q.empty()) {
      auto curr = q.front(); q.pop();

      if (!curr) bubblSeen = true;
      else if (bubblSeen) return false;
      else {
        q.push(curr->left);
        q.push(curr->right);
      }
    }
    return true;
  }



  // Check if binary tree is symmetric
  bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return isSymmetric(root->left, root->right);
  }

  bool isSymmetric(TreeNode* one, TreeNode* two) {
    if (!one && !two) return true;
    else if (!one || !two) return false;
    else if (one->value != two->value) return false;
    return isSymmetric(one->left, two->right)
        && isSymmetric(one->right, two->left);
  }

  // Iterative approach - use queue
  // First, push root twice to simulate left and right
  // At every level, pop twice, call it one and two
  //    (because left and right doesn't matter here, so we name them one and two to be clear of our intention!)
  // IMPORTANT: any null nodes will not be pushed into the queue!
  bool isSymmetric_iter(TreeNode* root) {
    if (!root || (!root->left && !root->right)) return true;

    // Push root twice to simular the "left vs right" behavior in the while loop
    deque<TreeNode*> q;
    q.push_back(root);
    q.push_back(root);
    TreeNode *one, *two;

    // Queue is guaranteed to not have NULLs
    while (!q.empty()) {
      one = q.front(); q.pop_front();
      two = q.front(); q.pop_front();

      if (one->value != two->value) return false;

      if (one->left && two->right) {
        q.push_back(one->left);
        q.push_back(two->right);
      }
      else if (!one->left || !two->right)
        return false;
      // If both nulls, do nothing

      if (one->right && two->left) {
        q.push_back(one->right);
        q.push_back(two->left);
      }
      else if (!one->right || !two->left)
        return false;
      // If both nulls, do nothing
    }

    return true;
  }


  
  // Check if binary tree is identical
  bool isIdentical(TreeNode* root) {
    if (!root) return true;
    return isIdentical(root->left, root->right);
  }

  bool isIdentical(TreeNode* one, TreeNode* two) {
    if (!one && !two) return true;
    else if (!one || !two) return false;
    else if (one->value != two->value) return false;
    return isIdentical(one->left, two->left)
        && isIdentical(one->right, two->right);
  }



  // Since the input tree is assumed to be balanced, it has log(n) levels
  // but each node has 4 branches, so the recursion tree is a quadtree
  // so the total number of nodes in the recursion tree is 4*logn = 2*(2logn) = 2(logn^2)
  // when tree is not balanced, height >>>>>> n, so it's O(n^2)
  bool isTweaked(TreeNode* one, TreeNode* two) {
    if (!one && !two) return true;
    else if (!one || !two) return false;
    else if (one->value != two->value) return false;

    return isTweaked(one->left, two->right) && isTweaked(one->right, two->left) // mirror
        || isTweaked(one->left, two->left) && isTweaked(one->right, two->right); // same
  }



  // Bad solution 1: in-order traverse, put into array, compare with previous
  // Bad solution 2: in-order traverse, check against previous during traversal
  // Good solution: pass min/max values down, and pass bool value up
  // Time O(n)
  // space O(height)
  bool isBST(TreeNode* root) {
    return isBST(root, INT_MIN, INT_MAX);
  }

  // pre-order recursion
  bool isBST(TreeNode* root, int min, int max) {
    if (!root) return true;
    if (root->value <= min || root->value >= max) return false; // Outside of the range? return false;
    return isBST(root->left, min, root->value)
        && isBST(root->right, root->value, max);
  }



  // Get keys in BST in given range
  // Time O(n) worst case, better answer: O(height + # of nods in [min, max])
  // Space O(height), recursion call stack
  vector<int> getRange(TreeNode* root, int min, int max) {
    vector<int> res;
    getRange(root, min, max, res);
    return res;
  }

  // Very similar to isBST above, but in-order recursion here
  void getRange(TreeNode* root, int min, int max, vector<int>& res) {
    if (!root) return;

    int val = root->value;
    if (val > min)  // no need for >=, because if current root is min, no need to search its left subtree, this is BST!!!
      getRange(root->left, min, max, res);

    if (val >= min && val <= max) // but here we need to use >= and <= !!!
      res.push_back(val);

    if (val < max)
      getRange(root->right, min, max, res);
  }



  // Time: O(h), worst case O(n) for skewed tree
  TreeNode* searchInBST(TreeNode* root, int target) {
    if (!root || root->value == target) return root;
    return target < root->value
      ? searchInBST(root->left, target)
      : searchInBST(root->right, target);
  }



  // Find value in BST closest to target (no duplicates in BST)
  // Naive: in-order traversal, find closest
  // Efficient: if equal? return; if not equal? go left / right
  // Time: O(h)
  int closestInBST(TreeNode* root, int target) {
    int minDiff = INT_MAX;
    int res = root->value;

    while (root) {
      if (root->value == target) return target;

      int diff = abs(target - root->value);
      if (diff < minDiff) {
        minDiff = diff;
        res = root->value;
      }

      // then go left / right
      if (target < root->value)
        root = root->left;
      else
        root = root->right;
    }
    return res;
  }



  // Find k values in BST closest to BST
  // Inorder traversal
  // Optimization 1: use k-size max heap, throw away n-k max, remaining will be out k closest
  // Optimization 2: pruning. Because of BST, one we have k elements bigger than target, we can stop searching
  // Time: O(nlogk), Space: O(k)
  vector<int> closestKInBST(TreeNode* root, int target, int k) {
    struct PairLess {
      bool operator()(pair<int, int> p1, pair<int, int> p2) { return p1.first < p2.first; }
    };
    // pair: distance, value
    priority_queue<pair<int, int>, vector<pair<int, int>>, PairLess> pq; 

    stack<TreeNode*> stack;
    auto curr = root;

    while (curr || !stack.empty()) {
      // keep going left
      if (curr) {
        stack.push(curr);
        curr = curr->left;
      }
      // left drained? fall back to stack to go back up then right
      else {
        curr = stack.top(); stack.pop();
        pq.push({ abs(curr->value - target), curr->value });
        if (pq.size() > k)
          pq.pop();
        curr = curr->right;
      }
    }

    vector<int> res(pq.size());
    for (int i = res.size() - 1; i >= 0; --i) {
      res[i] = pq.top().second;
      pq.pop();
    }
    return res;
  }



  // Find kth smallest in BST
  // pre-order + check k
  // Time: O(height + k)
  int kthSmallestInBST(TreeNode* root, int k) {
    stack<TreeNode*> stack;
    auto curr = root;
    while (curr || !stack.empty()) {
      if (curr) { // keep going down left and keep pushing
        stack.push(curr);
        curr = curr->left;
      }
      else {
        // coming back up from left? pop, print, go right
        curr = stack.top();
        if (--k == 0)
          return curr->value;
        stack.pop();
        curr = curr->right;
      }
    }
    return -1;
  }



  // Return the largest number < target, or INT_MIN if no such exists
  // Time: O(h), Space: O(1)
  int largestSmallerInBST(TreeNode* root, int target) {
    int res = INT_MIN;
    while (root) {
      int val = root->value;
      if (target <= val) {
        root = root->left;
      }
      else {
        res = val;
        root = root->right;
      }
    }
    return res;
  }



  // Target guaranteed to be in the tree, no dups, return inorder successor of the target (or -1 if no such exist)
  // Time: O(h), Space: O(1)
  int smallestLargerInBST(TreeNode* root, int target) {
    int res = -1;
    while (root) {
      int val = root->value;
      if (target < val) {
        res = val;
        root = root->left;
      }
      else
        root = root->right;
    }
    return res;
  }



  // Second largest in BST
  // Naive solution: in-order traverse all nodes, pick the 2nd max
  // Efficient solution:
  // 1) Largest node is the right most node in a BST
  //    a) If right most has no left subtree, 2nd max is its parent
  //    b) If right most has a left subtree, recursively find its rightmost
  int secondLargestInBST(TreeNode* root) {
    if (!root || (!root->left && !root->right)) return INT_MIN;

    // find the right most
    TreeNode* prev = NULL;
    TreeNode* curr = root;
    while (curr->right) {
      prev = curr;
      curr = curr->right;
    }

    if (!curr->left) return prev->value; // a) if no left, right parent

    curr = curr->left; // b) otherwise return left subtree's right most
    while (curr->right)
      curr = curr->right;
    return curr->value;
  }



  // Second smallest in BST
  // with 2 Assumptions: 
  // 1) each node either has 0 or 2 children
  // 2) root equals to its smaller child
  //    1
  //   / \
  //  1   3
  //     / \
  //    5   3
  // Solution:
  // At each split, we look for the bigger child
  // At the end, we return the smaller of the two children
  int secondSmallestInBinaryTree(TreeNode* root) {
    return secondSmallest_helper(root, root->value);
  }

  int secondSmallest_helper(TreeNode* root, int prev) {
    if (!root) return -1;
    if (root->value != prev) return root->value;

    int left = secondSmallest_helper(root->left, prev);
    int right = secondSmallest_helper(root->right, prev);
    if (left == -1) return right;
    if (right == -1) return left;
    return min(left, right);
  }



  // Longest consecutive sequence path in binary tree
  // Consecutive means: 1, 2, 3, etc, cannot have gap
  // Path means: can start from any node to any node, but only top-down wise, not bottom-up
  // Time: O(n), Space: O(h)
  int longestConsecutiveInBinaryTree(TreeNode* root) {
    if (!root) return 0;
    return getLongest(root, root->value, 0);
  }

  int getLongest(TreeNode* root, int parentVal, int len) {
    if (!root) return len;
    len = root->value == parentVal + 1 ? len + 1 : 1; // reset
    int left = getLongest(root->left, root->value, len);
    int right = getLongest(root->right, root->value, len);
    return max(left, right);
  }


  
  // Insert into a BST
  // Time O(h)
  // Note: the order of "add left" and "add right" can swap
  TreeNode* insertInBST(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);
    if (key < root->value)
      root->left = insertInBST(root->left, key); // add to left
    else if (key > root->value)
      root->right = insertInBST(root->right, key); // add to right
    return root;
  }

  TreeNode* insertInBST_iter(TreeNode* root, int key) {
    if (!root) {
      root = new TreeNode(key);
      return root;
    }
    TreeNode* curr = root;
    TreeNode* prev = NULL;

    // Keep searching until we hit NULL (then insert), or find the key (do nothing according to requirement)
    while (curr && curr->value != key) {
      prev = curr;
      if (key < curr->value) curr = curr->left;
      else curr = curr->right;
    }

    // Not found? Let's insert.
    if (!curr) {
      curr = new TreeNode(key);
      if (key < prev->value) prev->left = curr;
      else prev->right = curr;
    }
    // Found? Do nothing.
    // else if (curr->value == key)

    return root;
  }


  
  // Delete in a BST
  // Implementation notes:
  // when returning a node from the recursive call, we are returning either the deleted node, or the root of the subtree we are looking at
  // compare target with root value, go left and right
  // if target is found, 4 cases
  // 1. root is leaf - return NULL to erase it
  // 2. root only has left
  // 3. root only has right
  // 4. root has both - grab the smallest from right to replace root
  //    4.1 right has no left - smallest is the right itself
  //    4.2 right has a left - TOO BAD, WE NEED TO SEARCH!
  TreeNode* deleteTree(TreeNode* root, int target) {
    if (!root) return root;

    if (target < root->value) {
      root->left = deleteTree(root->left, target);
      return root;
    }
    else if (target > root->value) {
      root->right = deleteTree(root->right, target);
      return root;
    }

    ///// If we reach here: target is found, and it's root /////
    auto t = root;

    // Case 1: t is leaf
    // Case 2: t has only left
    // Case 3: t has only right
    if (!t->left && !t->right) return NULL;
    else if (!t->right) return t->left; // provide target's left to target's parent
    else if (!t->left) return t->right; // provide target's right to target's parent

    // Case 4: t has both left and right - grab the smallest on the right and replace it with t
    else {
      // Case 4.1: t.right has no left (to search for)
      if (!t->right->left) {
        t->right->left = t->left;
        return t;
      }
      else {
        // Case 4.2: t.right has left, find smallest below
        auto smallest = deleteSmallest(t->right);
        smallest->left = t->left;
        smallest->right = t->right;
        return smallest;
      }
    }
  }

  // Delete smallest node, but return the node itself
  TreeNode* deleteSmallest(TreeNode* curr) {
    auto prev = curr;

    while (curr->left) { // Go left all the way
      prev = curr;
      curr = curr->left;
    }

    prev->left = curr->right; // connect
    return curr;  // but return the curr
  }



  // LCA - guaranteed a and b both exist
  // Notes:
  // We start from the root and go top down
  //   1) If root is either a or b, then root is LCA
  // Recur left and right.
  //   2) If Left has a and right has b, then root is LCA
  //   3) If either is null, the other is LCA
  // Time: O(n)
  TreeNode* LCA1(TreeNode* root, TreeNode* a, TreeNode* b) {
    if (!root || root == a || root == b) return root; // 1

    auto left = LCA1(root->left, a, b);
    auto right = LCA1(root->right, a, b);

    if (left && right)
      return root; // 2
    else
      return left ? left : right; // 3
    // It can't be both left and right are nulls
  }



  // LCA with parent pointer
  // Brutal force:
  // traverse a to root and save all its parents into hash
  // traverse b to root, first time hit a node in the hash is the LCA
  // Time O(h), Space O(h) because of hash
  //
  // Better solution:
  // 1) Get depth for a and b
  // 2) Climb the lower to make both at the same level
  // 3) Climb both, where they meet, that's their LCA
  // Time O(h), Space O(1)
  TreeNodeP* LCA2(TreeNodeP* a, TreeNodeP* b) {
    int depth1 = getDepth(a);
    int depth2 = getDepth(b);
    int delta = depth1 - depth2;

    if (delta > 0)
      a = climbNode(a, delta);
    else if (delta < 0)
      b = climbNode(b, -delta);

    while (a && b) {
      if (a == b)
        return a;
      else {
        a = a->parent;
        b = b->parent;
      }
    }
    return NULL;
  }

  int getDepth(TreeNodeP* node) {
    int depth = 0;
    while (node) {
      depth++;
      node = node->parent;
    }
    return depth;
  }

  TreeNodeP* climbNode(TreeNodeP* node, int level) {
    while (level-- > 0)
      node = node->parent;
    return node;
  }

  

  // a or b might not be in the tree
  // Soluiton:
  // Use normal LCA as a helper function (that assumes both a and b are in the tree)
  // Case 1: "belongs to" relationship
  //    re-use helper to search b under a
  //    re-use helper to search a under b
  // Case 2: "not belongs to" relationship
  //    return as normal
  TreeNode* LCA3(TreeNode* root, TreeNode* a, TreeNode* b) {
    auto res = LCA1(root, a, b);

    if (res == a)
      return LCA1(a, b, b) ? a : NULL;
    else if (res == b)
      return LCA1(b, a, a) ? b : NULL;
    return res;
  }



  // LCA of k nodes
  // Assumptions: nodes are all in the tree, and not NULL
  // Instead of for loop, we can also convert nodes into a hashset, then call it from the main function
  TreeNode* LCA4(TreeNode* root, vector<TreeNode*> nodes) {
    if (!root) return NULL;

    for (auto n : nodes)
      if (n == root) // one of the nodes is the parent of the rest
        return root;

    auto left = LCA4(root->left, nodes); // physical meaning: left found SOME nodes
    auto right = LCA4(root->right, nodes); // physical meaning: right found SOME nodes

    // it doesn't matter which set of nodes left and right found, if both found any, root has to be the LCA!
    if (left && right)
      return root;
    else
      return left ? left : right;
  }



  // LCA in a BST
  TreeNode* LCA_BST(TreeNode* root, int a, int b) {
    if (!root) return NULL;

    if (a < root->value && b < root->value) // both to the left
      return LCA_BST(root->left, a, b);
    else if (a > root->value&& b > root->value) // both to the right
      return LCA_BST(root->right, a, b);
    else
      return root;
  }



  // LCA in a knary tree
  // Assumption: both nodes are in the tree
  KnaryTreeNode* LCA5(KnaryTreeNode* root, KnaryTreeNode* a, KnaryTreeNode* b) {
    if (!root || root == a || root == b) return root;

    KnaryTreeNode* found = NULL;
    for (auto ch : root->children) {
      auto node = LCA5(ch, a, b);

      if (!node) continue;
      else if (!found) found = node; //seen once? (of a and b is found)
      else return root; // seen twice? (both a and b found)
    }

    return found;
  }



  //  LCA of k nodes in a knary tree
  // Assumption: all nodes are in the tree
  KnaryTreeNode* LCA6(KnaryTreeNode* root, vector<KnaryTreeNode*> nodes) {
    if (!root) return root;

    for (auto n : nodes)
      if (n == root) return root;

    KnaryTreeNode* found = NULL;
    for (auto ch : root->children) {
      auto node = LCA6(ch, nodes);
      
      if (!node) continue;
      else if (!found) found = node;
      else return root;
    }

    return found;
  }



  // For Inorder sequence, 2, 5, 7, [10], 12, 15, 20, all values left to 10 are left subtree, all values right to 10 are right subtree
  // Use this rule to recursively build left and right subtrees
  // User a hashmap, so that given a value, we can quickly lookup its index in the inorder sequence
  TreeNode* reconstructWithPreorderInorder(const vector<int>& pre, const vector<int>& in) {
    const  int size = pre.size();
    unordered_map<int, int> inMap;
    for (auto n = 0; n != in.size(); ++n)
      inMap.insert({ in[n], n });

    return helper_prein(pre, inMap, 0, size - 1, 0, size - 1);
  }

  TreeNode* helper_prein(const vector<int>& pre, unordered_map<int, int>& inMap, int inLeft, int inRight, int preLeft, int preRight) {
    if (inLeft > inRight) return NULL;

    int rootVal = pre[preLeft];
    TreeNode* root = new TreeNode(rootVal);

    // The physical meaning of inOrder reaching root? Left subtree all traversed, right subtree not traversed.
    int inRoot = inMap[rootVal];

    // Boundaries for left subtree
    int inStart = inLeft;
    int inEnd = inRoot - 1;
    int preStart = preLeft + 1;
    int preEnd = preLeft - inLeft + inRoot;

    root->left = helper_prein(pre, inMap, inStart, inEnd, preStart, preEnd);

    // Boundaries for right subtree
    inStart = inEnd + 2; // +2: skip inRoot, then go next
    inEnd = inRight;
    preStart = preEnd + 1;
    preEnd = preRight;

    root->right = helper_prein(pre, inMap, inStart, inEnd, preStart, preEnd);

    return root;
  }



  // Similar to above (reconstruct with postorder and inorder)
  // Except now we have post order, where the root is at the end
  // The way we use the inorder sequence remains the same, hashmap!
  TreeNode* reconstructWithPostorderInorder(const vector<int>& post, const vector<int>& in) {
    const int size = post.size();
    unordered_map<int, int> inMap;
    for (auto n = 0; n != in.size(); ++n)
      inMap.insert({ in[n], n });

    return helper_postin(post, inMap, 0, size - 1, 0, size - 1);
  }

  TreeNode* helper_postin(const vector<int>& post, unordered_map<int, int>& inMap, int inLeft, int inRight, int postLeft, int postRight) {
    if (inLeft > inRight) return NULL;

    int rootVal = post[postRight];
    TreeNode* root = new TreeNode(rootVal);

    // The physical meaning of inOrder reaching root? Left subtree all traversed, right subtree not traversed.
    int inRoot = inMap[rootVal];

    // Boundaries for left subtree
    int inStart = inLeft;
    int inEnd = inRoot - 1;
    int postStart = postLeft;
    int postEnd = postLeft + (inEnd - inStart);

    root->left = helper_postin(post, inMap, inStart, inEnd, postStart, postEnd);

    // Boundaries for right subtree
    inStart = inEnd + 2; // +2: skip inRoot, then go next
    inEnd = inRight;
    postStart = postRight - (inEnd - inStart) - 1;
    postEnd = postRight - 1;

    root->right = helper_postin(post, inMap, inStart, inEnd, postStart, postEnd);

    return root;
  }



  // Within inorder, recursively find the roots from top to down, and split the remaining array such:
  //    everything left to the root: left subtree; right: right subtree
  // For each subtree, extract its elements in the level order sequence, and use them to build from left to right
  TreeNode* reconstructWithLevelIn(const vector<int>& level, const vector<int>& in) {
    return helper_levelin(level, in, 0, in.size() - 1);
  }

  // build subtree given a NEW section of level order sequence (inorder sequence remains full size all the time but paired with two boundarys)
  TreeNode* helper_levelin(const vector<int>& level, const vector<int>& in, int inLeft, int inRight) {
    if (inLeft > inRight) return NULL;

    auto root = new TreeNode(level.front());
    if (inLeft == inRight) return root;

    int inIndex = findNode(in, inLeft, inRight, root->value);
    auto levelLeft = extractNodes(level, in, inLeft, inIndex - 1);
    auto levelRight = extractNodes(level, in, inIndex + 1, inRight);

    root->left = helper_levelin(levelLeft, in, inLeft, inIndex - 1);
    root->right = helper_levelin(levelRight, in, inIndex + 1, inRight);
    return root;
  }

  // extract level order nodes from a given inorder section
  vector<int> extractNodes(const vector<int>& level, const vector<int>& in, int inLeft, int inRight) {
    vector<int> res;
    for (auto val : level)
      if (findNode(in, inLeft, inRight, val) != -1)
        res.push_back(val);
    return res;
  }

  // given a level node, find its inorder index
  int findNode(const vector<int>& in, int inLeft, int inRight, int val) {
    for (int i = inLeft; i <= inRight; ++i)
      if (in[i] == val)
        return i;
    return -1;
  }



  // Reconstruct BST with preOrder sequence
  // Recursion, pass in index (reference), key, and min max for bounding purpose; recursion returns root of the subtree
  // index starts from 0, because it's preOrder
  TreeNode* reconstructBSTWithPreOrder(const vector<int>& pre) {
    if (pre.empty()) return NULL;
    // Physical meaning of preOrder first element? it's the ROOT of the the tree we are building.
    int firstIndex = 0;
    return helper_pre(pre, firstIndex, pre[firstIndex], INT_MIN, INT_MAX);
  }

  TreeNode* helper_pre(const vector<int>& pre, int& index, int key, int min, int max) {
    if (index > pre.size() - 1) return NULL;

    TreeNode* root = NULL;

    if (key > min && key < max) {
      root = new TreeNode(key);
      index++;

      if (index < pre.size())
        root->left = helper_pre(pre, index, pre[index], min, key);
      if (index < pre.size())
        root->right = helper_pre(pre, index, pre[index], key, max);
    }
    return root;
  }



  // Reconstruct BST with postOrder sequence
  // Recursion, pass in index (reference), key, and min max for bounding purpose; recursion returns root of the subtree
  // index starts from size - 1, because it's postOrder
  TreeNode* reconstructBSTWithPostOrder(const vector<int>& post) {
    if (post.empty()) return NULL;
    // Physical meaning of the postOrder last element? Yes, it's the ROOT of THE TREE we are building!
    int lastIndex = post.size() - 1;
    return helper_post(post, lastIndex, post[lastIndex], INT_MIN, INT_MAX);
  }

  TreeNode* helper_post(const vector<int>& postOrder, int& index, int key, int min, int max) {
    // base case
    if (index < 0) return NULL;

    TreeNode* root = NULL;
    if (key > min && key < max) {
      root = new TreeNode(key);
      index--;

      if (index >= 0) {
        // pass in the reference of index, because as we build our tree, index will change
        // but we do pass in a constant key
        root->right = helper_post(postOrder, index, postOrder[index], key, max);
        root->left = helper_post(postOrder, index, postOrder[index], min, key);
      }
    }
    return root;
  }



  // Reconstruct BST with level order
  TreeNode* reconstructBSTWithLevelOrder(const vector<int>& nums) {
    if (nums.empty()) return NULL;
    TreeNode* root = NULL;
    for (auto n : nums)
      root = helper_level(root, n);
    return root;
  }

  TreeNode* helper_level(TreeNode* root, int val) {
    if (!root)
      root = new TreeNode(val);
    else if (val <= root->value)
      root->left = helper_level(root->left, val);
    else
      root->right = helper_level(root->right, val);
    return root;
  }



  // Two elements in a BST are swapped by mistake. Find them and recover.
  // Because inorder traversel of BST is sorted, this is essentially doing an inorder traversal and find two elements that violate the "sorted" property
  TreeNode* na = NULL, * nb = NULL, * nprev = new TreeNode(INT_MIN);
  TreeNode* recoverBST(TreeNode* root) {
    helper_recover(root);
    swap(na->value, nb->value);
    return root;
  }

  void helper_recover(TreeNode* root) {
    if (!root) return;
    helper_recover(root->left);
    if (nprev->value >= root->value) {
      if (!na) na = nprev;
      else nb = root;
    }
    nprev = root;
    helper_recover(root->right);
  }



  // Diameter of binary tree: longest path between any two nodes (path doesn't have to pass root)
  int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    diameter_helper(root, res);
    return res;
  }

  int diameter_helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int l = diameter_helper(root->left, res);
    int r = diameter_helper(root->right, res);
    res = max(l + r, res); // update global max
    return max(l, r) + 1; // return longer path (plus myself)
  }



  // Diameter of binary tree 2: longest path from LEAF to LEAF
  // we can ONLY update global max when both left and right are valid, because 人字形
  int diameterOfBinaryTree2(TreeNode* root) {
    int res = 0;
    diameter2_helper(root, res);
    return res;
  }

  int diameter2_helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int l = diameter2_helper(root->left, res);
    int r = diameter2_helper(root->right, res);
    if (root->left && root->right) {
      res = max(l + r + 1, res);
      return max(l, r) + 1;
    }
    else
      return root->left ? l : r;
  }



  // Binary tree paths (ie. all root->leaf paths)
  //    1
  //   / \
  //  2   3
  //   \
  //    5
  // Output: ["1->2->5", "1->3"]
  vector<string> binaryTreePaths(TreeNode* root) {
    if (!root) return vector<string>{""};

    string out = to_string(root->value);
    vector<string> res;
    binaryTreePath_helper(root, out, res);
    return res;
  }

  void binaryTreePath_helper(TreeNode* root, string out, vector<string>& res) {
    if (!root->left && !root->right) {
      res.push_back(out);
      return;
    }

    // we need to move down
    if (root->left) {
      string newOut = out + "->" + to_string(root->left->value);
      binaryTreePath_helper(root->left, newOut, res);
    }

    if (root->right) {
      string newOut = out + "->" + to_string(root->right->value);
      binaryTreePath_helper(root->right, newOut, res);
    }
  }



  // Max path sum in binary tree - leaf to leaf
  // At each node, we need to cover all 4 cases below:
  //   1        2        3         4
  //  / \      / \      / \       / \
  // 2   3   null 3    3 null  null null
  //
  // Two values to maintain:
  // 1. the return value: max root to leaf sum
  //    we have to pick one of the two paths
  // 2. global max: the max left+right+root so far: we can ONLY update global max when both left and right are valid, because 人字形
  int maxPathSum(TreeNode* root) {
    int res = INT_MIN;
    maxPathSum_helper(root, res);
    return res;
  }

  int maxPathSum_helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int left = maxPathSum_helper(root->left, res);
    int right = maxPathSum_helper(root->right, res);

    // we HAVE TO bring at least one child path
    if (root->left && root->right) {
      res = max(res, left + right + root->value); // we can ONLY update global max when both left and right are both valid, because 人字形
      return max(left, right) + root->value;
    }
    else {
      return root->left ? left + root->value : right + root->value;
    }
  }



  // Max path sum - ANY NODE to ANY NODE
  //
  // Two values to maintain:
  // 1. the return value: 3 CHOICES: bring left, bring right, don't bring any
  // 2. global max: 4 CHOICES: left+right+root, left+root, right+root, or root
  int maxPathSum2(TreeNode* root) {
    int res = INT_MIN;
    maxPathSum2_helper(root, res);
    return res;
  }

  int maxPathSum2_helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int left = maxPathSum2_helper(root->left, res);
    int right = maxPathSum2_helper(root->right, res);

    // we can bring at most one child path, and we can bring NO path, but we cannot bring both
    res = max(res, max(left, 0) + max(right, 0) + root->value);
    int returnVal = max(max(left, right) + root->value, root->value);
    return returnVal;
  }



  // Max path sum - root to leaf, any section
  // Brutal force: get all vertical paths from leaf, compute largest subarray sums, pick max
  //
  // Efficient solution: similar to 1 and 2
  // Here we PRUNE LEFT AND RIGHT TO POSITIVE NUMBERS, ie. if negative, I won't bring you
  int maxPathSum3(TreeNode* root) {
    int res = INT_MIN;
    maxPathSum3_helper(root, res);
    return res;
  }

  int maxPathSum3_helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int left = maxPathSum3_helper(root->left, res);
    int right = maxPathSum3_helper(root->right, res);
    left = max(left, 0); // pruning
    right = max(right, 0); // pruning

    int returnVal = max(left, right) + root->value;
    res = max(res, returnVal);
    return returnVal;
  }



  // Max path sum - root to leaf, end to end
  int maxPathSum4(TreeNode* root) {
    if (!root) return 0;

    int res = root->value;
    int left = maxPathSum4(root->left);
    int right = maxPathSum4(root->right);

    if (root->left && root->right) res += max(left, right);
    else if (!root->left) res += right;
    else if (!root->right) res += left;
    return res;
  }



  // Path sum to target - root to leaf, end to end
  bool pathSumToTarget(TreeNode* root, int target) {
    if (!root) return false;
    return pathSum_helper(root, target, 0);
  }

  bool pathSum_helper(TreeNode* root, int target, int sum) {
    if (!root)
      return target == sum;

    if (pathSum_helper(root->left, target, sum + root->value))
      return true;
    else if (pathSum_helper(root->right, target, sum + root->value))
      return true;
    return false;
  }



  // Path sum to target - root to leaf, any section
  // Related problem: subArraySumToTarget
  bool pathSumToTarget2(TreeNode* root, int target) {
    if (!root) return false;
    unordered_set<int> prefixSum;
    prefixSum.insert(0); // important!
    return pathSum2_helper(root, 0, target, prefixSum);
  }

  bool pathSum2_helper(TreeNode* root, int currSum, int target, unordered_set<int> prefixSum) {
    currSum += root->value;
    if (prefixSum.count(currSum - target)) return true;

    prefixSum.insert(currSum);

    if (root->left && pathSum2_helper(root->left, currSum, target, prefixSum))
      return true;
    if (root->right && pathSum2_helper(root->right, currSum, target, prefixSum))
      return true;
    return false;
  }



  // Count nodes in complete binary tree
  int countNodesInCompleteTree(TreeNode* root) {
    if (!root) return 0;

    int lh = 0, rh = 0;
    TreeNode* left = root, *right = root;

    while (left) {
      lh++;
      left = left->left;
    }

    while (right) {
      rh++;
      right = right->right;
    }

    if (lh == rh) return pow(2, lh) - 1;

    return 1 + countNodesInCompleteTree(root->left) + countNodesInCompleteTree(root->right);
  }
};
