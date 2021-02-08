#ifndef _34_448_ALL_MISSING_NUMBERS_H_
#define _34_448_ALL_MISSING_NUMBERS_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::swap

using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        // initialize
        int n = nums.size() - 1;
        vector<int> results;
        int i = 0;

        // re-order nums
        while (i <= n) {
            // check element position 
            if (nums[i] != i + 1 && nums[i] != 0) {
                // check duplicate
                if (nums[i] == nums[nums[i]-1]) {
                    // a duplicated element = another missing element
                    nums[i] = 0;
                }
                else
                    swap(nums[i], nums[nums[i] - 1]);
            }
            else {
                i++;
                continue;
            }
            
        }
        // missing elements are flagged by zero
        for (int i = 0; i <= n; i++) {
            if (nums[i] == 0)
                results.push_back(i + 1);
        }

        return results;
    }
};


#endif