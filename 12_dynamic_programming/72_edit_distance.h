#ifndef _56_72_EDIT_DISTANCE_H_
#define _56_72_EDIT_DISTANCE_H_
#include <iostream>
#include <vector>           //std::vector
#include <string>           //std::string
#include <algorithm>        //std::min

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        // let dp[i][j] == min. # of operations needed to convert word1[0:i) to word2[0:j), excluding
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // initialize: converting to empty string
        for (int i = 0; i <= n; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= m; j++) {
            dp[0][j] = j;
        }

        // loop
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1[i-1] == word2[j-1]) {
                    // neighboring entries in dp matrix are separated by at most +/-1;
                    // so dp[i-1][j-1] <= dp[i-1][j]+1 always holds;
                    // only need to consider the case of converting word1[0:i-1) to word2[0:j-1)
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    // case 1): go from state (i-1, j-1) + 1 replace operation;
                    // case 2): go from state (i, j-1) + 1 insertion operation;
                    // case 3): go from state (i-1, j) + 1 deletion operation;
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                }
            }
        }

        return dp[n][m];
    }
};

#endif