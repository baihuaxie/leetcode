#ifndef _92_787_CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H_
#define _92_787_CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H_
#include <iostream>
#include <queue>        //std::priority_queue
#include <vector>       //std::vector

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // use Dijskra's algorithm with constraints of path length <= k;

        // build graph;
        // graph[u] = {{v, w}, ...} -> an edge with price w exists from u to v;
        vector<vector<vector<int>>> graph(n);

        // build adjacency list from flights;
        // flight[i] = {u, v, w};
        for (auto e : flights) {
            graph[e[0]].push_back({e[1], e[2]});
        }

        // price[u] = current upper bound of price from src to u;
        vector<int> price(n, INT_MAX);
        price[src] = 0;

        // min priority queue for Dijskra's;
        // q contains {u, p, d} where p is price upper-bound and d is distance for this upper-bound;
        queue<vector<int>> q;
        q.push({src, 0, -1});

        // Dijskra's
        while (!q.empty()) {
            int u = q.front()[0];
            int p = q.front()[1];
            int d = q.front()[2];
            q.pop();
            // check distance
            if (d +1 > k)
                continue;
            // visit all neighbors;
            for (auto e : graph[u]) {
                int v = e[0];
                int w = e[1];
                // relax
                if (price[v] > p + w) {
                    price[v] = p + w;
                }
                q.push({v, p+w, d+1});
            }
        }

        if (price[dst] != INT_MAX)
            return price[dst];
        else
            return -1;
    }
};



#endif