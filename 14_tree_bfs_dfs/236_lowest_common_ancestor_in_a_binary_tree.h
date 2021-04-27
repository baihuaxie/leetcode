#ifndef _70_236_LOWEST_COMMON_ANCESTOR_IN_A_BINARY_TREE_H_
#define _70_236_LOWEST_COMMON_ANCESTOR_IN_A_BINARY_TREE_H_
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // the problem is constrained s/t both p & q are present in the tree starting w/t root;
        // but this constraint does not hold for any recursive sub-tree calls;
        // let lowestCommonAncestor() return the following:
        // 1) if neither p nor q is present in the subtree of root, return nullptr;
        // 2) if either p or q is present, return pointer to p or q => p can be thought of as the LCA of itself and null;
        // 3) if both p and q are present, return their LCA;

        // covers case 1)
        if (root == nullptr)
            return root;
        // covers cases 2) + 3)
        if (root == p || root == q)
            return root;

        // call recursively on two sub-trees;
        TreeNode *leftNode = lowestCommonAncestor(root->left, p, q);
        TreeNode *rightNode = lowestCommonAncestor(root->right, p, q);

        // if both child trees return valid pointers, it is case 3);
        // b/c p & q are unique, and there is no duplicated nodes in the tree;
        // they would be in two different child trees => their LCA is root;
        if (leftNode != nullptr && rightNode != nullptr)
            return root;

        // else at most one returned pointer is valid;
        // if rightNode is invalid, assume leftNode is valid, can be either case 2) or 3);
        // for case 2), since rightNode is nullptr, leftNode points to either p or q in the left tree;
        // so should return its pointer => return leftNode;
        // for case 3), both p and q are in left-tree; leftNode is already the LCA => return leftNode;
        // the same logic goes for if leftNode is invalid and rightNode is valid => always return the other pointer;
        // now assume leftNode is also invalid, this is case 1), should return nullptr;
        // since both pointers are nullptr, can return either => the same expression also covers this case;
        // in summary, all of the above cases can be summarized in one succinct expression;
        else
            return (leftNode == nullptr) ? rightNode : leftNode;
    }
};

#endif