#ifndef _106_212_WORD_SEARCH_II_1_H_
#define _106_212_WORD_SEARCH_II_1_H_
#include <iostream>
#include <vector>       //std::vector
#include <string>       //std::string
#include <utility>       //std::pair
#include <algorithm>    //std::find, std::max
#include <unordered_set>
#include <cstring>      //std::mem_set

using namespace std;

class Solution {
    // valid[i] = true is words[i] is still LIVE, i.e., has the same prefix w/t current searched word;
    int valid[30000];

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        string s;
        vector<string> res;
        vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<pair<int, int>> track;

        int num = words.size();
        int m = board.size();
        int n = board[0].size();
        // vector<bool> valid(num, true);
        memset(valid, 1, sizeof(valid));

        int max_len = 0;
        for (auto word : words) {
            int len = word.size();
            max_len = max(max_len, len);
        }

        // initiate search from all board positions
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                dfs(r, c, board, words, max_len, dirs, valid, s, track, res);
            }
        }

        return res;
    }

    void dfs1(int r, int c, vector<vector<char>>& board, vector<string>& words, vector<pair<int, int>>& dirs, vector<bool>& valid, string& s,
    vector<pair<int, int>>& track, vector<string>& res) {

        int m = board.size();
        int n = board[0].size();
        int num = words.size();
        int sz = s.size();

        // loop four directions
        for (auto dir : dirs) {
            int nr = r + dir.first;
            int nc = c + dir.second;

            // check current position is valid
            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                continue;
            char t = board[nr][nc];

            // conditional flags
            bool live_flag = false;
            bool found_flag = false;
            vector<bool> new_valid = valid;
            for (int i = 0; i < num; ++i) {
                if (valid[i]) {
                    int word_sz = words[i].size();
                    // s == words[i]
                    if (sz == word_sz)
                        found_flag = true;
                    else if (sz < word_sz) {
                        if (words[i][sz] != t)
                            new_valid[i] = false;
                        else
                            // if any one of `words` contain the correct next char, current node is LIVE
                            live_flag = true;
                    }
                }
            }

            // live nodes
            if (live_flag) {
                // if position has already been searched in current branch, skip it
                if (find(track.begin(), track.end(), make_pair(nr, nc)) != track.end())
                    return;
                track.push_back({nr, nc});
                s.push_back(t);
                if (found_flag)
                    res.push_back(s);
                // no terminal condition, keep expanding on live nodes
                dfs1(nr, nc, board, words, dirs, new_valid, s, track, res);
                // backtrack
                s.pop_back();
                track.pop_back();
            }
        }
    }

    void dfs(int r, int c, vector<vector<char>>& board, vector<string>& words, int& max_len, vector<pair<int, int>>& dirs, int (&valid)[30000], string& s,
    vector<pair<int, int>>& track, vector<string>& res) {

        // check current position is valid
        int m = board.size();
        int n = board[0].size();
        if (r < 0 || r >= m || c < 0 || c >= n)
            return;
        // if position has already been searched in current branch, skip it
        if (find(track.begin(), track.end(), make_pair(r, c)) != track.end())
            return;
        char t = board[r][c];

        int num = words.size();
        int sz = s.size();

        // conditional flags
        bool live_flag = false;
        bool found_flag = false;
        vector<bool> new_valid = valid;
        for (int i = 0; i < num; ++i) {
            if (valid[i]) {
                int word_sz = words[i].size();
                if (sz < word_sz) {
                    if (words[i][sz] != t)
                        new_valid[i] = false;
                    else {
                        // if any one of `words` contain the correct next char, current node is LIVE
                        live_flag = true;
                        if (sz+1 == word_sz)
                            found_flag = true;
                    }
                }
            }
        }

        // live nodes
        if (live_flag) {
            track.push_back({r, c});
            s.push_back(t);
            if (found_flag) {
                // do not push redundant words
                if (find(res.begin(), res.end(), s) == res.end())
                    res.push_back(s);
            }
            // loop four directions
            for (auto dir : dirs) {
                // terminal condition
                if (sz >= max_len || res.size() == words.size())
                    return;
                dfs(r+dir.first, c+dir.second, board, words, max_len, dirs, new_valid, s, track, res);
            }

            // backtrack
            s.pop_back();
            track.pop_back();
        }
    }
};

#endif