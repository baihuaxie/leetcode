#ifndef _89_685_REDUNDANT_CONNECTION_II_H_
#define _89_685_REDUNDANT_CONNECTION_II_H_
#include <iostream>
#include <vector>       //std::vector
#include <algorithm>    //std::find

using namespace std;

class Solution {
    // union-find structures;
    vector<int> id;
    vector<int> sz;

public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        // the redundant edge can have three possible scenarios:
        // 1) a cross edge or a forward edge; if there is a cross edge there would always be another forward edge if dfs
        // order is changed; can't decide which one to return since I don't know their order in the edge list;
        // 2) a back edge on a non-root node; in this caswe there is a root node w/t indegree==0; there is a cycle, but I must
        // remove this exact back edge;
        // 3) a back edge on a root node; in this case all indegree>=1; there is a cycle that contain this back edge, and I
        // can remove any edge along that cycle to form a directed tree;
        // although DFS can naturally classify the edge types, it can't help me to remove edge in cases 1) and 3) since I don't know order;
        // instead I should use union-find for these two cases;
        // for case 2) union-find won't work b/c it might remove the wrong edge; can modify the union-find but too troublesome,
        // better to just use DFS for this case only;

        // build graph adjacency list;
        int n = edges.size();
        vector<vector<int>> graph(n, vector<int>(0));
        vector<int> indegree(n, 0);
        for (auto edge : edges) {
            graph[edge[0]-1].push_back(edge[1]-1);
            indegree[edge[1]-1]++;
        }

        // node colors; 0=WHITE, 1=GREY, 2=BLAK;
        vector<int> colors(n, 0);

        vector<int> res;

        // if the graph contains a root node, do dfs first to distinguihs cases 1) or 2);
        auto it = ::find(indegree.begin(), indegree.end(), 0);
        if (it != indegree.end()) {
            // do dfs to find back edge on non-root node;
            if (dfs(it - indegree.begin(), graph, res, colors, indegree))
                return res;
        }

        // else either case 1) or case 3); use union-find;
        // initialize union-find structures;
        for (int i = 0; i < n; ++i) {
            id.push_back(i);
            sz.push_back(1);
        }
        for (auto edge : edges) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            // an edge should be removed if:
            // a) both u & v have been grouped under the same root => a cross / forward edge;
            // b) node v have two distinct parent nodes;
            if (find(u, v) || (root(v) != v && root(v) != u)) {
                res = edge;
                break;
            }
            else
                unite(u, v);
        }
        return res;
    }

    // return true if there is a back edge on non-root node; also return this edge through reference argument;
    bool dfs(int u, vector<vector<int>>& graph, vector<int>& back_edge, vector<int>& colors, vector<int>& indegree) {
        // change u color from WHITE to GREY;
        colors[u] = 1;
        for (auto v : graph[u]) {
            // check for back edge == both u and v are GREY;
            if (colors[v] == 1) {
                // check if u is a non-root node;
                if (indegree[u] > 0) {
                    back_edge.push_back(u+1);
                    back_edge.push_back(v+1);
                    return true;
                }
            }
            // for WHITE nodes do dfs, for BLACK nodes do nothing;
            else if (colors[v] == 0)
                return dfs(v, graph, back_edge, colors, indegree);
        }
        // change u color from GREY to BLACK;
        colors[u] = 2;
        return false;
    }

    // return root of node i;
    int root(int i) {
        while (i != id[i]) {
            // path compression;
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    // return true if nodes i and j have same root;
    bool find(int i, int j) {
        return root(i) == root(j);
    }

    // unite nodes i and j to same root;
    // always add link i->j, i.e. i is the parent node;
    void unite(int i, int j) {
        int p = root(i);
        int q = root(j);
        id[q] = p;
        sz[p] += sz[q];
    }
};


#endif