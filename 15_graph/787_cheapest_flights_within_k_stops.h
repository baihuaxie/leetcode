#ifndef _92_787_CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H_
#define _92_787_CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H_
#include <iostream>
#include <queue>        //std::priority_queue
#include <vector>       //std::vector

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // use a modified Dijskra's algorithm with constraints of path length <= k;

        // build graph;
        // graph[u] = {{v, w}, ...} -> an edge with price w exists from u to v;
        vector<vector<vector<int>>> graph(n);

        // build adjacency list from flights;
        // flight[i] = {u, v, w};
        for (auto e : flights) {
            graph[e[0]].push_back({e[1], e[2]});
        }

        // last_visit_distance[u] = distance of u to src since the last visit to u;
        vector<int> last_visit_distance(n, INT_MAX);
        last_visit_distance[src] = 0;

        // min priority queue for Dijskra's;
        // q contains {p, u, d} where p is price upper-bound and d is stops for this upper-bound;
        // invariate: q contains only and all active nodes;
        // a node in the BFS procedure is considered to be active if it's the following cases:
        // a) it is a WHITE node, i.e., never visited;
        // b) it is a GREY node, i.e., visited but its neighbors have not been visited;
        // c) it is a BLACK node, i.e., both itself and its neighbors have been visited; however, since
        // this algorithm requires multiple visits to the same node, a BLACK node can still be active if
        // and only if further searching the node might yield benefit;
        // this means if the distance of the node on current path is smaller or equal than the distance of it
        // on last path, it can be considered active;
        // all three cases might be expressed by conditions on last_visit_distance[v];
        priority_queue<vector<int>> q;
        q.push({0, src, 0});

        // Dijskra's
        while (!q.empty()) {
            int p = q.top()[0];
            int u = q.top()[1];
            int d = q.top()[2];
            q.pop();
            // if u == dst and u is GREY, means we have found the optimal path
            // since we would never again visit u after this iteration;
            if ( u == dst)
                return -p;
            // check stops on current path <= k;
            if (d > k)
                continue;
            // mark distance on this visit;
            last_visit_distance[u] = d;
            // visit all neighbors;
            for (auto e : graph[u]) {
                int v = e[0];
                int w = e[1];
                // push only GREY nodes into the priority queue;
                if (last_visit_distance[v] == INT_MAX || last_visit_distance[v] > d) 
                    // relax
                    q.push({p-w, v, d+1});
            }
        }
        return -1;
    }
};



#endif