#pragma once
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct TreeNode {
  int value;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : value(x), left(NULL), right(NULL) {}
};

class Codec {
public:
  string serialize(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    string data;
    while (!q.empty()) {
      auto curr = q.front();
      q.pop();
      if (!curr)
        data += "#,";
      else {
        q.push(curr->left);
        q.push(curr->right);
        data += to_string(curr->value) + ",";
      }
    }
    return data;
  }

  TreeNode* deserialize(string data) {
    TreeNode* root = NULL;
    queue<TreeNode**> q; // Note, this is not a queue of TreeNode*, it's a queue of the addresses of TreeNode*
    q.push(&root);
    auto i = data.begin();
    while (i != data.end()) {
      auto curr = q.front();

      if (*i == '#')
        i += 2;
      else {
        auto j = find(i, data.end(), ',');
        int val = stoi(string(i, j));
        *curr = new TreeNode(val);
        q.push(&((*curr)->left));
        q.push(&((*curr)->right));
        i = j + 1;
      }

      q.pop();
    }
    return root;
  }
};