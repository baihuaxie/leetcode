#ifndef _44_96_UNIQUE_BST_H_
#define _44_96_UNIQUE_BST_H_
#include <iostream>
#include <vector>       //std::vector

using namespace std;

class Solution {
public:
    int numTrees(int n) {
        // initialize values
        // V[j][i] = # of unique BST trees constructed by range [j+1:i+1] including
        vector<vector<int>> V(n, vector<int>(n, 0));
        V[0][0] = 1;

        // loop
        for (int i = 1; i <= n - 1; i++) {
            // update V[j][i] for j >= 1
            for (int j = 1; j <= i; j++) {
                V[j][i] = V[j - 1][i - 1];
            }
            // update V[0][i] by counting # of trees using different values as the root
            // root = 1 & root = i
            V[0][i] = V[1][i] + V[0][i - 1];
            // root between 1...i-1
            for (int j = 1; j <= i - 1; j++) {
                V[0][i] += V[0][j - 1] * V[j + 1][i];
            }
        }

        return V[0][n - 1];
    }
};

#endif