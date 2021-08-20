#ifndef _98_959_REGIONS_CUT_BY_SLASHES_H_
#define _98_959_REGIONS_CUT_BY_SLASHES_H_
#include <iostream>
#include <vector>       //std::vector
#include <map>          //std::map
#include <string>       //std::string
#include <utility>      //std::make_pair, pair

using namespace std;

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        // first build a graph from the grid, then use DFS to count number of connected components;

        int sz = grid.size();

        // adjacency list;
        vector<vector<int>> graph(2*sz*sz, vector<int>());

        // mapping[[i,j]] = {"/", [u, v]};
        // each mapping stores the symbol at grid position [i,j] along with the node id's being assigned;
        // if the symbol is "/" or "\\", assign two nodes; if the symbol is " ", assign one node;
        map<vector<int>, pair<string, vector<int>>> mapping;

        // build graph;
        int n = 0;
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                string s = grid[i].substr(j, 1);

                // build edge between current cell and top cell;
                if (i - 1 >= 0) {
                    string m = mapping[{i - 1, j}].first;
                    int u = mapping[{i - 1, j}].second[0];
                    int v = mapping[{i - 1, j}].second[1];
                    if (m == "/") {
                        if (s == "\\") {
                            graph[n+1].push_back(v);
                            graph[v].push_back(n+1);
                        }
                        else {
                            graph[n].push_back(v);
                            graph[v].push_back(n);
                        }
                    }
                    else {
                        if (s == "\\") {
                            graph[n+1].push_back(u);
                            graph[u].push_back(n+1);
                        }
                        else {
                            graph[n].push_back(u);
                            graph[u].push_back(n);
                        }
                    }
                }
                // build edge between current cell and left cell;
                if (j - 1 >= 0) {
                    string m = mapping[{i , j - 1}].first;
                    int v = mapping[{i, j - 1}].second[1];
                    graph[n].push_back(v);
                    graph[v].push_back(n);
                }

                if (s == "/" or s == "\\") {
                    mapping.insert({vector<int>({i, j}), make_pair(s, vector<int>({n, ++n}))});
                }
                else {
                    mapping.insert({vector<int>({i, j}), make_pair(s, vector<int>({n, n}))});
                }

                n++;
            }
        }

        // find number of connected components;
        int numComponents = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                numComponents++;
                dfs(i, graph, visited);
            }
        }

        return numComponents;
    }

    void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited) {
        for (auto v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dfs(v, graph, visited);
            }
        }
    }
};


#endif