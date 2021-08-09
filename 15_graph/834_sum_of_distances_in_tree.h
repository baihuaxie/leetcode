#ifndef _97_834_SUM_OF_DISTANCES_IN_TREE_H_
#define _97_834_SUM_OF_DISTANCES_IN_TREE_H_
#include <iostream>
#include <vector>       //std::vector

using namespace std;

class Solution {
    int numNodes = 0;
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {

        // use DP + dfs;

        // the key difficulty in dfs is that, if node u -> v, I can have all information needed
        // in dp[v] (child node) after dfs(v) for node u, but dp[u] (parent node) won't have all
        // information needed for node v, b/c I don't know anything about u's silblings;
        // this difficulty will be present no matter how I design my dp;
        // the solution is to use two dfs calls;

        // let dp[u] = sum of distances from all nodes in the subtree starting from node u;
        // let sz[u] = number of nodes in the subtree starting from node u (including u itself);
        // let dist[v] = sum of distances from all nodes in the graph, i.e., the desired results;

        // the key is to observe the following three relationships b/t u (parent) -> v (child):
        // a) dp[u] += dp[v] + sz[v];
        // b) sz[u] += sz[v];
        // c) dist[v] = dist[u] + n - 2 * sz[v];

        // two dfs calls:
        // first call to calculate dp and sz;
        // second call to calcuate dist based on dp and sz;
        // two calls must start from the same node and follow exactly the same parent->child visiting
        // sequences; in this case I can actually use dp for dist;

        // build graph;
        vector<vector<int>> graph(n, vector<int>());
        for (auto e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        numNodes = n;

        // dp
        vector<int> dp(n, 0);
        vector<int> sz(n, 0);

        vector<bool> visited(n, false);

        dfs_1(0, graph, visited, dp, sz);
        dfs_2(0, graph, visited, dp, sz);

        return dp;
    }

    int dfs_1(int u, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& dp, vector<int>& sz) {
        sz[u]++;
        visited[u] = true;
        for (auto v : graph[u]) {
            if (!visited[v]) {
                dp[u] += dfs_1(v, graph, visited, dp, sz) + sz[v];
                sz[u] += sz[v];
            }
        }
        return dp[u];
    }

    void dfs_2(int u, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& dp, vector<int>& sz) {
        visited[u] = false;
        for (auto v : graph[u]) {
            if (visited[v]) {
                dp[v] = dp[u] + numNodes - 2 * sz[v];
                dfs_2(v, graph, visited, dp, sz);
            }
        }
    }
};

#endif