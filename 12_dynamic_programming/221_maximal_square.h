#ifndef _47_221_MAXIMAL_SQUARE_H_
#define _47_221_MAXIMAL_SQUARE_H_
#include <iostream>
#include <vector>           //std::vector
#include <algorithm>       //std::min, std::max

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        // m = # of rows; n = # of columns;
        int m = matrix.size();
        int n = matrix[0].size();

        // value function dp[i][j] = size of max. square ending at point [i][j]
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // running result
        int max_sz = 0;

        // initialize top-most row
        for (int k = 0; k < n; k++) {
            if (matrix[0][k] == '1') {
                dp[0][k] = 1;
                max_sz = 1;
            }
        }

        // initialize left-most col
        for (int k = 0; k < m; k++) {
            if (matrix[k][0] == '1') {
                dp[k][0] = 1;
                max_sz = 1;
            }
        }

        // loop through matrix
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // update values
                if (matrix[i][j] == '1')
                    dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
                max_sz = max(max_sz, dp[i][j]);
            }
        }

        return max_sz * max_sz;
    }
};

#endif