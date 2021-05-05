#ifndef _80_332_RECONSTRUCT_ITINERARY_H_
#define _80_332_RECONSTRUCT_ITINERARY_H_
#include <iostream>
#include <vector>           //std::vector
#include <map>              //std::map
#include <string>           //std::string
#include <algorithm>        //std::reverse, std::sort
#include <functional>       //std::greater<string>

using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // problem is to find an Eulerian path;
        // use Hierholzer's algorithm w/t DFS;
        // idea is to add an edge {u, v} whenever backtrack from node v to u during dfs;

        // use adjacency list to represent graph;
        // nodes are id-ed by strings, so use map;
        // graph[u] = vector of {v} s/t node v is u's neighbor;
        map<string, vector<string>> graph;

        // build adjacency list representation from list of edges in tickets;
        // tickets[i] = {u, v} = a directed edge from u to v;
        for (auto t : tickets) {
            graph[t[0]].push_back(t[1]);
        }

        // sort adjacency list to ensure access smaller lexical nodes first (backwards access);
        for (auto& adj : graph) {
            sort(adj.second.begin(), adj.second.end(), greater<string>());
        }


        // results;
        vector<string> path;

        // start node = "JFK"
        dfsEulerianPath(graph, "JFK", path);

        // return reversed path;
        reverse(path.begin(), path.end());
        return path;
    }

    void dfsEulerianPath(map<string, vector<string>>& graph, string node, vector<string>& path) {

        // iterate adjacency list backwards to make use of vector.pop_back();
        while (!graph[node].empty()) {
            string v = graph[node].back();
            if (!graph[node].empty())
                graph[node].pop_back();
            dfsEulerianPath(graph, v, path);
        }
        // Hierholzer's algorithm: add node when backtrack from node;
        path.push_back(node);
    }
};


#endif