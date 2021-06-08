#ifndef _86_802_FIND_EVENTUAL_SAFE_STATES_H_
#define _86_802_FIND_EVENTUAL_SAFE_STATES_H_
#include <iostream>
#include <vector>       //std::vector
#include <queue>        //std::queue
#include <algorithm>    //std::sort

using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        // first find all safe nodes by checking outdegree == 0;
        // let bfs queue keep all such nodes (with remaining outdegree == 0);
        // do the bfs routine on the reversed graph;
        // pop a node from the queue and add to the results whiling keeping ascending order;
        // note that this is equivalent to bfsTopoSort on the reversed graph;

        int n = graph.size();

        // bfs queue keeps all nodes w/t remaining outdegree == 0;
        queue<int> q;
        // outdegree;
        vector<int> outdegree(n, 0);
        // transposed graph;
        vector<vector<int>> graph_t(n, vector<int>(0));

        for (int i = 0; i < n; ++i) {
            // initialize outdegree;
            outdegree[i] += graph[i].size();
            // initialize bfs queue;
            if (outdegree[i] == 0)
                q.push(i);
            // transpose graph;
            for (auto j : graph[i]) {
                graph_t[j].push_back(i);
            }
        }

        // results;
        vector<int> res;

        // bfs topological sorting on reversed graph;
        while (!q.empty()) {
            int u = q.front();
            res.push_back(u);
            q.pop();

            for (auto v : graph_t[u]) {
                if (--outdegree[v] == 0)
                    q.push(v);
            }
        }

        sort(res.begin(), res.end());
        return res;
    }
};

#endif