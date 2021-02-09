#ifndef _28_128_LONGEST_CONSECUTIVE_SEQ_H_
#define _28_128_LONGEST_CONSECUTIVE_SEQ_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::max_element
#include <unordered_map>    //std::unordered_map

using namespace std;

class Solution {
    // WQUPC union-find data structures
    vector<int> id;
    vector<int> sz;

public:
    int longestConsecutive(const vector<int>& nums) {

        int n = nums.size();
        
        if (n < 2)
            return n;
        // initialize
        sz = vector<int>(n, 1);
        for (int i = 0; i < n; i++) {
            id.push_back(i);
        }

        // store visited elements
        unordered_map<int, int> rec;

        // loop
        for (int i = 0; i < n; i++) {
            // bypass duplicated elements
            if (rec.find(nums[i]) != rec.end())
                continue;

            rec[nums[i]] = i;
            
            if (rec.find(nums[i]-1) != rec.end())
                unite(i, rec[nums[i] - 1]);
            if (rec.find(nums[i]+1) != rec.end())
                unite(i, rec[nums[i] + 1]);
        }

        return *max_element(sz.cbegin(), sz.cend());
    }

    // return root of node i
    int root(int i) {
        while (i != id[i]) {
            // path-compression
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    // unite objects i & j
    void unite(int i, int j) {
        int p = root(i);
        int q = root(j);
        if (p == q) return;
        if (sz[p] < sz[q]) {
            id[p] = q;
            sz[q] += sz[p];
        }
        else {
            id[q] = p;
            sz[p] += sz[q];
        }
    }
};

#endif