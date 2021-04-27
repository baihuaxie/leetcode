#ifndef _72_BINARY_TREE_MAX_PATH_SUM_H_
#define _72_BINARY_TREE_MAX_PATH_SUM_H_
#include <iostream>
#include <algorithm>        //std::max

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
    // a running max to store the max. path sum found during DFS;
    int running_max = INT_MIN;
public:
    int maxPathSum(TreeNode* root) {
        maxPath(root);
        return running_max;
    }
    int maxPath(TreeNode* root) {
        // let maxPathSum(root) return the max. path sum of the sub-tree starting w/t root s/t the path ends at node=root;
        if (root != nullptr) {
            // get left & right child trees;
            // if left / right tree is null or negative, set to 0;
            int left = max(maxPath(root->left), 0);
            int right = max(maxPath(root->right), 0);
            
            // the max. sum possible for current tree; update running max;
            running_max = max(left + right + root->val, running_max);
            
            // returned max sum must be a path that ends at root;
            return root->val + max(left, right);
        }
        return 0;
    }
};

#endif