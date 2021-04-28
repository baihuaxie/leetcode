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
            queue<TreeNode*> q;
            q.push(root);

            while (!q.empty()) {
                TreeNode* p = q.front();
                q.pop();

                if (p == nullptr) {
                    // use "#" to represent nullptr values;
                    s.append("#,");
                }
                else {
                    s.append(to_string(p->val) + ",");
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
        // construct binary tree from level-order;
        queue<TreeNode*> q;
        TreeNode* root = nullptr;
        if (data != "#") {
            auto j = data.find_first_of(",", 0);
            auto v = data.substr(0, j);
            root = new TreeNode(stoi(v));
            q.push(root);

            auto i = j;
            int n = data.size();

            while (!q.empty()) {
                TreeNode* p = q.front();
                q.pop();

                if (i < n) {
                    for (auto l : {'l', 'r'}) {
                        j = data.find_first_of(",", i + 1);
                        // returns std::string::npos if i+1 exceeds string length;
                        if (j != string::npos) {
                            // get a substr b/t two delimiters;
                            // e.g., return '-5' if the string is "1,-5,3", i=1, j=4;
                            v = data.substr(i + 1, j - 1 - i);
                            if ( v != "#") {
                                TreeNode* ptr = new TreeNode(stoi(v));
                                if (l == 'l')
                                    p->left = ptr;
                                else
                                    p->right = ptr;
                                q.push(ptr);
                            }
                            i = j;
                        }
                    }
                }
            }
        }
        return root;
    }
};

#endif