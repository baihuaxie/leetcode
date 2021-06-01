#ifndef _84_684_REDUNDANT_EDGE_H_
#define _84_684_REDUNDANT_EDGE_H_
#include <iostream>
#include <vector>       //std::vector

using namespace std;

class Solution {
    // WQUPC union-find;
    // id[i] = root of node i;
    vector<int> id;
    // sz[i] = depth of tree from root node i; only valid if i is a root node;
    vector<int> sz;

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // use union-find;
        // loop through edges {u, v} in order; if both u and v have the same root, then edge {u, v} is the back edge, return it;
        // else join u and v in the same tree;

        // initialize union-find structures;
        int n = edges.size();
        for (int i = 0; i < n; ++i) {
            id.push_back(i);
            sz.push_back(1);
        }

        vector<int> res;

        // loop through edges;
        for (auto e : edges) {
            // e = {u, v}; node id should be decreased by 1 to start from 0;
            int u = e[0] - 1;
            int v = e[1] - 1;
            
            if (find(u, v))
                res = e;
            else
                unite(u, v);
        }

        return res;
    }

    // root: return the root of node i;
    int root(int i) {
        while (i != id[i]) {
            // path compression;
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    // return true if both node i and j are in the same tree;
    bool find(int i, int j) {
        return root(i) == root(j);
    }

    // join node i and node j into the same tree;
    void unite(int i, int j) {
        int p = root(i);
        int q = root(j);
        if (sz[p] < sz[q]) {
            id[p] = q;
            sz[q] += sz[p];
        }
        else {
            id[q] = p;
            sz[p] += sz[q];
        }
    }
};

#endif
