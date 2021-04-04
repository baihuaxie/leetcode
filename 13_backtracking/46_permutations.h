#ifndef _59_46_PERMUTATIONS_H_
#define _59_46_PERMUTATIONS_H_
#include <iostream>
#include <vector>           //std::vector

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {

        int n = nums.size();

        // results
        vector<vector<int>> results;
        vector<int> v;

        // booking of node status
        vector<bool> flags(n, true);

        // backtracking from root
        dfs(0, nums, flags, results, v);

        return results;
    }

    void dfs(int node, vector<int>& nums, vector<bool>& flags, vector<vector<int>>& results, vector<int>& v) {
        int n = nums.size();
        // search child nodes
        for (int i = 0; i < n; ++i) {
            // if node is live
            if (flags[i]) {
                v.push_back(nums[i]);
                // mark nums[i] as dead for current sub-tree
                flags[i] = false;
                // if node is terminal
                if (v.size() == n) {
                    results.push_back(v);
                    // backtrack, nums[i] is live for the next sub-tree
                    flags[i] = true;
                    v.pop_back();
                }
                else
                    // expansion
                    dfs(i, nums, flags, results, v);
            }
        }
        // all child trees have been searched, backtrack;
        v.pop_back();
        flags[node] = true;
    }
};


#endif