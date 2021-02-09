#ifndef _19_62_UNIQUE_PATHS_H_
#define _19_62_UNIQUE_PATHS_H_
#include <iostream>
#include <vector>   //std::vector

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // iteration index
        int i, j;
        // initialize value functions data structure as m x n 2d vector
        vector<vector<int>> v(m, vector<int>(n, 0));

        // iterate value functions
        for (i = m - 1; i >= 0; i--) {
            for (j = n - 1; j >= 0; j--) {
                // for bottom & right edges set value to 1
                if ( i == m - 1 || j == n - 1)
                    v[i][j] = 1;
                // for other positions use update rule
                else
                    v[i][j] = v[i + 1][j] + v[i][j + 1];
            }
        }
        // return value at grid's starting position as the result
        return v[0][0];
    }
};


#endif