#ifndef _31_238_PRODUCT_EXCEPT_SELF_H_
#define _31_238_PRODUCT_EXCEPT_SELF_H_
#include <iostream>
#include <vector>   //std::vector

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // initialize results
        int n = nums.size() - 1;
        vector<int> output(n + 1, 1);
        int right_prod = 1;

        // first-pass: build left products
        for (int i = 1; i <= n; i++) {
            output[i] = output[i - 1] * nums[i - 1];
        }
        // second-pass: build right products & combine
        for (int j = n - 1; j >= 0; j--) {
            right_prod *= nums[j+1];
            output[j] *= right_prod;
        }
        return output;
    }
};

#endif