#ifndef _104_2065_MAXIMUM_PATH_QUALITY_OF_A_GRAPH_II_
#define _104_2065_MAXIMUM_PATH_QUALITY_OF_A_GRAPH_II_
#include <iostream>
#include <vector>       //std::vector
#include <algorithm>    //std::max
#include <cstring>      //memset
#include <utility>      //std::pair

using namespace std;

class SolutionII {
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        int res = values[0];
        vector<vector<pair<int,int>>> graph(n);
        for(int i=0;i<edges.size();i++)
        {
            graph[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            graph[edges[i][1]].push_back({edges[i][0], edges[i][2]});
        }
        
        vector<int> visited(n, 0);
        vector<int> live_visits;
        vector<int> all_dfs_calls;
        // dfs(graph, values, visited, res, 0, 0, 0, maxTime, live_visits, all_dfs_calls);
        // dfs2(graph, values, visited, res, 0, 0, 0, maxTime);
        /*for (auto u : live_visits)
            cout << u << " ";
        cout << endl;
        for (auto u : all_dfs_calls)
            cout << u << " ";
        cout << endl;*/
        cout << "all dfs calls: " << all_dfs_calls.size() << endl;
        cout << "live node visits: " << live_visits.size() << endl;
        return res;
    }
    
    void dfs(vector<vector<pair<int,int>>>& graph, vector<int>& values, vector<int>& visited, int& res, int node, int score, int time, int& maxTime,
    vector<int>& live_visits, vector<int>& all_dfs_calls)
    {
        all_dfs_calls.push_back(node);
        if(time > maxTime)
            return;
        
        live_visits.push_back(node);

        if(visited[node] == 0)
            score += values[node];
        
        visited[node]++;
		
      
        if(node == 0)
            res = max(res, score);
        
        for(auto it : graph[node])
        {
            int neigh = it.first;
            int newTime = time + it.second;
            dfs(graph, values, visited, res, neigh, score, newTime, maxTime, live_visits, all_dfs_calls);
        }
        
        visited[node]--;
    }

    void dfs2(vector<vector<pair<int,int>>>& graph, vector<int>& values, vector<int>& visited, int& res, int node, int score, int time, int& maxTime)
    {
        if(time > maxTime)
            return;

        if(visited[node] == 0)
            score += values[node];
        
        visited[node]++;
		
      
        if(node == 0)
            res = max(res, score);
        
        for(auto it : graph[node])
        {
            int neigh = it.first;
            int newTime = time + it.second;
            dfs2(graph, values, visited, res, neigh, score, newTime, maxTime);
        }
        
        visited[node]--;
    }
};

#endif