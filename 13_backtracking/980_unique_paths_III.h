#ifndef _102_980_UNIQUE_PATHS_III_H_
#define _102_980_UNIQUE_PATHS_III_H_
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {

        // get number of empty positions;
        int m = grid.size();
        int n = grid[0].size();
        int cnt = 0;
        int start_i, start_j;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 || grid[i][j] == 2)
                    cnt++;
                if (grid[i][j] == 1) {
                    visited[i][j] = true;
                    start_i = i;
                    start_j = j;
                }
            }
        }
        int num_paths = 0;
        vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        dfs(grid, visited, dirs, start_i, start_j, cnt, m, n, num_paths);
        return num_paths;
    }

    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, vector<vector<int>>& dirs, int pi, int pj, int& cnt, int& m, int& n, int& num_paths) {

        for (auto dir : dirs) {
            int ci = pi + dir[0];
            int cj = pj + dir[1];
            if (ci < 0 || ci >= m || cj < 0 || cj >= n)
                continue;
            if (grid[ci][cj] == 2 && cnt > 1)
                continue;
            // if child node is LIVE
            if (grid[ci][cj] != -1 && !visited[ci][cj]) {
                cnt--;
                visited[ci][cj] = true;
                // check Terminal condition
                if (cnt == 0)
                    num_paths++;
                else
                    dfs(grid, visited, dirs, ci, cj, cnt, m, n, num_paths);
                // backtrack
                cnt++;
                visited[ci][cj] = false;
            }
        }
    }
};