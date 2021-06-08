#ifndef _88_839_SIMILAR_STRING_GROUPS_H_
#define _88_839_SIMILAR_STRING_GROUPS_H_
#include <iostream>
#include <vector>       //std::vector
#include <string>       //std::string
#include <map>          //std::map
#include <utility>      //std::pair, std::make_pair

using namespace std;

class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        // step 1: build an undirected graph; use hamming distantce == 2 as condition for an edge;
        // step 2: find number of connected components on this graph using DFS;

        // nodes are represented by str's; graph's adjacency list is a map;
        map<string, vector<string>> graph;
        for (auto str : strs) {
            graph.insert(make_pair(str, vector<string>(0)));
        }

        // build adjacency list;
        int n = strs.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isSimilarbyHammingDist(strs[i], strs[j])) {
                    // add an undirected edge b/t nodes u = strs[i] and v = strs[j];
                    graph[strs[i]].push_back(strs[j]);
                    graph[strs[j]].push_back(strs[i]);
                }
            }
        }

        // find all connected components using DFS;
        map<string, bool> visited;
        for (auto str : strs) {
            visited.insert(make_pair(str, false));
        }
        int connected_components = 0;
        for (auto& [u, neighbors]  : graph) {
            if (!visited[u]) {
                connected_components++;
                dfs(u, visited, graph);
            }
        }
        return connected_components;
    }

    bool isSimilarbyHammingDist(string& src, string& tgt) {
        int dist = 0;
        int n = src.size();
        for (int i = 0; i < n; ++i) {
            if (src[i] != tgt[i])
                dist++;
        }
        return dist == 2 ? true : false;
    }

    void dfs(const string& u, map<string, bool>& visited, map<string, vector<string>>& graph) {
        for (auto v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dfs(v, visited, graph);
            }
        }
    }
};

#endif