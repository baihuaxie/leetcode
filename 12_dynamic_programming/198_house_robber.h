#ifndef _46_198_HOUSE_ROBBER_H_
#define _46_198_HOUSE_ROBBER_H_
#include <iostream>
#include <vector>       //std::vector
#include <algorithm>    //std::max

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        // initialize values; dp[i] = opt. solution for subarray [0:i] excluding
        int n = nums.size();
        vector<int> dp(n+1, 0);
        
        if (n > 0)
            dp[1] = nums[0];

        // loop
        for (int i = 1; i < n; i++) {
            dp[i + 1] = max(dp[i - 1] + nums[i], dp[i]);
        }

        return dp[n];
    }
};

#endif