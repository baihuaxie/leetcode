#ifndef _82_743_NETWORK_DELAY_TIME_H_
#define _82_743_NETWORK_DELAY_TIME_H_
#include <iostream>
#include <vector>       //std::vector
#include <algorithm>    //std::max_element
#include <queue>        //std::priority_queue

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        // graph's adjacency list;
        // graph[u] = {{v, w}, ...} -> an edge with weight=w exists from node u to v;
        vector<vector<vector<int>>> graph(n);

        // build adjacency list from edge list;
        // times = {u, v, w};
        for (auto e : times) {
            graph[e[0]-1].push_back({e[1]-1, e[2]});
        }

        // distance[u] = current upper-bound of delay from source node k to node u;
        // initialize to INT_MAX;
        vector<int> distance(n, INT_MAX);
        distance[k-1] = 0;

        // priority queue for Dijkstra's;
        // q contains {u, d} where {u} are visited nodes, d = -distance[u];
        // stores negative b/c by default q.front() returns max value -> max negative = min distance;
        priority_queue<vector<int>> q;

        // push source node;
        q.push({k-1, 0});

        // Dijkstra's algorithm via BFS;
        while (!q.empty()) {
            int node = q.top()[0];
            q.pop();
            // visit all neighbors;
            for (auto e : graph[node]) {
                int v = e[0];
                int w = e[1];
                // relax;
                if (distance[v] > distance[node] + w) {
                    distance[v] = distance[node] + w;
                    q.push({v, -distance[v]});
                }
            }
        }

        // find max. distance;
        int delay = *max_element(distance.begin(), distance.end());
        return delay == INT_MAX ? -1 : delay;
    }
};


#endif