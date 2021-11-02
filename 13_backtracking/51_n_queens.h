#ifndef _101_51_N_QUEENS_H_
#define _101_51_N_QUEENS_H_
#include <iostream>
#include <vector>       //std::vector
#include <string>       //std::string
#include <cstring>      //std::memset

using namespace std;

class Solution {
    // isValid[r][c] = number of Queens that invalidates this position;
    int isValid[10][10];
public:
    vector<vector<string>> solveNQueens(int n) {

        string empty_row(n, '.');
        vector<string> board(n, empty_row);
        vector<vector<string>> boards;

        memset(isValid, 0, sizeof(isValid));

        dfs_nqueens(0, n, board, boards);
        return boards;
    }

    void invalidate(int r, int c, int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == r || j == c || i+j == r+c || i-r == j-c)
                    isValid[i][j]++;
            }
        }
    }

    void validate(int r, int c, int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == r || j == c || i+j == r+c || i-r == j-c)
                    isValid[i][j]--;
            }
        }
    }

    void dfs_nqueens(int row, int n, vector<string>& board, vector<vector<string>>& boards) {

        for (int col = 0; col < n; ++col) {
            // live
            if (isValid[row][col] == 0) {

                invalidate(row, col, n);
                board[row][col] = 'Q';

                // terminal
                if (row == n - 1) {
                    boards.push_back(board);
                }
                // expansion
                else
                    dfs_nqueens(row + 1, n, board, boards);

                // backtrack
                board[row][col] = '.';
                validate(row, col, n);
            }
        }
    }
};


#endif