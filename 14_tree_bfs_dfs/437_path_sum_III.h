#ifndef _71_437_PATH_SUM_III_H_
#define _71_437_PATH_SUM_III_H_
#include <iostream>
#include <map>          //std::map

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
    int count = 0;
    int pathSum(TreeNode* root, int targetSum) {
        // hash map: prefix[i] == count of path prefix sum equal to i;
        // prefix sum = sum of node value from root to current node;
        map<int, int> prefix;

        // add occurrence '0'; for path starts w/t root node;
        prefix[0]++;

        dfs_prefix(root, prefix, 0, targetSum);

        return count;
    }

    void dfs_prefix(TreeNode* root, map<int, int>& prefix, int curr_sum, int targetSum) {
        if (root != nullptr) {
            // curr_sum == path sum from root to current node;
            curr_sum += root->val;
            // path[i+1:j] = prefix[j] - prefix[i] == targetSum;
            // let j be the current root node, so prefix[j] == curr_sum;
            // so curr_sum - targetSum = prefix[i], a preceding prefix sum;
            count += prefix[curr_sum - targetSum];
            // add curr_sum to prefix counts;
            prefix[curr_sum]++;

            dfs_prefix(root->left, prefix, curr_sum, targetSum);
            dfs_prefix(root->right, prefix, curr_sum, targetSum);

            // at dfs return, need to subtract the current path sum, as current node should not
            // be counted in any future paths;
            prefix[curr_sum]--;
        }
    }
};

#endif