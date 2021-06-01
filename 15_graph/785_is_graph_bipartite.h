#ifndef _83_785_IS_GRAPH_BIPARTITE_H_
#define _83_785_IS_GRAPH_BIPARTITE_H_
#include <iostream>
#include <vector>           //std::vector
#include <queue>            //std::queue

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // use BFS to color nodes layer by layer, then check all edges to have both ends w/t different color; if all true return true;
        // graph is adjacency list;
        // always start w/t node id = 0;

        int n = graph.size();

        // bfs queue; stores all visited nodes;
        queue<int> q;

        vector<bool> visited(n, false);
        vector<bool> colors(n, false);

        // bfs driver; graph might be disconnected;
        for (int s = 0; s < n; ++s) {
            if (visited[s])
                continue;

            q.push(s);
            colors[s] = true;
            visited[s] = true;

            // loop
            while (!q.empty()) {
                int u = q.front();
                q.pop();

                // color all unvisited neighbors;
                for (auto v : graph[u]) {
                    if (visited[v])
                        continue;
                    else {
                        visited[v] = true;
                        // opposite color to u;
                        colors[v] = colors[u] ? false : true;
                        q.push(v);
                    }
                }
            }
        }

        // check all edges;
        for (int u = 0; u < n; ++u) {
            for (auto v : graph[u]) {
                // if two ends of the same edge has same color, return false;
                if ((colors[u] && colors[v]) || (!colors[u] && !colors[v]))
                    return false;
            }
        }
        return true;
    }
};

#endif