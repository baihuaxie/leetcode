#ifndef _75_534_DIAMETER_OF_BINARY_TREE_H_
#define _75_534_DIAMETER_OF_BINARY_TREE_H_
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
    // a running max. to store the max. path found during search;
    int running_max = 0;

public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxPath(root);
        return running_max;
    }

    int maxPath(TreeNode* root) {
        // maxPath(root) returns # of edges of the longest path found in the subtree starting w/t root s/t the path ends at node = root;
        if (root != nullptr) {
            // get child trees;
            int left = maxPath(root->left);
            int right = maxPath(root->right);

            // update running_max w/t the max. possible # of edges;
            running_max = max(left + right + 2, running_max);

            // returned path must end at root node;
            return max(left, right) + 1;
        }
        // if root is null; returns -1 instead of 0 is b/c of the +2 before;
        return -1;
    }
};

#endif
