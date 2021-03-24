#ifndef _53_416_PARTITION_EQUALS_SUBSET_SUM_H_
#define _53_416_PARTITION_EQUALS_SUBSET_SUM_H_
#include <iostream>
#include <vector>           //std::vector

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {

        int n = nums.size();

        /* 
            states = j;
            dp[j][i] == true if number=i can be formed by a subset in range nums[:j] including;
            first get tot = sum of all elements in nums; only need to find up to dp[n][tot/2];
            update rule: at each iteration check to compare i & nums[j];
                - a) if nums[j] == i, set dp[j][i] = true;
                - b) if nums[j] > i, nums[j] should be excluded, so set dp[j][i] = dp[j-1][i];
                - c) if nums[j] < i, nums[j] can either be included or excluded
                    - if included, then dp[j][i] = dp[j-1][i-nums[j]];
                    - if excluded, then dp[j][i] = dp[j-1][i];
                    - result is an 'OR' of the two cases
            
            - can further reduce the value function from 2d to 1d array;
                - only need to access dp[j-1] to update dp[j] => reuse by setting dp[j-1] = dp[j] after update
                - this can be further omitted if only use one 1d array dp
        */

        // find tot
        int tot = 0;
        for (auto num : nums)
        {
            tot += num;
        }
        // tot must be even number if a partition exists; both should sum to tot/2
        if (tot % 2 != 0)
            return false;
        int sum = tot / 2;

        // initialize 1d values; dp[i] == true if number=i can be formed by any subset in nums
        vector<bool> dp(sum + 1, false);
        // set dp[0] to be true, so case a) can be subsumed as dp[i-nums[j]] when i == nums[j] by case c)
        dp[0] = true;

        // nested loop
        for (int j = 0; j < n; j++) {
            // only need to find values up to sum = tot/2
            for (int i = sum; i > 0; i--) {
                // if nums[j] > i, update rule is dp[i] = dp[i] => can be omitted
                if (i >= nums[j])
                    dp[i] = dp[i] || dp[i - nums[j]];
            }
        }
        
        // if tot/2 can be formed by a subset, then a partition exists 
        return dp[sum];
    }
};

#endif