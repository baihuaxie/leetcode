#ifndef _95_841_KEYS_AND_ROOMS_H_
#define _95_841_KEYS_AND_ROOMS_H_
#include <iostream>
#include <vector>       //std::vector

using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // equivalent to if number of connected components == 1;

        int n = rooms.size();
        int numComponents = 0;

        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                numComponents++;
                dfs(i, rooms, visited);
            }
        }

        return numComponents == 1;
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