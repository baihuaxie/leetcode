#ifndef _73_297_SERIALIZE_DESERIALIZE_BINARY_TREE_H_
#define _73_297_SERIALIZE_DESERIALIZE_BINARY_TREE_H_
#include <iostream>
#include <string>           //std::string
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

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // use level-order;
        if (root != nullptr) {
            string s;
            queue(TreeNode *) q;
            q.push(root);

            while (!q.empty()) {
                TreeNode *p = q.front();
                q.pop();

                if (p == nullptr) {
                    // use "#" to represent nullptr values;
                    s.push_back('#');
                }
                else {
                    s.push_back(p->val);
                    q.push(p->left);
                    q.push(p->right);
                }
            }
            return s;
        }
        return "#";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
    }
};

#endif