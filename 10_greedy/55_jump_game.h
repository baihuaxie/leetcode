#ifndef _JUMP_GAME_H_
#define _JUMP_GaME_H_
#include <iostream>
#include <vector>   //std::vector

using namespace std;

class Solution {
public:
    bool canJump(const vector<int>& nums) {
        // initialize starting index
        int ptr = 0;
        // array size
        int n = nums.size() - 1;

        // loop
        while (ptr <= n) {
            // return true is already at last position
            if (ptr == n)
                return true;
            // return false if stuck at zero
            if (nums[ptr] == 0)
                return false;

            // initialize loop variables
            int jump_pos, max_jump, i;
            jump_pos = ptr;
            max_jump = 0;

            // loop for max. jump position from ptr
            for (i = ptr + 1; i <= ptr + nums[ptr]; i++) {
                // check if last position can be reached
                if (i == n || i + nums[i] >= n)
                    return true;
                // otherwise check the greedy criterion: i + nums[i] = largest && nums[max_pos] != 0
                else if (i + nums[i] >= max_jump) {
                    jump_pos = i;
                    max_jump = i + nums[i];
                }
            }
            // take a jump
            ptr = jump_pos;
        }
        return true;
    }
};


#endif