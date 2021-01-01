#ifndef FIRST_MISSING_POS_INTEGER
#define FIRST_MISSING_POS_INTEGER
#include <iostream>
#include <vector>   //std::vector
#include <algorithm> //std::swap

using namespace std;


class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // initialize pointers
        // result is in the range [head + 1, tail + 2]
        int head = 0;
        int tail = nums.size() - 1;

        // loop array
        // when head = tail + 1, result = [head + 1, head + 1] so result = head + 1 is determined
        while (head <= tail) {

            // if head points to a valid element & this element is in correct position
            if (nums[head] == head + 1)
                // increment lower limit
                head++;

            // if head points to an invalid element
            // an invalid element is when the value is larger or equal than upper limit, or smaller than lower limit
            // note that if value == upper limit it is still invalid, e.g., for n = 5, value 6 is upper limit, but 6 can not be in the array
            // 2nd & 3rd conditions take care of duplicated elements
            else if (nums[head] >= tail + 2 || nums[head] <= head || nums[head] == nums[nums[head] - 1]) {
                // swap invalid element to tail of the array
                swap(nums[head], nums[tail]);
                // decrement upper limit
                tail--;
            }

            // if head points to a valid element but this element is in an incorrect position
            else
                // swap the element to correct position
                swap(nums[head], nums[nums[head] - 1]);
        }

        // when while loop terminated, the result is always bounded by [head+1, head+1]
        return head + 1;
    }
};


int main() {
    Solution sol;
    vector<int> nums = {1,2,0};
    int res = sol.firstMissingPositive(nums);
    cout << res << endl;
}


#endif