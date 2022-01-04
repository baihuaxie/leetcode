#ifndef _108_2056_NUMBER_OF_VALID_MOVE_COMBINATIONS_ON_CHESSBOARD_H_
#define _108_2056_NUMBER_OF_VALID_MOVE_COMBINATIONS_ON_CHESSBOARD_H_
#include <iostream>
#include <vector>       //std::vector
#include <map>          //std::map
#include <string>       //std::string
#include <set>          //std::multiset
#include <utility>      //std::pair
#include <algorithm>    //std::adjacent_find, none_of

using namespace std;

class Solution {
public:
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {

        // possible move directions for each piece;
        map<string, vector<pair<int, int>>> directions;
        for (auto piece : pieces) {
            if (piece == "rook")
                directions.insert({"rook", {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}});
            if (piece == "bishop")
                directions.insert({"bishop", {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}});
            if (piece == "queen")
                directions.insert({"queen", {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}});
        }

        // generate all possible move combinations at each step in the search loop
        // moves[i] = {dir[0], dir[1], ..., dir[n-1]} where dir[j] is a possible move direction for pieces[j];
        int n = pieces.size();
        vector<vector<pair<int, int>>> moves;
        vector<vector<pair<int, int>>::iterator> its(n);
        for (int i = 0; i < n; ++i){
            // initialize iterators to beginning of each vector;
            its[i] = directions[pieces[i]].begin();
        }
        while (its[0] != directions[pieces[0]].end()) {
            // add a move combination;
            vector<pair<int, int>> move;
            for (auto it : its) {
                move.push_back(*it);
            }
            moves.push_back(move);
            // loop combinations backwards from last vector to first;
            ++its[n - 1];
            for (int i = n - 1; (i > 0) && (its[i] == directions[pieces[i]].end()); --i) {
                // restart iterator when it reaches the end + move the next iterator ahead by 1 position;
                its[i] = directions[pieces[i]].begin();
                ++its[i - 1];
            }
        }

        // boards[i] == an 8x8 board that tracks all positions which have already been moved by pieces[i]
        // boards[i][r][c] == true if pieces[i] have not been on position (r,c) before;
        vector<vector<vector<bool>>> boards(n, vector<vector<bool>>(8, vector<bool>(8, true)));
        //for (int i = 0; i < n; ++i) {
        //    boards[i][positions[i][0]][positions[i][1]] = false;
        //}

        int num_combinations = 0;
        vector<pair<int, int>> pos;
        for (auto p : positions) {
            pos.push_back({p[0]-1, p[1]-1});
        }
        dfs(moves, pieces, boards, pos, num_combinations);

        return num_combinations;
    }

    void dfs(vector<vector<pair<int, int>>>& moves, vector<string>& pieces, vector<vector<vector<bool>>>& boards,
             vector<pair<int, int>>& pos, int& num_combinations) {
        
        // check that new positions are valid
        for (auto p : pos) {
            if (p.first < 0 || p.first >= 8 || p.second < 0 || p.second >= 8)
                return;
        }

        // ready data structures for the live condition check;
        int n = pieces.size();
        vector<bool> flags(n);
        for (int i = 0; i < n; ++i)
            flags[i] = boards[i][pos[i].first][pos[i].second];
        multiset<pair<int, int>> pos_set;
        for (auto p : pos)
            pos_set.insert(p);

        // LIVE condition:
        // 1. at least one piece is on a new position which it has not been on before; 
        // 2. no two pieces occupy the same position;    
        if (
            any_of(flags.begin(), flags.end(), [](bool v){ return v; })
            && adjacent_find(pos_set.begin(), pos_set.end()) == pos_set.end()) {

            num_combinations++;

            // update boards
            for (int i = 0; i < n; ++i) {
                boards[i][pos[i].first][pos[i].second] = false;
            }

            // loop possible moves
            for (auto move : moves) {
                // new positions
                vector<pair<int, int>> new_pos(n);
                for (int i = 0; i < n; ++i) {
                    new_pos[i].first = pos[i].first + move[i].first;
                    new_pos[i].second = pos[i].second + move[i].second;
                }
                // expand
                dfs(moves, pieces, boards, new_pos, num_combinations);
            }

            // backtrack
            for (int i = 0; i < n; ++i) {
                boards[i][pos[i].first][pos[i].second] = flags[i];
            }
        }

    }
};

#endif