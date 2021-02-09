#ifndef _29_152_MAX_PROD_SUBARRAY_H_
#define _29_152_MAX_PROD_SUBARRAY_H_
#include <algorithm> //std::max, std::min, std::swap
#include <iostream>
#include <vector> //std::vector

using namespace std;

class Solution {
public:
    int maxProduct(const vector<int>& nums) {

        int n = nums.size();
        if (n < 1)
            return 0;

        // initialize value function
        int vmax = 1;
        int vmin = 1;

        // running max
        int max_prod = nums[0];

        // loop
        for (int i = 0; i < n; i++) {
            int p = nums[i];
            if (p < 0)
                // make a swap; can assume nums[i] to be non-negative in subsequent updates
                swap(vmax, vmin);
            
            // update values
            vmax = max(vmax * p, p);
            vmin = min(vmin * p, p);

            // update running max
            max_prod = max(max_prod, vmax);
        }
        return max_prod;
    }
};

#endif