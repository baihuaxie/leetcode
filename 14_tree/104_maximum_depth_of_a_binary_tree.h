#ifndef _64_104_MAXIMUM_DEPTH_OF_A_BINARY_TREE_H_
#define _64_104_MAXIMUM_DEPTH_OF_A_BINARY_TREE_H_
#include <iostream>
#include <algorithm>        //std::max

using namespace std;

class Solution {
public:
    int maxDepth(TreeNode* root) {

        if (root == nullptr)
            return 0;

        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

#endif