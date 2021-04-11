#ifndef _60_98_VALIDATE_BINARY_SEARCH_TREE_H_
#define _60_98_VALIDATE_BINARY_SEARCH_TREE_H_
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
    bool isValidBST(TreeNode* root) {
        
        // isValidBST(root) = isValidBST(leftTree) && leftTreeSmaller && isValidBST(rightTree) && rightTreeLarger

        if (root == nullptr)
            return true;

        bool leftTree = false, rightTree = false;

        if (isValidBST(root->left)) {
            // check right-most node in leftTree <= root
            TreeNode *ptr = root->left;
            if (ptr == nullptr)
                leftTree = true;
            else {
                while (ptr->right != nullptr)
                    ptr = ptr->right;
                if (ptr->val <= root->val)
                    leftTree = true;
            }
        }

        if (isValidBST(root->right)) {
            // check left-most node in rightTree >= root
            TreeNode *ptr = root->right;
            if (ptr == nullptr)
                rightTree = true;
            else {
                while (ptr->left != nullptr)
                    ptr = ptr->left;
                if (ptr->val >= root->val)
                    rightTree = true;
            }
        }

        return leftTree && rightTree;
    }
};

#endif