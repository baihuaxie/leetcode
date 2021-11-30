#ifndef _104_2065_MAXIMUM_PATH_QUALITY_OF_A_GRAPH_
#define _104_2065_MAXIMUM_PATH_QUALITY_OF_A_GRAPH_
#include <iostream>
#include <vector>       //std::vector
#include <algorithm>    //std::max
#include <cstring>      //memset
#include <utility>      //std::pair

using namespace std;

class Solution {
    int visited[1000], dist[1000];

public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {

        int n = values.size();

        // build graph;
        // graph[u] = {v, time};
        vector<vector<vector<int>>> graph(n);
        for (auto e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }

        /*vector<vector<pair<int, int>>> graph2(n);
        for (auto e : edges) {
            graph2[e[0]].push_back({e[1], e[2]});
            graph2[e[1]].push_back({e[0], e[2]});
        }*/

        // visited[v] = number of visits to node v in current path;
        // dist[v] = distance of node v from node 0 in current path;
        memset(visited, 0, sizeof(visited));
        memset(dist, 0, sizeof(dist));
        visited[0] = 1;

        int time = 0;
        int q = values[0];
        int maxQ = q;

        // dfs backtrack;
        vector<int> live_visits;
        vector<int> all_dfs_calls;
        dfs1(0, graph, values, maxQ, q, time, maxTime);
        // dfs2(0, graph2, values, maxQ, q, time, maxTime);
        /*for (auto u : live_visits)
            cout << u << " ";
        cout << endl;
        for (auto u : all_dfs_calls)
            cout << u << " ";
        cout << endl;*/
        cout << "all dfs calls: " << all_dfs_calls.size() << endl;
        cout << "live node visits: " << live_visits.size() << endl;

        return maxQ;
    }

    void dfs1(int u, vector<vector<vector<int>>>& graph, vector<int>& values, int& maxQ, int q, int time, int& maxTime) {
        for (auto e : graph[u]) {
            int v = e[0];
            int t = e[1];
            int nq = q;
            // LIVE condition
            if (maxTime-time >= t && dist[u] >= dist[v]) {
                int newtime = time + t;
                visited[v]++;
                if (dist[v] == 0 && v != 0)
                    dist[v] = dist[u] + 1;
                if (visited[v] == 1)
                    nq = q + values[v];
                // Terminal condition
                if (v == 0)
                    maxQ = max(maxQ, q);
                // expansion
                dfs1(v, graph, values, maxQ, nq, newtime, maxTime);
                // backtrack
                visited[v]--;
                dist[v] = 0;
            }
        }
    }

    void dfs2(int u, vector<vector<pair<int, int>>>& graph, vector<int>& values, int& maxQ, int q, int time, int& maxTime) {
        for (auto e : graph[u]) {
            int v = e.first;
            int t = e.second;
            int nq = q;
            // LIVE condition
            if (maxTime-time >= t && dist[u] >= dist[v]) {
                int newtime = time + t;
                visited[v]++;
                if (dist[v] == 0 && v != 0)
                    dist[v] = dist[u] + 1;
                if (visited[v] == 1)
                    nq = q + values[v];
                // Terminal condition
                if (v == 0)
                    maxQ = max(maxQ, q);
                // expansion
                dfs2(v, graph, values, maxQ, nq, newtime, maxTime);
                // backtrack
                visited[v]--;
                dist[v] = 0;
            }
        }
    }
};

#endif