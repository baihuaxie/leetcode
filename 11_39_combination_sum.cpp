#ifndef COMBINATION_SUM
#define COMBINATION_SUM
#include <iostream>
#include <algorithm> // std::sort
#include <vector>   // std::vector

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // initialize backtracking data structures
        vector<int> v;
        // results
        vector<vector<int>> res;

        // sort candidates first
        sort(candidates.begin(), candidates.end());

        // search sub-tree from first index
        combine(candidates, v, res, target, 0);

        return res;
    }

    void combine(vector<int>& candidates, vector<int>& v, vector<vector<int>>& res, int target, int parent_idx) {
        // initialize ptr to parent node
        int ptr = parent_idx;
        int n = candidates.size();
        int value;

        // backtracking: every index < ptr is considered dead node, every index > ptr considered live node
        while (ptr < n) {

            value = candidates[ptr];
            // match; a valid combination is found
            if ( value == target) {
                // push value into vector v
                v.push_back(value);
                // add combination in v to result
                res.push_back(v);
                // pop out value from v before returning to maintain contents in v match with s
                v.pop_back();
                // terminate search
                break;
            }

            // value exceeds target; because all elements in candidates are non-negative, current node is now dead
            else if (value > target) {
                // terminate search directly
                break;
            }
        
            // search sub-tree from current node
            else {
                // current node is live
                v.push_back(value);
                // search sub-tree from expansion node
                combine(candidates, v, res, target - value, ptr);
                // after search returns, current node ptr is dead, so pop it
                v.pop_back();
                // loop to ptr+1
                ptr++;
            }
        }
    }
};


int main() {
    Solution sol;
    vector<int> candidates = {1};
    int target = 1;
    vector<vector<int>> results = sol.combinationSum(candidates, target);

    // print results
    for (auto tuple: results) {
        cout << '[';
        for (auto i: tuple) {
            cout << i << ',';
        }
        cout << "]," << endl;
    }
}


#endif