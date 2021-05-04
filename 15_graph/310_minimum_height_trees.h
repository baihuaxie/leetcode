#ifndef _79_310_MINIMUM_HEIGHT_TREES_H_
#define _79_310_MINIMUM_HEIGHT_TREES_H_
#include <iostream>
#include <queue>        //std::queue
#include <vector>       //std::vector

using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // main idea: root(s) of MHTs must be middle nodes on the longest path b/t two leaf nodes;
        // can adapt BFS topological sort procedure to find the roots;
        // by removing nodes w/t degree=1 level by level until the last 1 or 2 nodes;

        vector<int> res;

        // if n == 1, just return the node;
        if (n == 1) {
            res.push_back(0);
            return res;
        }

        // use adjacency list to represent graph;
        // graph[u] = vector of neighbor nodes of u;
        vector<vector<int>> graph(n, vector<int>());

        // degrees[u] == number of edges connected to node u;
        // used in bfsTopoSort;
        vector<int> degrees(n, 0);

        // build adjacency list from edges;
        // edge[i] = {u, v} -> an undirected edge exists b/t nodes u and v;
        int num_edges = edges.size();
        for (int i = 0; i < num_edges; ++i) {
            // edges are undirected;
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
            // update degrees;
            degrees[edges[i][0]]++;
            degrees[edges[i][1]]++;
        }

        // BFS queue: holds all nodes w/t degree=1; i.e. leaf nodes;
        queue<int> q;

        // initialize BFS queue w/t existing leaf nodes in the graph;
        for (int i = 0; i < n; ++i) {
            if (degrees[i] == 1)
                q.push(i);
        }

        // adapt BFS topological sort;
        // only keep removing leaf nodes when there are more than 2 nodes remaining;
        // when n == 2 or n == 1, the root(s) have been found;
        // note that in case when n == 2, but there should be just one root node, the
        // redundant node would have kept being removed in the for-loop before exiting;
        // after exting the while-loop, the content in q is the root(s);
        while (n > 2) {
            int q_size = q.size();
            // BFS removes nodes level by level;
            for (int i = 0; i < q_size; ++i) {
                int u = q.front();
                q.pop();
                n--;
                // visit neighbors;
                for (auto v : graph[u]) {
                    // remove leaf node u;
                    // add v to queue if v becomes a new leaf node;
                    if (--degrees[v] == 1)
                        q.push(v);
                }
            }
        }
        // pop content of q and return;
        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }

        return res;
    }
};

#endif