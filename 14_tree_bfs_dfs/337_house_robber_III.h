#ifndef _51_337_HOUSE_ROBBER_III_H_
#define _51_337_HOUSE_ROBBER_III_H_
#include <iostream>
#include <algorithm>            //std::max
#include <utility>              //std::pair

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
    int rob(TreeNode* root) {
        pair<int, int> robRoot = dfs(root);
        return max(robRoot.first, robRoot.second);
    }

    pair<int, int> dfs(TreeNode* root) {
        // return a pair of ints (dp_rob, dp_skip)
        // dp_rob == max. profit of robbing the subtree starting with root, if root is robbed
        // dp_skip == max. profit of robbing the subtree starting with root, if root is not robbed

        if (root == nullptr)
            return {0, 0};

        // recursively traverse child trees
        pair<int, int> robLeft = dfs(root->left);
        pair<int, int> robRight = dfs(root->right);

        // 1. if root is robbed, then dp_rob = root->val + dp_skip(left) + dp_skip(right)
        int dp_rob = root->val + robLeft.second + robRight.second;
        // 2. if root is not robbed, then dp_skip = max(dp_rob(left), dp_skip(left)) + max(dp_rob(right), dp_skip(right))
        int dp_skip = max(robLeft.first, robLeft.second) + max(robRight.first, robRight.second);

        return {dp_rob, dp_skip};
    }
};

#endif