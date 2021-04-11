#ifndef _63_102_BINARY_TREE_LEVEL_ORDER_TRAVERSAL_H_
#define _63_102_BINARY_TREE_LEVEL_ORDER_TRAVERSAL_H_
#include <iostream>
#include <vector>           //std::vector
#include <queue>            //std::queue
#include <utility>          //std::pair, make_pair

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
    vector<vector<int>> levelOrder(TreeNode* root) {

        // results
        vector<vector<int>> nodes;

        // temporary result to hold nodes on each level
        vector<int> v;

        // level id
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
                        level = p.second;
                        nodes.push_back(v);
                        while (!v.empty())
                            v.pop_back();
                    }
                    v.push_back(p.first->val);
                    q.push(make_pair(p.first->left, level+1));
                    q.push(make_pair(p.first->right, level+1));
                }
            }
            nodes.push_back(v);
        }

        return nodes;
    }
};


#endif