#ifndef _20_64_MIN_PATH_SUMS_H_
#define _20_64_MIN_PATH_SUMS_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::min

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        // initialize grid sizes
        int m, n;
        m = grid.size();
        n = grid[0].size();

        // initialize value funtions
        vector<vector<int>> v(m, vector<int>(n, 0));
        // initialize last position's value
        v[m - 1][n - 1] = grid[m - 1][n - 1];

        // declare looping index
        int i, j;

        // loop for right edges
        for (i = m - 2; i >= 0; i--) {
            v[i][n - 1] = v[i + 1][n - 1] + grid[i][n - 1];
        }
        // loop for bottom edges
        for (j = n - 2; j >= 0; j--) {
            v[m - 1][j] = v[m - 1][j + 1] + grid[m - 1][j];
        }

        // loop
        for (i = m - 2; i >= 0; i--) {
            for (j = n - 2; j >= 0; j--) {
                // update rule
                v[i][j] = grid[i][j] + min(v[i + 1][j], v[i][j + 1]);
            }
        }

        // return
        return v[0][0];
    }
};

#endif
