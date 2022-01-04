#ifndef _107_692_24_GAME_H_
#define _107_692_24_GAME_H_
#include <iostream>
#include <vector>           //std::vector
#include <utility>          //std::pair, make_pair

using namespace std;

class Solution {
public:
    bool judgePoint24(vector<int>& cards) {

        // let {norm, denorm} be a pair that describes a "real" division i.e. norm / denorm;
        // - denorm != 0 always holds;
        // - if norm % denorm == 0, evaluates to just norm / denorm;
        // all the numbers in search are represented by such a pair;
        // evaluation only happens at the leaf nodes;

        // initialize
        vector<pair<int, int>> nums;
        for (auto num : cards) {
            nums.push_back({num, 1});
        }

        // backtrack search;
        return dfs(nums);
    }

private:
    pair<int, int> pairAdd(pair<int, int>& a, pair<int, int>& b) {
        return make_pair(a.first * b.second + a.second * b.first, a.second * b.second);
    }

    pair<int, int> pairSubtract(pair<int, int>& a, pair<int, int>& b) {
        return make_pair(a.first * b.second - a.second * b.first, a.second * b.second);
    }

    pair<int, int> pairMult(pair<int, int>& a, pair<int, int>& b) {
        return make_pair(a.first * b.first, a.second * b.second);
    }

    pair<int, int> pairDiv(pair<int, int>& a, pair<int, int>& b) {
        return make_pair(a.first * b.second, a.second * b.first);
    }

    bool evaluate(pair<int, int>& a) {
        if (a.second != 0)
            if (a.first % a.second == 0)
                if (a.first / a.second == 24)
                    return true;
        return false;
    }

    bool dfs(vector<pair<int, int>> nums) {
        
        // evaluate if only one last element left
        int sz = nums.size();
        if (sz == 1) {
            return evaluate(nums[0]);
        }

        // no Live condition; all nodes in the search tree are considered LIVE;
        // pick two numbers;
        for (int i = 0; i < sz; ++i) {
            for (int j = i + 1; j < sz; ++j) {

                // loop four operators
                pair<int, int> a = nums[i];
                pair<int, int> b = nums[j];

                auto it = nums.begin();
                for (auto tmp : {pairAdd(a, b), pairSubtract(a, b), pairSubtract(b, a),
                     pairMult(a, b), pairDiv(a, b), pairDiv(b, a)}) {

                    nums.erase(it + i);
                    nums.erase(it + j - 1);
                    nums.push_back(tmp);

                    // Terminal condition + expansion
                    if (dfs(nums))
                        return true;
                    
                    // backtrack
                    nums.pop_back();
                    nums.insert(it + i, a);
                    nums.insert(it + j, b);
                } 
            }
        }
        return false;
    }
};

#endif