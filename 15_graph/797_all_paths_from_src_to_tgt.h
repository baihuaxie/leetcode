#ifndef _85_797_ALL_PATHS_FROM_SOURCE_TO_TARGET_H_
#define _85_797_ALL_PATHS_FROM_SOURCE_TO_TARGET_H_
#include <iostream>
#include <vector>       //std::vector

using namespace std;

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        // use backtracking + dfs;
        // b/c the graph is DAG, can treat each new node as live; for a live node add it to the temporary result vector s;
        // then check if it is a terminal node -> condition should be that if node == n-1;
        // if true, push s into global result vector res, then pop current node from s;
        // if false, expand current node by calling the dfs routine recursively;
        // after all neighbors have been visited, backtract from parent node by popping from s; this can work b/c s essentially stores
        // the dfs stack;

        // results;
        vector<vector<int>> res;
        vector<int> s;
        s.push_back(0);

        int n = graph.size();

        // call dfs routine from source node 0;
        dfs(0, s, res, graph, n);

        return res;
    }

    void dfs(int u, vector<int>& s, vector<vector<int>>& res, vector<vector<int>>& graph, int n) {
        // visit all neighbors;
        for (auto v : graph[u]) {
            // assume all nodes are live b/c it is DAG;
            s.push_back(v);
            // check for terminal node;
            if (v == n-1) {
                res.push_back(s);
                // backtrack from v;
                s.pop_back();
            }
            // else for expansion node;
            else
                dfs(v, s, res, graph, n);
        }
        // backtrack from u;
        s.pop_back();
    }
};

#endif