#ifndef _68_207_COURSE_SCHEDULE_H_
#define _68_207_COURSE_SCHEDULE_H_
#include <iostream>
#include <vector>       //std::vector
#include <queue>        //std::queue

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

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

        // bfsTopoSort
        while (!q.empty()) {
            int node = q.front();
            // remove node from graph; this can be used for topological ordering if needed;
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
        return n == 0;
    }
};

#endif