#ifndef _99_851_LOUD_AND_RICH_H_
#define _99_851_LOUD_AND_RICH_H_
#include <iostream>
#include <vector>   //std::vector

using namespace std;


class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {

        // use DFS;
        // let the graph be a DAG such that u->v means v is richer than u;
        // let answer[v] = i = dfs(v) return the node i such that quiet[i] is the smallest amount in v's sub-graph;
        // after DFS backtrack make an update to answer[u] using answer[v];

        // build graph;
        int n = quiet.size();
        vector<vector<int>> graph(n, vector<int>());
        for (auto e : richer) {
            // e[i] = {u,v} meaning u is richer than v;
            // we want to reverse the edge direction to v->u;
            graph[e[1]].push_back(e[0]);
        }

        // answer;
        vector<int> answer(n, 0);

        // colors;
        vector<bool> visited(n, false);

        // dfs driver;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, graph, visited, quiet, answer);
            }
        }

        return answer;
    }

    void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& quiet, vector<int>& answer) {
        int min_loudness = quiet[u];
        answer[u] = u;
        for (auto v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dfs(v, graph, visited, quiet, answer);
            }
            // update answer
            if (quiet[answer[v]] < min_loudness) {
                min_loudness = quiet[answer[v]];
                answer[u] = answer[v];
            }
        }
    }
};

#endif