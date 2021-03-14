#ifndef _49_300_LONGEST_INCREASING_SUBSEQUENCE_H_
#define _49_300_LONGEST_INCREASING_SUBSEQUENCE_H_
#include <iostream>
#include <vector>           //std::vector
#include <algorithm>        //std::max

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();

        // dp[i] == length of longest strictly increasing subsequence ending at index=i-1
        vector<int> dp(n, 0);
        // initialize
        dp[0] = 1;

        // running max
        int len = 1;

        // loop
        for (int i = 1; i < n; i ++) {
            // update
            for (int j = i - 1; j >= 0; j--) {
                // strictly increasing
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            // if nums[i] is the smallest
            dp[i] = max(dp[i], 1);

            len = max(len, dp[i]);
        }

        return len;
    }
};


#endif