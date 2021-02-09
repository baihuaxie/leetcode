#ifndef _35_560_SUBARRAY_SUM_K_H_
#define _35_560_SUBARRAY_SUM_K_H_
#include <iostream>
#include <vector>   //std::vector
#include <map>      //std::map

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        int n = nums.size() - 1;

        // prefix sums => the sum of num[i:j] = sums[j]-sums[i]
        // no need to store all sums
        int prefix_sums = 0;

        // a hash table to store prefix_sum: counts
        map<int, int> sums_freq;
        // initialize sums_freq[0] = 1 for cases of nums[i] == k
        sums_freq[0] = 1;

        int count = 0;

        // loop
        for (int i = 0; i <= n; i++) {

            prefix_sums += nums[i];

            // prefix_sums - k = sums[i], a previously visited sum
            count += sums_freq[prefix_sums - k];

            // increment sums count
            sums_freq[prefix_sums]++;
        }

        return count;
    }
};

#endif