#ifndef _55_647_PALINDROMIC_SUBSTRING_H_
#define _55_647_PALINDROMIC_SUBSTRING_H_
#include <iostream>
#include <string>           //std::string
#include <vector>           //std::vector

using namespace std;

class Solution {
public:
    int countSubstrings(string s) {

        int n = s.size();

        if (n == 0) return 0;

        // let dp[i][j] == true if substring in range s[i:j] including is palindromic
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        dp[0][0] = true;

        // running counter
        int counter = 1;

        // loop
        for (int j = 1; j < n; j++) {
            for (int i = 0; i <= j; i++) {
                if (s[j] == s[i]) {
                    // update
                    if (j == i || j == i+1 || dp[i+1][j-1]) {
                        dp[i][j] = true;
                        counter++;
                    }
                }
            }
        }

        return counter;
    }
};

#endif