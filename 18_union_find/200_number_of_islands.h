#ifndef _67_200_NUMBER_OF_ISLANDS_H_
#define _67_200_NUMBER_OF_ISLANDS_H_
#include <iostream>
#include <vector>       //std::vector

using namespace std;

class Solution {
    // WQUPC union-find data structure
    // id[i] = index of parent node to node=i
    vector<int> id;
    int count;

public:
    int numIslands(vector<vector<char>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        // initialize # of islands
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1')
                    count++;
            }
        }
        
        // initialize id[i]=i; serialize node index = i * num_of_cols + j
        for (int i = 0; i < m * n; ++i) {
            id.push_back(i);
        }

        // loop edges
        for (int i = 1; i < m; ++i) {
            int index = i * n;
            if (grid[i][0] != '0') {
                if (grid[i-1][0] == '1')
                    unite(index, index - n);
            }
        }
        for (int j = 1; j < n; ++j) {
            int index = j;
            if (grid[0][j] != '0') {
                if (grid[0][j-1] == '1')
                    unite(index, index - 1);
            }
        }

        // loop grid
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                int index = i * n + j;
                if (grid[i][j] != '0') {
                    if (grid[i-1][j] == '1')
                        unite(index, index - n);
                    if (grid[i][j-1] == '1')
                        unite(index, index - 1);
                }
            }
        }

        return count;
    }

    // root method: return root of node i
    int root(int i) {
        while (i != id[i]) {
            // path-compression
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    // union method: unite two nodes i & j
    void unite(int i, int j) {
        int p = root(i);
        int q = root(j);
        if (p == q)
            return;
        // always add new node to tree, no need for size check;
        id[p] = q;
        count--;
    }
};


#endif