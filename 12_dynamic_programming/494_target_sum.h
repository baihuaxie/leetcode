#ifndef _54_494_TARGET_SUM_H_
#define _54_494_TARGET_SUM_H_
#include <iostream>
#include <vector>           //std::vector

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {

        int n = nums.size();

        // find the sum of all nums
        int tot = 0;
        for (auto num : nums) {
            tot += num;
        }

        if (S > tot || S < -tot)
            return 0;

        // let dp[i][j] == # of ways to sum range nums[0:i] including to number = j - tot;
        // where tot = sum of all elements in nums;
        // there are two possible ways to go from i-1 to i, depending on the value of j:
        // 1) add +nums[i]; this leads to dp[i][j] = dp[i-1][j-nums[i]];
        // 2) add -nums[i]; this leads to dp[i][j] = dp[i-1][j+nums[i]];
        // since dp[i] only requires knowledge of previous row dp[i-1], the 2d value function
        // can be further reduced to 2 1d value functions;
        vector<int> dp1(2 * tot + 1, 0);

        // initialize for the first number in nums
        if (nums[0] == 0)
            dp1[tot] = 2;
        else {
            dp1[tot - nums[0]] = 1;
            dp1[tot + nums[0]] = 1;
        }
        vector<int> dp2 = dp1;

        // loop through index=i in nums
        for (int i = 1; i < n; i++) {
            int a = nums[i];
            // loop through all j's
            for (int j = 0; j < 2 * tot + 1; j++) {
                if (j < a)
                    // case 2)
                    dp2[j] = dp1[j + a];
                else if (j >= a && j <= 2*tot - a)
                    // case 1) + 2)
                    dp2[j] = dp1[j - a] + dp1[j + a];
                else
                    // case 1)
                    dp2[j] = dp1[j - a];
            }
            dp1 = dp2;
        }

        return dp2[S + tot];
    }
};

#endif