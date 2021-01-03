#ifndef JUMP_GAME_II
#define JUMP_GAME_II
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::max_element

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        // initialize jumps
        int jumps = 0;
        // initialize starting index
        int ptr = 0;
        // array size
        int n = nums.size();

        // loop
        while (ptr < n) {
            // check if ptr is already the last index
            if (ptr == n - 1)
                return jumps;
            // check if the last index can be reached by one jump from ptr
            else if (ptr + nums[ptr] >= n - 1) {
                jumps++;
                return jumps;
            }
            // otherwise take a greedy step
            else {
                // initialize greedy routine
                int max_jump, max_pos, i;
                max_jump = 0;
                max_pos = 0;

                // greedy criterion: take a jump where from the destination can jump to farthest position
                // i.e., maximize (index + nums[index])
                for (i = ptr+1; i <= ptr + nums[ptr]; i++) {
                    if (i + nums[i] >= max_jump) {
                        max_pos = i;
                        max_jump = i + nums[i];
                    }
                }
                // set destination
                ptr = max_pos;
                // increment jumps
                jumps++;
            }
        }
        return jumps++;
    }
};


int main() {
    Solution sol;
    vector<int> nums = {10,9,8,7,6,5,4,3,2,1,1,0};
    int jumps = sol.jump(nums);
    cout << jumps << endl;
}

#endif