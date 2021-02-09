#ifndef ROTATE_IMAGE
#define ROTATE_IMAGE
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::swap

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // matrix size
        int n = matrix.size();
        // check if matrix is empty
        if (n >= 1) {
            // loop circles
            int k;
            for (k = 0; k <= n / 2 - 1; k++) {
                // index variables
                int i, j;
                // keep row index fixed
                i = k;
                // loop column index from starting position
                for (j = k; j <= n - k - 2; j++) {
                    // form 4-element groups that can be rotated independently of other matrix elements
                    // let starting element be (i,j), the rotation order should be
                    // (i,j) -> (j,n-1-i) -> (n-1-i,n-1-j) -> (n-1-j,i) -> (i,j)
                    // do three in-place swaps between elements in position (i,j) & 3 other positions sequentially
                    swap(matrix[i][j], matrix[j][n - 1 - i]);
                    swap(matrix[i][j], matrix[n - 1 - i][n - 1 - j]);
                    swap(matrix[i][j], matrix[n - 1 - j][i]);
                }
            }
        }
    }
};


void print_matrix(vector<vector<int>>& matrix) {
    for (auto row: matrix) {
        cout << '[';
        for (auto i: row) {
            cout << i << ',';
        }
        cout << "]," << endl;
    }
}

int main() {
    Solution sol;
    vector<vector<int>> matrix;
    matrix.push_back({5,1,9,11});
    matrix.push_back({2,4,8,10});
    matrix.push_back({13,3,6,7});
    matrix.push_back({15, 14, 12, 16});
    print_matrix(matrix);
    sol.rotate(matrix);
    print_matrix(matrix);
}

#endif