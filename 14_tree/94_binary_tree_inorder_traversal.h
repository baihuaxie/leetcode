#ifndef _61_94_BINARY_TREE_INORDER_TRAVERSAL_H_
#define _61_94_BINARY_TREE_INORDER_TRAVERSAL_H_
#include <iostream>
#include <vector>           //std::vector

using namespace std;

struct TreeNode {
    // members
    int val = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    // constructors
    TreeNode() = default;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){};
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){};
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> nodes;
        inorder(root, nodes);
        return nodes;
    }

    void inorder(TreeNode* node, vector<int>& nodes) {

        if (node != nullptr) {
            inorder(node->left, nodes);
            nodes.push_back(node->val);
            inorder(node->right, nodes);
        }
    }
};

#endif