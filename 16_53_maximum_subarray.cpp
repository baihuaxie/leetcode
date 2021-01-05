#ifndef MAXIMUM_SUBARRAY
#define MAXIMUM_SUBARRAY
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::max

using namespace std;


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // initialize two pointers
        int head, tail;
        head = 0;
        tail = nums.size() - 1;
        // initialze partial sums
        int left_sum, right_sum;
        left_sum = 0;
        right_sum = 0;

        // loop
        while (head < tail) {
            // decide which pointer to move
            if (left_sum + nums[head] <= right_sum + nums[tail]) {
                // check if nums[head] should be included in left sum
                if (left_sum + nums[head] > 0)
                    // add to left sum
                    left_sum += nums[head];
                else
                    // elements preceding head should be excluded
                    left_sum = 0;
                // incremenet head
                head++;
            }
            else {
                // check if nums[tail] should be included in right sum
                if (right_sum + nums[tail] > 0)
                    // add to right sum
                    right_sum += nums[tail];
                else
                    // elements following tail should be excluded
                    right_sum = 0;
                // decrement tail
                tail--;
            }
        }
        // return scenarios
        if (left_sum == 0 && right_sum == 0)
            return nums[head];
        else if (left_sum + nums[head] > 0 || right_sum + nums[head] > 0)
            return left_sum + right_sum + nums[head];
        else
            return max(left_sum, right_sum);
        }
};


int main() {
    Solution sol;
    vector<int> nums = {-2, 1};
    cout << sol.maxSubArray(nums) << endl;
}

#endif