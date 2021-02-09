#ifndef _30_168_MAJ_ELEMENT_H_
#define _30_168_MAJ_ELEMENT_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>   //std::count

using namespace std;


class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return plurality(nums, 0, nums.size() - 1);
    }

    int plurality(vector<int>& nums, int start, int end) {
        // terminal case
        if (start == end)
            return nums[start];
        
        // divide
        int m = (start + end) / 2;
        int left_plural = plurality(nums, start, m);
        int right_plural = plurality(nums, m + 1, end);

        // combine
        if (left_plural == right_plural)
            return left_plural;
        else {
            if (count(nums.begin() + start, nums.begin() + end + 1, left_plural) > count(nums.begin() + start, nums.begin() + end + 1, right_plural))
                return left_plural;
            else
                return right_plural;
        }
    }
};