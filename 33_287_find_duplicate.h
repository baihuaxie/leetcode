#ifndef _33_287_FIND_DUPLICATE_H_
#define _33_287_FIND_DUPLICATE_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::swap

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // elements are in [1, n]
        int n = nums.size() - 1;
        int ptr = 0;
        // loop
        while (ptr <= n) {
            if (nums[ptr] == ptr + 1) {
                ptr += 1;
                continue;
            }
            else {
                if (nums[ptr] == nums[nums[ptr]-1])
                    return nums[ptr];
                else
                    swap(nums[ptr], nums[nums[ptr] - 1]);
            }
        }
        return nums[ptr];
    }
};


#endif