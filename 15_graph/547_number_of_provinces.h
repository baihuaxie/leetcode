#ifndef _94_547_NUMBER_OF_PROVINCES_H_
#define _94_547_NUMBER_OF_PROVINCES_H_
#include <iostream>
#include <vector>       // std::vector

using namespace std;

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        // this problem is equivalent to finding the number of connected components in undirected graph;
        // use DFS;

        int n = isConnected.size();

        // adjacency list;
        vector<vector<int>> graph(n, vector<int>());

        // build adjacency list;
        // isConnected[e] = {u, v, flag} == there is an edge between u and v if flag==true;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (isConnected[i][j]) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        // number of connected components;
        int numComponents = 0;

        vector<bool> visited(n, false);

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                numComponents++;
                dfs(i, graph, visited);
            }
        }

        return numComponents;
    }

    void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited) {
        for (auto v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dfs(v, graph, visited);
            }
        }
    }
};


#endif