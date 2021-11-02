#ifndef _102_126_WORD_LADDER_II_H_
#define _102_126_WORD_LADDER_II_H_
#include <iostream>
#include <vector>           //std::vector
#include <string>           //std::string
#include <queue>            //std::priority_queue
#include <unordered_map>    //std::unordered_map
#include <unordered_set>    //std::unodered_set
#include <utility>          //std::make_pair
#include <algorithm>        //std::find

using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {

        // results
        vector<vector<string>> res;

        // if endWord is not in wordList, return empty results directly;
        if (find(wordList.begin(), wordList.end(), endWord) == wordList.end())
            return res;

        // if beginWord is not in wordList, add it;
        if (find(wordList.begin(), wordList.end(), beginWord) == wordList.end()) {
            wordList.push_back(beginWord);
        } 

        // construct a graph from wordList;
        unordered_map<string, vector<string>> graph;
        for (auto word : wordList) {
            graph.insert(make_pair(word, vector<string>(0)));
        }

        // build adjacency list; there is an edge betwee two nodes if the two words differ by just one letter;
        int n = wordList.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                string u = wordList[i];
                string v = wordList[j];
                if (isNeighborbyHammingDistance(u, v)) {
                    graph[u].push_back(v);
                    graph[v].push_back(u);
                }
            }
        }

        return res;
    }

    bool isNeighborbyHammingDistance(string& u, string& v) {
        int dist = 0;
        int n = u.size();
        for (int i = 0; i < n; ++i) {
            if (u[i] != v[i])
                dist++;
        }
        return dist == 1 ? true : false;
    }

    vector<string> bfsDijkstra(string beginWord, string endWord, unordered_map<string, vector<string>>& graph, unordered_set<string>& visited) {
        

    }
};

#endif