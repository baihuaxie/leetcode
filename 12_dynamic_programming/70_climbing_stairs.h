#ifndef _42_70_CLIMBING_STAIRS_H_
#define _42_70_CLIMBING_STAIRS_H_
#include <iostream>
#include <vector>       //std::vector

using namespace std;

class Solution {
public:
    int climbStairs(int n) {

        if (n < 3)
            return n;

        // initialize value function
        vector<int> V(n, 0);
        V[0] = 1;
        V[1] = 2;

        // loop
        for (int i = 2; i < n; i++) {
            // update rule: first step can be either 1 step or 2 steps
            V[i] = V[i - 1] + V[i - 2];
        }

        return V[n - 1];
    }
};

#endif