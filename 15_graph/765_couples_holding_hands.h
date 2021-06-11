#ifndef _90_765_COUPLES_HOLDING_HANDS_H_
#define _90_765_COUPLES_HOLDING_HANDS_H_
#include <iostream>
#include <vector>       //std::vector
#include <map>          //std::map
#include <utility>      //std::pair, make_pair

using namespace std;

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        // idea: let each node in the graph represent two people, so there are N nodes;
        // add an edge b/t node A and B if both contain one of the partners in any couple;
        // build this graph based on input;
        // then use either dfs or bfs to traverse the graph while making swaps;
        // color the nodes: WHITE = contains people from different couples; BLACK = contains a couple;
        // condition: make a swap both node u and v are WHITE && there is an edge b/t u and v;
        // count number of swaps and return it once graph traversal is finished;

        // graph in adjacency list;
        map<pair<int, int>, vector<pair<int, int>>> graph;

        // node colors;
        map<pair<int, int>, bool> matched;

        // initialize;
        int n = row.size();
        for (int i = 0; i < n / 2; ++i) {
            auto node = make_pair(row[2*i], row[2*i + 1]);
            graph.insert(make_pair(node, vector<pair<int, int>>(0)));
            if (isMatched(row[2*i], row[2*i+1]))
                matched.insert(make_pair(node, true));
            else
                matched.insert(make_pair(node, false));
        }

        // add edges to build adjacency list;
        for (int i = 0; i < n / 2; ++i) {
            for (int j = i + 1; j < n / 2; ++j) {
                auto u = make_pair(row[2*i], row[2*i + 1]);
                auto v = make_pair(row[2*j], row[2*j + 1]);
                if (isMatched(row[2*i], row[2*j]) || isMatched(row[2*i], row[2*j+1]) || 
                    isMatched(row[2*i+1], row[2*j]) || isMatched(row[2*i+1], row[2*j+1])) {
                    graph[u].push_back(v);
                    graph[v].push_back(u);
                }
            }
        }

        int numSwaps = 0;

        // dfs driver;
        for (auto& [u, neighbors] : graph) {
            dfs(u, graph, numSwaps, matched);
        }

        return numSwaps;
    }

    // check if two people are a couple
    bool isMatched(int a, int b) {
        // a couple must have id's 2n and 2n+1;
        if ((a % 2 == 0 && b == a+1) || (b % 2 == 0 && a == b+1))
            return true;
        else
            return false;
    }

    void dfs(const pair<int, int>& u, map<pair<int, int>, vector<pair<int, int>>>& graph, int& numSwaps, map<pair<int, int>, bool>& matched) {
        if (!matched[u]) {
            for (auto v : graph[u]) {
                if (!matched[v]) {
                    // make a virtual swap; don't need to really swap variables;
                    numSwaps++;
                    // after the swap u is always matched;
                    // v would also be matched, if v has no other neighbors;
                    // if v has another neighbor, then v would not be matched;
                    // in either case there is no need to color v;
                    matched[u] = true;
                    dfs(v, graph, numSwaps, matched);
                }
            }
            // when backtrack from u, u is always matched;
            matched[u] = true;
        }
    }
};

#endif