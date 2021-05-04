#ifndef _78_210_COURSE_SCHEDULE_II_H_
#define _78_210_COURSE_SCHEDULE_II_H_
#include <iostream>
#include <queue>            //std::queue
#include <vector>           //std::vector

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

        // graph's adjacency list representation;
        vector<vector<int>> graph(numCourses);
        int edges = prerequisites.size();

        // indegree[i] == remaining number of incoming edges to node i;
        vector<int> indegree(numCourses, 0);
        int n = numCourses;

        // build graph representation from list of edges in prerequisites;
        for (int i = 0; i < edges; ++i) {
            // prerequisitess[i] = {u, v} s/t v -> u;
            graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
            indegree[prerequisites[i][0]]++;
        }

        // q: holds nodes s/t indegree[node] == 0;
        queue<int> q;

        // initialize q by visiting all nodes in graph once;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
                n--;
            }
        }

        // topological order;
        vector<int> order;

        // bfsTopoSort
        while (!q.empty()) {
            int node = q.front();
            // remove node from graph; this can be used for producing a (any) topological ordering;
            order.push_back(node);
            q.pop();

            // visit all neighbors of node;
            for (auto v : graph[node]) {
                // topo-sort routine;
                if (--indegree[v] == 0) {
                    q.push(v);
                    n--;
                }
            }
        }

        // if there is a cycle, then not all nodes can be visited during topo-sort, n must > 0;
        // return a null array if there is a cycle;
        return n == 0 ? order : vector<int>{};
    }
};


#endif