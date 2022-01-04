#ifndef _109_2008_MAX_EARNINGS_FROM_TAXI_H_
#define _109_2008_MAX_EARNINGS_FROM_TAXI_H_
#include <iostream>
#include <vector>       //std::vector
#include <algorithm>    //std::sort, std::max

using namespace std;

class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {

        // sort rides by non-decreasing end points;
        sort(rides.begin(), rides.end(), [](const vector<int>& a, const vector<int>& b)
             { return a[1] < b[1]; });

        // let p[i] = index to the ride with the right-most (largest) end point no greater than rides[i].start
        // i.e. the upper bound that corresponds to the latest non-overlapping preceding ride request;
        // p[0] = -1 -> no disjoint preceding ride requests available;
        int m = rides.size();
        /*vector<int> p(m, -1);
        for (int i = m - 1; i > 0; --i) {
            p[i] = binarySearch(rides, 0, i - 1, rides[i][0]);
        }*/
        vector<vector<int>> p(m, vector<int>(1, -1));

        // first use binary search to find an upper bound index;
        // since there might be multiple rides with the same end points == upper bound;
        // need to perform a subsequent lower bound search with target == upper bound to find a range;
        for (int i = m - 1; i > 0; --i) {
            int ub = binarySearch_ub(rides, 0, i - 1, rides[i][0]);
            // if upper bound doesn't exist then do nothing;
            if (ub == -1)
                continue;
            int lb = binarySearch_lb(rides, 0, i - 1, rides[ub][1]);
            for (int j = lb; j <= ub; ++j) {
                p[i].push_back(j);
            }
        }

        // let dp[i] = max tips for rides[0:i];
        // a dichotomy exists for rides[i]: either it's in or not in the optimal solution;
        // the update rule just takes max of the two scenarios;
        vector<long long> dp(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            long long dp_tmp_max = 0;
            for (int k = 0; k < p[i - 1].size(); ++k)
                dp_tmp_max = max(dp_tmp_max, dp[p[i - 1][k] + 1]);
            dp[i] = max(dp_tmp_max + rides[i-1][2] + rides[i-1][1] - rides[i-1][0], dp[i - 1]);
        }

        return dp[m];
    }

    int binarySearch_ub(vector<vector<int>>& rides, int l, int r, int target) {
        // upper-bound: return the index i to the right-most rides[i][1] <= target;
        // assume in non-decreasing order;
        // returns -1 if no such element exists;
        if (l > r)
            return r;
        else {
            int mid = (l + r) / 2;
            if (rides[mid][1] > target)
                // go left
                return binarySearch_ub(rides, l, mid-1, target);
            else
                // go right
                return binarySearch_ub(rides, mid + 1, r, target);
        }
    }

    int binarySearch_lb(vector<vector<int>>& rides, int l, int r, int target) {
        // lower-bound: return the index i to the right-most rides[i][1] <= target;
        // assume in non-decreasing order;
        // returns rides.size() if no such element exists;
        if (l > r)
            return l;
        else {
            int mid = (l + r) / 2;
            if (rides[mid][1] >= target)
                // go left
                return binarySearch_lb(rides, l, mid-1, target);
            else
                // go right
                return binarySearch_lb(rides, mid + 1, r, target);
        }
    }
};

#endif