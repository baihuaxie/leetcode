#ifndef THREE_SUM_CPP
#define THREE_SUM_CPP
#include <iostream>
#include <algorithm>    //std::sort
#include <vector>       //std::vector

using namespace std;


class Solution {
public:
    // returns a vector whose elements are vectors of ints (triplets)
    vector<vector<int>> threeSum(vector<int>& nums) {
        // sort nums by sort(iter, iter)
        sort(nums.begin(), nums.end());

        // results; initialize to empty vector by default
        vector<vector<int>> res;

        // size of nums
        int n = nums.size();

        // check nums being empty
        // nums.size() = 1 or 2 would be covered by the while-loop condition
        if (nums.empty())
            return res;

        int start, end;
        int target;

        // loop over nums
        for (int i = 0; i < n; i++) {
            // target value is negative of current element
            target = -nums[i];
            // sub-array starts from i+1, ends at nums tail
            start = i + 1;
            end = n - 1;

            // loop over sub-array from start to end
            while (start < end) {
                if (nums[start] + nums[end] < target)
                    // increase sum by increasing start
                    start++;
                else if (nums[start] + nums[end] > target)
                    // decrease sum by decreasing end
                    end--;
                // if three elements sum to zero
                else {
                    // add to res
                    vector<int> v{nums[i], nums[start], nums[end]};
                    res.push_back(v);
                    // move start and end
                    start++;
                    end--;
                    // increase start if subsequent elements are duplicated
                    while (start < end && nums[start] == nums[start-1])
                        start++;
                    // decrease end if preceding elements are duplicated
                    while (start < end && nums[end] == nums[end+1])
                        end--;
                }
            }
            // move i if duplicated
            while (i+1 < n && nums[i] == nums[i+1])
                i++;
        }
        return res;
    }
};

int main() {
    Solution sol;
    // vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<int> nums = {0};
    vector<vector<int>> res;
    res = sol.threeSum(nums);
    // c++ can not cout entire vector as a whole like Python; must do looping?
    for (auto tuple: res) {
        cout << '[';
        for (auto i: tuple) {
            cout << i << ',';
        }
        cout << "]," << endl;
    }
}

#endif