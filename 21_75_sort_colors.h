#ifndef _21_75_SORT_COLORS_H_
#define _21_75_SORT_COLORS_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::swap

using namespace std;

class Solution {
public:
    // naive two-pass solution by counting elements then overwriting
    void sortColors(vector<int>& nums) {
        // initialze counts
        vector<int> counts(3, 0);

        // initialize pointer
        auto ptr = nums.begin();

        // loop to count colors
        while (ptr != nums.end()) {
            // count
            counts[*ptr++] += 1;
        }

        // loop to overwrite nums with counts
        while (ptr != nums.begin()) {
            // decrement ptr
            ptr--;
            // write 2
            if (nums.end() - ptr <= counts[2])
                *ptr = 2;
            // write 1
            else if (nums.end() - ptr > counts[2] && nums.end() - ptr <= counts[1] + counts[2])
                *ptr = 1;
            // write 0
            else
                *ptr = 0;
        }
    }
};

#endif