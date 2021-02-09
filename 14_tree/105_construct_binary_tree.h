#ifndef _26_105_CONSTRUCT_BINARY_TREE_H_
#define _26_105_CONSTRUCT_BINARY_TREE_H_
#include <iostream>
#include <vector>   //std::vector

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

        return buildSubTree(preorder.begin(), inorder.begin(), preorder.size());
    }

    TreeNode* buildSubTree(vector<int>::iterator preorder, vector<int>::iterator inorder, int n) {
        
        if (n == 0) return nullptr;

        // locate root element in inorder traversal
        int k = 0;
        while (*(inorder+k) != *preorder)
            k++;
        // create root element
        TreeNode *node = new TreeNode(*preorder);

        node->left = buildSubTree(preorder+1, inorder, k);
        node->right = buildSubTree(preorder + k + 1, inorder + k + 1, n - k - 1);

        return node;
    }
};

#endif