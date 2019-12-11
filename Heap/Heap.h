#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <deque>
#include <queue>

using namespace std;

class TreeNode {
public:
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

class Heap {
public:
  vector<int> heapify(vector<int> array) {
    int size = array.size();

    // start with  size / 2 -1 (ie non leaf row, first node), do percolateDown leftwards through the array
    for (int n = size / 2 - 1; n >= 0; --n)
      percolateDown(array, size, n);

    return array;
  }

  vector<int> offerHeap(vector<int> array, int element) {
    int size = array.size();
    array.at(size - 1) = element;

    percolateUp(array, size - 1);

    return array;
  }

  vector<int> updateHeap(vector<int> array, int index, int element) {
    int size = array.size();
    if (index < 0 || index > size - 1) return array;

    // It's already a heap, remember this! (ie. no need to heapify)

    if (element == array[index]) return array;

    int previousValue = array[index];
    array[index] = element;

    if (element > previousValue)
      percolateDown(array, size, index);
    else
      percolateUp(array, index);

    return array;
  }

  // Heap sort with MAX HEAP!!!
  vector<int> heapsort(vector<int> array) {
    int size = array.size();

    // Build max heap, using the n/2-1 technique
    for (int n = size / 2 - 1; n >= 0; --n) {
      percolateDown_maxHeap(array, size, n);
    }

    // one by one
    // 1) extra max (root) to the bottom of array
    // 2) heapify the REDUCED heap
    for (int n = size - 1; n >= 0; --n) {
      swap(array[0], array[n]);
      percolateDown_maxHeap(array, n, 0); // percolate down root
    }

    return array;
  }

  bool isMinHeap(vector<int> array) {
    int size = array.size();
    if (array.empty() || size == 1) return true;

    // similar to level order traversal, use queue!
    queue<int> q;
    q.push(0);

    int curr = 0;
    while (!q.empty()) {
      curr = q.front();
      q.pop();

      int left = curr * 2 + 1;
      int right = left + 1;

      if (left < size) {
        if (array[left] < array[curr]) return false;
        else q.push(left);
      }

      if (right < size) {
        if (array[right] < array[curr]) return false;
        else q.push(right);
      }
    }

    return true;
  }

  // similar as abve, queue of nodes instead of indexes
  bool isMinHeap(TreeNode* root) {
    if (!root) return true;
    if (!root->left && !root->right) return true;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      TreeNode* curr = q.front();
      q.pop();

      // Here we need another "bubble" check: if we see null, the rest cannot be null
      // Implemented in Java solution on LaiCode

      if (curr->left) {
        if (curr->left->value < curr->value) return false;
        else q.push(curr->left);
      }

      if (curr->right) {
        if (curr->right->value < curr->value) return false;
        else q.push(curr->right);
      }
    }

    return true;
  }

private:

  // percolate down - iterative
  void percolateDown(vector<int>& array, int size, int n) {
    // check legal
    if (n > size / 2 - 1) return;

    while (true) {
      int swapCandidate = n; // initialize min as root
      int left = 2 * n + 1; // left child
      int right = 2 * n + 2; // right child

      // If left child is smaller than root 
      if (left < size && array[left] < array[swapCandidate])
        swapCandidate = left;

      // If right child is smaller than smallest
      if (right < size && array[right] < array[swapCandidate])
        swapCandidate = right;

      // If smallest is not root 
      if (swapCandidate != n)
        swap(array[n], array[swapCandidate]);
      else
        break;

      n = swapCandidate;
    }
  }

  void percolateDown_maxHeap(vector<int>& array, int size, int n) {
    // check legal
    if (n > size / 2 - 1) return;

    while (true) {
      int swapCandidate = n; // initialize min as root
      int left = 2 * n + 1; // left child
      int right = 2 * n + 2; // right child

      // If left child is smaller than root 
      if (left < size && array[left] > array[swapCandidate])
        swapCandidate = left;

      // If right child is smaller than smallest
      if (right < size && array[right] > array[swapCandidate])
        swapCandidate = right;

      // If smallest is not root 
      if (swapCandidate != n)
        swap(array[n], array[swapCandidate]);
      else
        break;

      n = swapCandidate;
    }
  }

  // percolate down - recursive
  void percolateDown_recur(vector<int>& array, int size, int n) {
    int swapCandidate = n; // initialize min as root
    int left = 2 * n + 1; // left child
    int right = 2 * n + 2; // right child

    // If left child is smaller than root 
    if (left < size && array[left] < array[swapCandidate])
      swapCandidate = left;

    // If right child is smaller than smallest
    if (right < size && array[right] < array[swapCandidate])
      swapCandidate = right;

    // If smallest is not root 
    if (swapCandidate != n)
    {
      swap(array[n], array[swapCandidate]);

      // Recursively heapify the affected sub-tree 
      percolateDown_recur(array, size, swapCandidate);
    }
  }

  // percolate down - max heap - recur
  void percolateDown_maxHeap_recur(vector<int>& array, int size, int n) {
    int swapCandidate = n; // initialize min as root
    int left = 2 * n + 1; // left child
    int right = 2 * n + 2; // right child

    // If left child is smaller than root 
    if (left < size && array[left] > array[swapCandidate])
      swapCandidate = left;

    // If right child is smaller than smallest
    if (right < size && array[right] > array[swapCandidate])
      swapCandidate = right;

    // If smallest is not root 
    if (swapCandidate != n)
    {
      swap(array[n], array[swapCandidate]);

      // Recursively heapify the affected sub-tree 
      percolateDown_maxHeap_recur(array, size, swapCandidate);
    }
  }

  void percolateUp(vector<int>& array, int index) {
    while (index > 0) {
      int parentIndex = (index - 1) / 2;

      if (array[parentIndex] <= array[index])
        break;

      swap(array[parentIndex], array[index]);
      index = parentIndex;
    }
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

  //static void printTree(TreeNode* root) {
  //  auto height = getHeight(root);
  //  vector<string> strs(height + 1);
  //  printPreOrder(root, strs, 0, height);

  //  for (auto n = 0; n != strs.size(); ++n)
  //    if(!all_of(strs[n].begin(), strs[n].end(), isspace))
  //      cout << strs[n] << endl;
  //  cout << endl;
  //}

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

private:

  static void printPreOrder(TreeNode* root, vector<string>& strs, int level, int height) {
    auto numSpacing = (int)pow(2, height - level - 1);
    for (auto n = 0; n != numSpacing; ++n)
      strs[level] += " ";

    if (!root) {
      strs[level] += " ";
      return;
    }
    else {
      strs[level] += to_string(root->value);
    }

    printPreOrder(root->left, strs, level + 1, height);
    printPreOrder(root->right, strs, level + 1, height);
  }

  static int getHeight(TreeNode* root) {
    if (!root) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
  }
};
