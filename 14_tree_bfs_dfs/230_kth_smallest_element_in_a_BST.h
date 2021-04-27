#ifndef _69_230_KTH_SMALLEST_ELEMENT_IN_A_BST_H_
#define _69_230_KTH_SMALLEST_ELEMENT_IN_A_BST_H_
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
    int kthSmallest(TreeNode* root, int k) {
        // in-order traversal
        vector<int> inorder;
        dfs(root, inorder);
        return inorder[k-1];
    }

    void dfs(TreeNode* root, vector<int>& inorder) {
        if (root != nullptr) {
            dfs(root->left, inorder);
            inorder.push_back(root->val);
            dfs(root->right, inorder);
        }
    }
};


#endif