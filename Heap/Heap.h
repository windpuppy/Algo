#pragma once

#include "../Common/Common.h"

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <deque>
#include <queue>

using namespace std;

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
