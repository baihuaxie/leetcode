#ifndef _18_56_MERGE_INTERVALS_H_
#define _18_56_MERGE_INTERVALS_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::sort

using namespace std;


class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // sort intervals by starting index
        sort(intervals.begin(), intervals.end(),
             [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });

        // initialize a const iterator object ptr
        vector<vector<int>>::const_iterator ptr = intervals.cbegin();

        // initialize results
        vector<vector<int>> results;

        // loop while ptr has not reached last position
        while (ptr != intervals.cend()) {
            // set intermediate interval
            vector<int> merged = *ptr++;
            // check if end[i] >= start[i+1] for overlapping intervals
            while ( ptr != intervals.cend() && merged[1] >= (*ptr)[0]) {
                // check if end[i] < end[i+1]; if true, set merged end index to the larger one;
                // otherwise no need to update merged
                if (merged[1] < (*ptr)[1])
                    merged[1] = (*ptr)[1];
                ptr++;
            }
            results.push_back(merged);
        }
        return results;
    }
};


#endif