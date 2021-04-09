#ifndef _65_114_FLATTEN_BINARY_TREE_TO_LINKED_LIST_H_
#define _65_114_FLATTEN_BINARY_TREE_TO_LINKED_LIST_H_
#include <iostream>

using namespace std;

struct TreeNode {
    // constructors
    TreeNode() = default;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){};
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){};

    // members
    int val = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

class Solution {
public:
    void flatten(TreeNode* root) {
        
        if (root != nullptr) {
            // after left & right trees are flattened, each is pre-order traversal;
            flatten(root->left);
            flatten(root->right);

            TreeNode *ptr = root->left;

            // if root->left is nullptr, no need to do anything;
            if (ptr != nullptr) {
                // iterate to last node on left tree;
                while (ptr->right != nullptr) {
                    ptr = ptr->right;
                }
                // attach right tree to last node on left tree;
                ptr->right = root->right;
                root->right = root->left;
                root->left = nullptr;
            }
        }
    }
};

#endif