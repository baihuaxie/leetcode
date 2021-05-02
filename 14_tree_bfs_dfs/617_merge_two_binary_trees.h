#ifndef _76_617_MERGE_TWO_BINARY_TREES_H_
#define _76_617_MERGE_TWO_BINARY_TREES_H_
#include <iostream>

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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        // let mergeTrees(root1, root2) returns a pointer to root1 s/t the sub-trees are merged by rules;
        // first merge the root nodes, then call this function on the child trees recursively;

        if (root1 == nullptr && root2 == nullptr)
            return nullptr;
        else if (root1 == nullptr && root2 != nullptr)
            return root2;
        else if (root1 != nullptr && root2 == nullptr)
            return root1;
        else {
            root1->val += root2->val;
            root1->left = mergeTrees(root1->left, root2->left);
            root1->right = mergeTrees(root1->right, root2->right);
            return root1;
        }
    }
};

#endif