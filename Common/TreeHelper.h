#pragma once

#include "Common.h"

#include <vector>
#include <optional>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class TreeHelper
{
public:
  static TreeNode* buildTree(const vector<optional<int>>& values, int index = 0) {
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

  static TreeNodeP* buildTreeP(const vector<optional<int>>& values, int index = 0) {
    if (!values.size() || index == values.size()) return NULL;

    TreeNodeP* node = new TreeNodeP(values[index].value());
    node->parent = NULL;

    int i = index * 2 + 1; // left index
    int j = i + 1; // right index

    if (i < values.size() && values[i].has_value()) {
      node->left = buildTreeP(values, i);
      node->left->parent = node;
    }
    if (j < values.size() && values[j].has_value()) {
      node->right = buildTreeP(values, j);
      node->right->parent = node;
    }
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