#ifndef _48_279_PERFECT_SQUARES_H_
#define _48_279_PERFECT_SQUARES_H_
#include <iostream>
#include <vector>           //std::vector
#include <algorithm>        //std::min

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        // dp[i] = least # of perfect squares that sum to i
        vector<int> dp(n+1, 0);

        // loop to n
        for (int i = 1; i <= n; i++) {
            // let min_sqs be maximum possible value at i
            int min_sqs = i;
            // update rule: loop through perfect squares smaller than i only
            for (int j = 1; j * j <= i; j++) {
                min_sqs = min(min_sqs, dp[i - j * j] + 1);
            }
            dp[i] = min_sqs;
        }

        return dp[n];
    }
};

#endif