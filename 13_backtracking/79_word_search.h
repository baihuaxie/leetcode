#ifndef _23_79_WORD_SEARCH_H_
#define _23_79_WORD_SEARCH_H_
#include <iostream>
#include <vector>   //std::vector
#include <string>   //std::string
#include <algorithm>    //std::find

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // initialize backtracking stack for searched words
        vector<vector<int>> v;

        // initialize looping indices
        int i, j;
        int m = board.size();
        int n = board[0].size();

        // loop searches
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                // check if the search should be initiated
                if (board[i][j] == word[0]) {
                    // start a search from current node
                    if (word_search(board, word, v, i, j))
                        return true;
                }
            }
        }
        // otherwise after all search is finished & no word is found
        return false;
    }

    bool word_search(vector<vector<char>>& board, string& word, vector<vector<int>>& v, int i, int j) {
        // current node is always expansion; add node into v
        v.push_back({i,j});
        // return true directly if word is found
        if (v.size() == word.size())
            return true;

        // add live nodes (adjacent nodes) to search stack
        vector<vector<int>> s;
        int m = board.size();
        int n = board[0].size();
        // add left node
        if (j != 0)
            s.push_back({i, j - 1});
        // add downward node
        if (i != m - 1)
            s.push_back({i + 1, j});
        // add right node
        if (j != n - 1)
            s.push_back({i, j + 1});
        // add upward node
        if (i != 0)
            s.push_back({i - 1, j});
        
        // loop while search stack contains available live nodes
        while (!s.empty()) {
            // pop a live node
            vector<int> node(2, -1);
            node = s.back();
            s.pop_back();

            // check if the node has already been searched
            if (find(v.begin(), v.end(), node) != v.end())
                continue;

            // the bounding condition is that if the live node equals the next correct character in word
            // if true the current node is live & expansion
            if (board[node[0]][node[1]] == word[int(v.size())]) {
                // search from expansion node
                if (word_search(board, word, v, node[0], node[1]))
                    // directly return true if the search returned true
                    return true;
            }
        }
        // if the loop terminates with all live nodes now marked dead, return false
        // remove it from v
        v.pop_back();
        return false;
    }
};

#endif