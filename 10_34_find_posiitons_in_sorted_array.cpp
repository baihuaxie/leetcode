#ifndef FIND_POSITIONS_IN_SORTED_ARRAY
#define FIND_POSITIONS_IN_SORTED_ARRAY
#include <iostream>
#include <vector>   //std::vector

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // nums size
        int n;
        n = nums.size();
        // initialize binary search indices
        int l, r, mid;
        l = 0;
        r = n - 1;

        // initialize two indices to for backtracking right half
        int l_bt, r_bt;
        l_bt = -1;
        r_bt = -1;

        // initialize results
        vector<int> pos = {-1, -1};

        // empty nums
        if (nums.empty())
            return pos;

        // check loop condition
        while (l < r) {
            // middle index; this guarantees mid+1 always exists in the indices since l<r is the condition
            mid = (l + r) / 2;

            // if the target is found, search for staring & ending positions
            if (target == nums[mid]) {
                // check if mid == starting position
                if (mid == 0 || nums[mid-1] < target) {
                    // log starting position
                    pos[0] = mid;
                    
                    if (pos[1] != -1)
                        // return positions if already found
                        return pos;
                    else {
                        // backtracking if needed
                        if (l_bt != -1) {
                            l = l_bt;
                            r = r_bt;
                        }
                        // search for ending position in right half & include mid (starting = ending is possible)
                        else
                            l = mid;
                    }
                }
                // check if mid == ending position
                // do not use 'else if' here, as these two conditions might satisfy simultaneously
                if (mid == n - 1 || nums[mid+1] > target) {
                    // log ending position
                    pos[1] = mid;

                    if (pos[0] != -1)
                        // return positions if already found
                        return pos;
                    else
                        // search for starting position in left half & include mid (starting = ending is possible)
                        r = mid;
                }
                // if either starting or ending position is not found
                if (pos[0] == -1 || pos[1] == -1) {
                    // for the first time, store mid & r for backtracking the right half
                    if (l_bt == -1) {
                        l_bt = mid+1;
                        r_bt = r;
                    }
                    // search for staring position in left half
                    if (pos[0] == -1) {
                        r = mid;
                        continue;
                    }
                    // search for ending position in the right half
                    if (pos[1] == -1) {
                        l = mid + 1;
                    }
                }
            }

            // otherwise, search for target
            else if (target < nums[mid])
                // search in left half [l:mid]
                r = mid;
            else
                // seearch in right half [mid+1:r]
                l = mid + 1;
        }
        // when there is only one element to search
        if (l == r) {
            if (target == nums[l]) {
                if (pos[0] == -1)
                    pos[0] = l;
                if (pos[1] == -1)
                    pos[1] = r;
            }
        }
        return pos;
    }
};


int main() {
    Solution sol;
    vector<int> nums = {5,5,5,5,7,7,8,8,8,8,8,8,8,8,10,10,10,10};
    //vector<int> nums;
    //vector<int> nums = {0};
    vector<int> pos;
    pos = sol.searchRange(nums, 10);
    cout << '[';
    for (auto p: pos) {
        cout << p << ' ';
    }
    cout << "]" << endl;
}

#endif