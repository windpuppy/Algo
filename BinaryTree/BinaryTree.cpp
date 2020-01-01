#include "BinaryTree.h"

int main()
{
  BinaryTree sol;
  
  // PreOrder
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7 };
    auto root = Helper::buildTree(values);
    auto res = sol.preOrder(root); // 1 2 3 4 5 7
    cout << endl;
  }

  // PreOrder - iterative
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.preOrder_iter(root); // 1 2 3 4 5 7
    cout << endl;
  }

  // InOrder
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7 };
    auto root = Helper::buildTree(values); // 4 2 5 1 3 7
    auto res = sol.inOrder(root);
    cout << endl;
  }

  // InOrder - recursive
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.inOrder_iter(root); // 4 2 5 1 3 7
    cout << endl;
  }

  // PostOrder
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7 };
    auto root = Helper::buildTree(values);
    auto res = sol.postOrder(root); // 4 5 2 7 3 1
    cout << endl;
  }

  // PostOrder - iterative
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.postOrder_iter(root); // 4 5 2 7 3 1
    cout << endl;
  }

  // PostOrder - iterative - cheat
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.postOrder_iter_cheat(root); // 4 5 2 7 3 1
    cout << endl;
  }

  // LevelOrder traversal
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, 6, 7, nullopt , nullopt , nullopt , nullopt , nullopt , nullopt , 8 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.levelOrder(root);
  }

  // Zigzag traversal
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, 6, 7, nullopt , nullopt , nullopt , nullopt , nullopt , nullopt , 8 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.zigzag(root);
  }

  // Vertical order traversal - naive O(n^2)
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, 6, 7, nullopt, nullopt, nullopt, nullopt, nullopt, 8, nullopt, 9 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.verticalOrder(root);
  }

  // Vertical order traversal 2 - more efficient O(nlogn)
  {
    vector<optional<int>> values{ 5, 3, 10, nullopt, 4, 8, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, 9 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.verticalOrder2(root);
  }

  // Height
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7, 8 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto height = sol.height(root);
    cout << endl;
  }

  // Height - iterative
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5, nullopt, 7, 8 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto height = sol.height_iter(root);
    cout << endl;
  }

  // IsBalanced
  {
    vector<optional<int>> values{ 1, 2, 3, 4, nullopt, nullopt, 5, 6, nullopt, nullopt, 7 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.isBalanced(root); // false
  }

  // IsBalanced - optimized
  {
    vector<optional<int>> values{ 1, 2, 3, 4, nullopt, nullopt, 5, 6, nullopt, nullopt, 7 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.isBalanced2(root); // false
  }

  // is BST complete
  {
    vector<optional<int>> values{ 1, 2, 3, nullopt, nullopt, 4, 5 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.isCompleted(root);

    vector<optional<int>> values2{ 1, 2, 3, 4, 5, nullopt, nullopt };
    root = Helper::buildTree(values2);
    Helper::printTree(root);
    res = sol.isCompleted(root);
  }

  // IsSymmetric
  {
    vector<optional<int>> values{ 3, 5, 5, 4, nullopt, nullopt, 4 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.isSymmetric(root); //true
  }

  // IsSymmetric - iterative
  {
    vector<optional<int>> values{ 1, 2, 2, 3, nullopt, 3, nullopt };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.isSymmetric_iter(root); //false

    vector<optional<int>> values2{ 1, 2, 2, 3, 3, 4, 4 };
    root = Helper::buildTree(values2);
    Helper::printTree(root);
    res = sol.isSymmetric_iter(root);
  }

  // IsTweaked
  {
    vector<optional<int>> onev{ 1, 2, nullopt, 3, 4, nullopt, nullopt, 5 };
    vector<optional<int>> twov{ 1, 2, nullopt, nullopt, 3, 5 };
    auto one = Helper::buildTree(onev);
    auto two = Helper::buildTree(twov);
    auto res = sol.isTweaked(one, two); // false
  }

  // Is BST
  {
    vector<optional<int>> values{ 6, 4, 10, 2, 5, 6, 12 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.isBST(root); // false
  }

  // Get range
  {
    vector<optional<int>> values{ 7, 3, 16, 2, 5, 11, 18, 1, nullopt, 4, 6, nullopt, 12, nullopt, 20 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.getRange(root, -5, -2); // empty
    res = sol.getRange(root, 3, 11);
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Search in BST
  {
    vector<optional<int>> values{ 7, nullopt, 16, 11, 18, nullopt, 12, nullopt, 20 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.searchInBST(root, 10);
    res = sol.searchInBST(root, 10);
  }

  // Find closest
  {
    vector<optional<int>> values{ 8, 7, 15, 6, 9, 11, 13 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.closestInBST(root, 10);
  }

  // Find closest k
  {
    vector<optional<int>> values{ 4, 2, 5, 1, 3 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.closestKInBST(root, 3, 4);
    res = sol.closestKInBST(root, 5, 4);
  }

  // Largest number smaller than target in BST
  {
    vector<optional<int>> values{ 8, 6 };
    auto root = Helper::buildTree(values);
    auto res = sol.largestSmallerInBST(root, 7); // 6
  }

  // 2nd largest in BST
  {
    vector<optional<int>> values{ 3, 1, nullopt, nullopt, 2 };
    auto root = Helper::buildTree(values);
    auto res = sol.secondLargestInBST(root); // 2
  }
  
  // Insert in BST
  {
    vector<optional<int>> values{ 5, 3, 9, 1, 4, 8, 15, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, 12 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.insertInBST(root, 10);
    Helper::printTree(root);
  }

  // Insert in BST - iterative
  {
    vector<optional<int>> values{ 5, 3, 9, 1, 4, 8, 15, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, 12 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.insertInBST_iter(root, 10);
    Helper::printTree(root);
  }

  // Delete in BST
  {
    vector<optional<int>> values{ 3, 2, 8, nullopt, nullopt, 6, 10, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, 12 };
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.deleteTree(root, 2);
    Helper::printTree(res);

    root = Helper::buildTree(values);
    Helper::printTree(root);
    res = sol.deleteTree(root, 8);
    Helper::printTree(res);

    vector<optional<int>> values2{ 3,
      2, 8,
      nullopt, nullopt, 6, 12,
      nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, 11, 14,
      nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, nullopt, 9, nullopt, nullopt, nullopt };
    root = Helper::buildTree(values2);
    auto node9 = sol.searchInBST(root, 9);
    node9->right = new TreeNode(10);
    Helper::printTree(root);
    res = sol.deleteTree(root, 8);
    Helper::printTree(res);

    vector<optional<int>> values3{ 7, 3, nullopt, 2, 5, 1, nullopt, 4, 6 };
    root = Helper::buildTree(values3);
    Helper::printTree(root);
    res = sol.deleteTree(root, 5);
    Helper::printTree(res);

    vector<optional<int>> values4{ 6, 3, 12, 2, 4, 8, 16, 1, nullopt, nullopt, 5, nullopt, 9, 14, 18 };
    root = Helper::buildTree(values4);
    Helper::printTree(root);
    res = sol.deleteTree(root, 6);
    Helper::printTree(res);
  }
  




  // Reconstruct with preOrder and inOrder
  {
    vector<int> preOrder{ 4, 1, 5, 6, 7, 10, 9 };
    vector<int> inOrder{ 1, 6, 5, 7, 4, 10, 9 };
    auto res = sol.reconstructWithPreorderInorder(preOrder, inOrder);
    Helper::printTree(res);
  }

  // Reconstruct with postOrder and inOrder
  {
    vector<int> postOrder{ 6, 7, 5, 1, 9, 10, 4 };
    vector<int> inOrder{ 1, 6, 5, 7, 4, 10, 9 };
    auto res = sol.reconstructWithPostorderInorder(postOrder, inOrder);
  }

  // Reconstruct with levelOrder and inOrder
  {

  }

  // Reconstruct BST with preOrder
  {
    vector<int> preOrder{ 4, 2 };
    auto res = sol.reconstructBSTWithPreOrder(preOrder);
  }

  // Reconstruct BST with postOrder
  {
    vector<int> postOrder{ 1, 2, 4, 7, 5, 10, 13, 12, 8, 3 };
    auto res = sol.reconstructBSTWithPostOrder(postOrder);
    Helper::printTree(res);
  }

  // Recover BST
  {
    vector<optional<int>> values{ 5, 3, 9, INT_MIN, 2 };
    auto root = Helper::buildTree(values);
    auto res = sol.recoverBST(root);
  }

  // Flatten
  {
    vector<optional<int>> values{ 1, 2, 5, 3, 4, nullopt, 6 };
    auto root = Helper::buildTree(values);
    auto res = sol.flattenBinaryTreeToLinkedList(root);
    Helper::printTree(res);
    root = Helper::buildTree(values);
    res = sol.flattenBinaryTreeToLinkedList2(root);
    Helper::printTree(root);
  }
  
  // LCA 1
  {
    vector<optional<int>> values{ 5, 9, 12, 2, 3, nullopt, 14 };
    auto root = Helper::buildTree(values);
    auto res = sol.LCA1(root, root->left->left, root->right);
  }

  // LCA 2 - with parent
  {
    vector<optional<int>> values{ 5, 9, 12, 2, 3, nullopt, 14};
    auto root = Helper::buildTreeP(values);
    auto res = sol.LCA2(root->left->left, root->right->right);
    res = sol.LCA2(root->left->left, root->left);
    res = sol.LCA2(root->left->left, new TreeNodeP(100));
  }

  // LCA 3 - nodes not guaranteed to exist
  {
    vector<optional<int>> values{ 5, 9, 12, 2, 3, nullopt, 14 };
    auto root = Helper::buildTree(values);
    auto res = sol.LCA3(root, root->left->left, new TreeNode(100));
  }

  // LCA 4 - k nodes
  {
    vector<optional<int>> values{ 5, 9, 12, 2, 3, nullopt, 14 };
    auto root = Helper::buildTree(values);
    vector<TreeNode*> nodes;
    nodes.push_back(root->left->left); // 2
    nodes.push_back(root->left->right); // 3
    nodes.push_back(root->right->right); // 14
    auto res = sol.LCA4(root, nodes);

    nodes.pop_back();
    nodes.push_back(root->left); // 9
    res = sol.LCA4(root, nodes);
  }

  // Binary tree paths
  {
    vector<optional<int>> values{ 1, 2, 3, 4, 5};
    auto root = Helper::buildTree(values);
    Helper::printTree(root);
    auto res = sol.binaryTreePaths(root);
  }

  // Path sum to target, root to leaf
  {
    vector<optional<int>> values{ 1 };
    auto root = Helper::buildTree(values);
    auto res = sol.pathSumToTarget(root, 1);
  }

  // Path sum to target, root to leaf, any section
  {
    vector<optional<int>> values{ 1 };
    auto root = Helper::buildTree(values);
    auto res = sol.pathSumToTarget2(root, 1);
  }

  cin.get();
}

