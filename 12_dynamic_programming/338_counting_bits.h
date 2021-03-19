#ifndef _52_338_COUNTING_BITS_H_
#define _52_338_COUNTING_BITS_H_
#include <iostream>
#include <vector>       //std::vector
#include <cmath>        //std::pow

using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        // initialize results = value functions;
        // dp[i] = number of 1's in the binary representation of number=i
        vector<int> dp(num + 1, 0);

        // initialize j; keep j = max. integer such that 2**j <= i
        int j = 0;
        int m = pow(2, j);

        // loop from i=1
        for (int i = 1; i <= num; i++){
            // keep j to be max.
            if (i / m == 2)
                m = pow(2, ++j);
            // e.g., dp[9] = dp[9-2**3] + 1 = 2
            if (m < i)
                dp[i] = dp[i - m] + 1;
            // for numbers like 1, 2, 4, 8, ...
            else {
                dp[i] = 1;
            }
        }

        return dp;
    }
};

#endif