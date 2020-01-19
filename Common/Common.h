#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  ListNode* next;
  int value;
  ListNode(int v) : value(v), next(NULL) {};
};

struct RandomListNode {
  int value;
  RandomListNode* next;
  RandomListNode* random;
  RandomListNode(int v) : value(v), next(NULL), random(NULL) {};
};

struct TreeNode {
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : value(v), left(NULL), right(NULL) {}
};

struct TreeNodeP {
  int value;
  TreeNodeP* left;
  TreeNodeP* right;
  TreeNodeP* parent;
  TreeNodeP(int v) : value(v), left(NULL), right(NULL), parent(NULL) {}
};

struct KnaryTreeNode {
  int value;
  vector<KnaryTreeNode*> children;
  KnaryTreeNode(int v) : value(v) {}
};

struct GraphNode {
  int value;
  vector<GraphNode*> neighbors;
  GraphNode(int v) : value(v) {}
};
