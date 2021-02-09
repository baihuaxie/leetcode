#ifndef _32_283_MOVE_ZEROS_H_
#define _32_283_MOVE_ZEROS_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::swap

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // initialize pointers
        vector<int>::iterator ptr1=nums.begin();
        vector<int>::iterator ptr2=nums.begin();

        // one-pass loop
        while (ptr2 < nums.end()) {
            // ptr1: points to element i such that nums[0:i] != 0 && nums[i]==0
            while (ptr1 < nums.end()) {
                if (*ptr1 != 0)
                    ptr1++;
                else
                    break;
            }
            ptr2 = ptr1 + 1;
            // ptr2: points to element j such that nums[i:j] == 0 && nums[j]!=0 && j>=i
            while (ptr2 < nums.end()) {
                if (*ptr2 == 0)
                    ptr2++;
                else {
                    swap(*ptr1, *ptr2);
                    break;
                }
            }
        }
    }
};

#endif