#ifndef _50_322_COIN_CHANGE_H_
#define _50_322_COIN_CHANGE_H_
#include <iostream>
#include <vector>           //std::vector
#include <algorithm>        //std::min
#include <limits>           //std::INT_MAX

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {

        int m = coins.size();

        // dp[i] = fewest # of coins to sum to i
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        // loop
        for (int i = 1; i <= amount; i++) {
            // update rule: check each coin
            for (int j = 0; j < m; j++) {
                if (coins[j] > i)
                    continue;
                else if (coins[j] == i) {
                    dp[i] = 1;
                    break;
                }
                else {
                    if (dp[coins[j]] != -1 && dp[i-coins[j]] != -1)
                        dp[i] = min(dp[i], dp[coins[j]] + dp[i - coins[j]]);
                }
            }
            if (dp[i] == INT_MAX)
                dp[i] = -1;
        }

        return dp[amount];
    }
};

#endif