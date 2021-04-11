#ifndef _66_199_BINARY_TREE_RIGHT_SIDE_VIEW_H_
#define _66_199_BINARY_TREE_RIGHT_SIDE_VIEW_H_
#include <iostream>
#include <vector>           //std::vector
#include <queue>            //std::queue
#include <utility>          //std::make_pair, pair

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
    vector<int> rightSideView(TreeNode* root) {
        
        // results
        vector<int> view;

        // temporary result to hold nodes at each level
        int temp;

        // current level
        int level = 0;

        // BFS
        if (root != nullptr) {

            queue<pair<TreeNode *, int>> q;
            q.push(make_pair(root, level));

            while (!q.empty()) {

                pair<TreeNode *, int> p = q.front();
                q.pop();

                if (p.first != nullptr) {
                    if (p.second > level) {
                        view.push_back(temp);
                        level = p.second;
                    }
                    temp = p.first->val;
                    q.push(make_pair(p.first->left, level + 1));
                    q.push(make_pair(p.first->right, level + 1));
                }
            }
            view.push_back(temp);
        }

        return view;
    }
};

#endif