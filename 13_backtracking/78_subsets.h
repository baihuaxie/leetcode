#ifndef _22_78_SUBSETS_H_
#define _22_78_SUBSETS_H_
#include <iostream>
#include <vector>   //std::vector

using namespace std;


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // initialize results
        vector<vector<int>> res;
        // initialize backtracking stack
        vector<int> v;

        // backtracking
        find_subsets(nums, res, v, nums.cbegin());

        // add empty element into res
        res.push_back({});

        // return results
        return res;
    }

    void find_subsets(vector<int>& nums, vector<vector<int>>& res, vector<int>& v, vector<int>::const_iterator parent_node) {
        // initialize ptr to current node
        auto ptr = parent_node;

        // loop sub-tree searches; loop condition == bounding condition
        while (ptr != nums.cend()) {
            // current node is always considered live & expansion
            v.push_back(*ptr);
            // push v as a subset into result
            res.push_back(v);
            // search sub-tree; sub-tree does not contain current expansion node
            find_subsets(nums, res, v, ++ptr);
            // after sub-tree search returns, previous current node becomes dead
            v.pop_back();
        }
    }
};

#endif