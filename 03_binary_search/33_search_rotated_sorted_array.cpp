#ifndef SEARCH_ROTATED_SORTED_ARRAY
#define SEARCH_ROTATED_SORTED_ARRAY
#include <iostream>
#include <vector>   //std::vector

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        // initialize indices for binary search
        int l, r, mid;
        l = 0;
        r = nums.size()-1;
        
        // non-recursive search
        while (l <= r) {
            // last element left to search
            if  (l == r)      
            {
                if (target == nums[l])
                    return l;
                else
                    return -1;
            }

            // middle index; left half is l~mid, right half is mid+1~r
            mid = (l + r) / 2;

            // scenarios when target is found directly
            if (nums[l] == target)
                return l;
            if (nums[mid] == target)
                return mid;
            if (nums[r] == target)
                return r;
            
            // scenarios to search in left half
            if  ((nums[l] > nums[mid] && target < nums[mid]) ||                        // pivot & target both in left
                (nums[l] > nums[mid] && target > nums[mid] && target > nums[r]) ||     // pivot in left, target larger than nums[r] so in left
                (nums[mid] > nums[r] && target < nums[mid] && target > nums[l]) ||      // pivot in right, target is larger than nums[l] so in left
                (nums[l] < nums[mid] && nums[mid] < nums[r] && target < nums[mid]))     // no pivot point, target is smaller than nums[mid] so in left
                // discard right half & mid point
                r = mid;
            
            // scenarios to search in right half
            else if  ((nums[l] > nums[mid] && target > nums[mid] && target < nums[r]) ||    // pivot in left, target is between mid and r so in right half
                (nums[mid] > nums[r] && target > nums[mid]) ||                         // pivot & target both in right
                (nums[mid] > nums[r] && target < nums[mid] && target < nums[l]) ||     // pivot in right, target is smaller than nums[l] so in right
                (nums[l] < nums[mid] && nums[mid] < nums[r] && target > nums[mid]))     // no pivot point, target is larger than nums[mid] so in right
                // discard left half & mid point
                l = mid + 1;
            
            // not found
            else
                return -1;
        }
    }
};


int main() {
    Solution sol;
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << sol.search(nums, 6) << endl;
}

#endif