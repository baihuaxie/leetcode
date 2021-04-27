#ifndef _67_226_INVERT_BINARY_TREE_H_
#define _67_226_INVERT_BINARY_TREE_H_
#include <iostream>
#include <queue>            //std::queue

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
    TreeNode* invertTree(TreeNode* root) {
        
        // BFS
        if (root != nullptr) {
            queue<TreeNode*> q;
            q.push(root);

            while (!q.empty()) {
                TreeNode* p = q.front();
                q.pop();

                TreeNode* temp;
                temp = p->left;
                p->left = p->right;
                p->right = temp;

                if (p->left != nullptr)
                    q.push(p->left);
                if (p->right != nullptr)
                    q.push(p->right);
            }
        }

        return root;
    }
};

#endif