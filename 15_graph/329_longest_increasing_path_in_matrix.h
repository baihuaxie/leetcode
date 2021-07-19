#ifndef _93_LONGEST_INCREASING_PATH_IN_A_MATRIX_H_
#define _93_LONGEST_INCREASING_PATH_IN_A_MATRIX_H_
#include <iostream>
#include <vector>       // std::vector
#include <queue>        // std::queue

using namespace std;

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // first contruct a DAG from the matrix:
        // - a matrix element matrix[i][j] is a node;
        // - a directed edge exists from (i,j) to a neighbor if matrix[i][j] < neighbor;
        // - there can be no cycles so the graph is a DAG;
        // - there can be multiple connected components since there is no edge if two neighbors
        //   are equal in value;
        // the problem is now to find the longest path in the DAG(s); for general graph this is
        // an NP-hard problem, but for DAG there is a linear solution using topological sorting;
        // use bfsTopoSort to construct a topological ordering of the DAG, then count the max.
        // levels in the ordering as the result;

        // for this problem there is no need to use actual adjacency list to represent the graph;
        // because each node would have at most four neighbors (four directions in matrix);
        // each node can be represented by (i,j);

        int M = matrix.size();
        int N = matrix[0].size();

        // neighbors are in 4 directions;
        vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // indegree;
        vector<vector<int>> indegree(M, vector<int>(N, 0));

        // bfs queue; 
        // invariant = all nodes with remaining indegree == 0;
        queue<vector<int>> q;

        // initialize graph and bfs queue;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                // initialize indegrees;
                for (auto dir : dirs) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    if (ni >= 0 && ni < M && nj >= 0 && nj < N) {
                        if (matrix[i][j] > matrix[ni][nj]) {
                            indegree[i][j]++;
                        }
                    }
                }
                // initialize queue;
                if (indegree[i][j] == 0)
                    q.push({i, j});
            }
        }

        // initialize length;
        int length = 0;

        // bfs TopoSort;
        while (!q.empty()) {
            // take note from leetcode-310 Min Height Trees;
            // main the number of nodes with indegree==0 at CURRENT level & only remove their neighbors;

            int q_sz = q.size();

            for (int sz = 0; sz < q_sz; ++sz) {
                auto u = q.front();
                q.pop();
                int i = u[0];
                int j = u[1];

                // visit neighbors;
                for (auto dir : dirs) {
                    int vi = i + dir[0];
                    int vj = j + dir[1];

                    // if there is a directed edge from u to neighbor v;
                    if (vi >= 0 && vi < M && vj >= 0 && vj < N) {
                        if (matrix[i][j] < matrix[vi][vj]) {
                            if (--indegree[vi][vj] == 0)
                                q.push({vi, vj});
                        }
                    }
                }
            }
            // increment level count;
            // this is correct since I'm counting levels here;
            // if I didn't use queue.size() then I'll be counting all the nodes in the topological ordering;
            length++;
        }
        return length;
    }
};

#endif