#ifndef _100_37_SUDOKU_SOLVER_H_
#define _100_37_SUDOKU_SOLVER_H_
#include <iostream>
#include <vector>       //std::vector
#include <cstring>

using namespace std;

class Solution {
    // hashmaps for row, column and cubic;
    // row[i][d] = 1 if digit `d` is in the i-th row;
    int row[9][256];
    int col[9][256];
    int cubic[3][3][256];

public:
    void solveSudoku(vector<vector<char>>& board) {

        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(cubic,0,sizeof(col));

        int sz = board.size();

        // initialize hashmaps;
        for (int r = 0; r < sz; ++r) {
            for (int c = 0; c < sz; ++c) {
                if (board[r][c] != '.') {
                    int digit = board[r][c];
                    row[r][digit] = 1;
                    col[c][digit] = 1;
                    cubic[r / 3][c / 3][digit] = 1;
                }
            }
        }

        dfsSudokuSolver(board, 0, 0);
    }

    bool checkValidDigit(int r, int c, char digit) {
        // check if `digit` is valid at row=r and col=c;
        if (row[r][digit] == 1)
            return false;
        if (col[c][digit] == 1)
            return false;
        if (cubic[r/3][c/3][digit] == 1)
            return false;
        return true;
    }

    bool dfsSudokuSolver(vector<vector<char>>& board, int r, int c) {

        // returns true if the board can be solved from position of row=r and col=c
        // the parent node is the current board
        // a child node is the new board with a digit added to position (r, c)

        // first ensure position (r,c) is valid for dfs, as only valid positions can be in the backtrack search tree
        if (r == 9)
            // all cells have been visited, return true directly
            return true;
        if (c == 9)
            // move to next row
            return dfsSudokuSolver(board, r + 1, 0);
        if (board[r][c] != '.')
            // move to next col
            return dfsSudokuSolver(board, r, c + 1);

        // then loop through child nodes
        // each child node is a new board with position (r, c) filled with a digit chosen from 1~9
        for (char digit = '1'; digit <= '9'; ++digit) {

            // if current node is live
            if (checkValidDigit(r, c, digit)) {

                // update solution
                board[r][c] = digit;

                // update tree
                row[r][digit] = 1;
                col[c][digit] = 1;
                cubic[r / 3][c / 3][digit] = 1;

                // if current node is terminal, return solution
                // this condition can be checked by if all board positions have been visited
                if (dfsSudokuSolver(board, r, c + 1))
                    return true;
                // else current node is expansion, call recursively on next position
                //else
                //    ;
                
                // backtrack
                board[r][c] = '.';
                row[r][digit] = 0;
                col[c][digit] = 0;
                cubic[r / 3][c / 3][digit] = 0;
            }
        }

        // backtrack from parent node
        // note that we didn't do anything on the parent node
        // so just return false
        return false;
    }
};

#endif