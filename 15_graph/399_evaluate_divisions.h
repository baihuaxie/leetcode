#ifndef _81_399_EVALUATE_DIVISIONS_H_
#define _81_399_EVALUATE_DIVISIONS_H_
#include <iostream>
#include <string>       //std::string
#include <vector>       //std::vector
#include <queue>        //std::queue
#include <unordered_map>    //std::unordered_map
#include <unordered_set>    //std::unordered_set
#include <utility>      //std::pair, make_pair

using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // this is a graph problem;
        // equations[i] = {u, v} represents a directed edge b/t two nodes u and v; the weight is values[i] = u / v;
        // when constructing the graph we also add edge v-u w/t weight = 1/value[i] if value[i]!=0;
        // for a query = queries[j] = {s, w}; if either s or w is not in the graph, return -1.0 directly;
        // else, the problem is to find a path from s to w in the graph and return the product of the edge weights;
        // to speed up, we find the path w/t min. number of intermediate nodes, i.e., the shortest path from s to w assuming
        // weights are all 1 in the Dijkstra algorithm => equivalent to just BFS;

        // nodes are represented by strings, therefore the adjacency list is a map of maps, i.e., u -> map<v, value>
        // use std::unordered_map b/c it allows avg. constant access and find() operations;
        unordered_map<string, unordered_map<string, double>> graph;

        // build adjacency list;
        int E = values.size();
        for (int i = 0; i < E; ++i) {
            // equations[i] = {u, v}; values[i] = u / v;
            graph[equations[i][0]].insert(make_pair(equations[i][1], values[i]));
            // also add the reverse edge; the problem is constrained s.t. values > 0.0, so no need to check for division by zero;
            graph[equations[i][1]].insert(make_pair(equations[i][0], 1 / values[i]));
        }

        vector<double> results;

        // loop through all queries; for each query conduct a BFS search over the graph;
        for (auto query : queries) {

            // query = {s, w};
            string src = query[0];
            string dest = query[1];

            // return -1.0 if either src or dest node is not in the graph;
            // b/c when constructing the graph, if u->v is in equations, v->u is also added to the graph;
            // so we can just check the existence of keys as both u and v would be in the map keys;
            if (graph.count(src) == 0 || graph.count(dest) == 0)
                results.push_back(-1.0);

            // return 1.0 if src == dest;
            else if (src == dest)
                results.push_back(1.0);

            // return directly if there is an edge b/t src and dest in the graph already;
            else if (graph[src].count(dest) != 0)
                results.push_back(graph[src][dest]);

            // else use bfs procedure to find a path;
            else {
                // color the visited nodes for each search;
                unordered_set<string> visited;
                double res = bfsDijkstra(query[0], query[1], graph, visited);
                if (res != 0)
                    results.push_back(res);
                else
                    results.push_back(-1.0);
            }
        }

        return results;
    }

    double bfsDijkstra(string src, string dest, unordered_map<string, unordered_map<string, double>>& graph, unordered_set<string>& visited) {

        // assumes src and dest are both in the graph && there is a path from src to dest;

        // bfs queue; invariant = q contains all visited nodes;
        // queue contains <node, product> where product are edge values multiplied from src to node;
        queue<pair<string, double>> q;
        q.push(make_pair(src, 1.0));

        // bfs loop;
        while (!q.empty()) {
            pair<string, double> curr = q.front();
            q.pop();

            visited.insert(curr.first);
            // visit all neighbors;
            // node = <string, double> = {v, value};
            for (auto node : graph[curr.first]) {
                // if node has been visited, do nothing;
                if (visited.count(node.first) == 0) {
                    // update product values along the path;
                    double val = curr.second * node.second;
                    // return directly if dest node has been found;
                    if (node.first == dest)
                        return val;
                    // else push node and new product into queue;
                    else
                        q.push(make_pair(node.first, val));
                }
            }
        }
        // return 0 if path is not found;
        // this shouldn't happen, but add here for completeness;
        return 0;
    }
};

#endif