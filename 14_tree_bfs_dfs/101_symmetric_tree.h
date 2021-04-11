#ifndef _62_101_SYMMETRIC_TREE_H_
#define _62_101_SYMMETRIC_TREE_H_
#include <iostream>
#include <vector>       //std::vector
#include <queue>        //std::queue (for BFS)
#include <utility>      //std::make_pair, std::pair

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
    bool isSymmetric(TreeNode* root) {
        
        if (root == nullptr)
            return true;

        // BFS queue; each element = pair of <leftNode, rightNode>; left/right can be nullptr;
        queue<pair<TreeNode *, TreeNode *>> q;
        q.push(make_pair(root->left, root->right));

        // loop
        while (!q.empty()) {
            // get new pair to search
            pair<TreeNode *, TreeNode *> p = q.front();
            q.pop();

            // if both nodes are nullptr -> symmetric; continue to next pair
            if (p.first == nullptr && p.second == nullptr)
                continue;

            // if only one of the nodes is nullptr -> asymmetric, return false;
            // this condition works b/c already excluded the case that both are nullptr;
            else if (p.first == nullptr || p.second == nullptr)
                return false;

            // if both are not nullptr, compare their val;
            else {
                if (p.first->val != p.second->val)
                    return false;
            }

            // push new pairs
            q.push(make_pair(p.first->left, p.second->right));
            q.push(make_pair(p.first->right, p.second->left));
        }

        return true;
    }
};

#endif