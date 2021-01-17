#ifndef _25_85_MAXIMAL_RECTANGLE_H_
#define _25_85_MAXIMAL_RECTANGLE_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::max
#include <stack>    //std::stack

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        
        if (matrix.empty())
            return 0;

        // initialize result
        int max_area = 0;

        // initialize index
        int i, j;
        int m = matrix.size() - 1;
        int n = matrix[0].size() - 1;

        // initialize 1d value funtion along column direction
        // state i = matrix[0:i][:n]
        vector<int> V(n+1, 0);

        // loop through rows
        for (i = 0; i <= m; i++) {
            // update value function
            for (j = 0; j <= n; j++) {
                if (matrix[i][j] == '0')
                    V[j] = 0;
                else
                    V[j] += 1;
            }
            // solve the max rectangle in histogram problem
            max_area = max(max_area, largestRectHisto(V));
        }
        return max_area;
    }

    int largestRectHisto(vector<int>& heights) {
        // initialize stack
        // stack elements = [heights[i], p[i]], where p[i] = left-most index
        // such that heights[p[i]] <= heights[i]
        stack<vector<int>> s;

        // initialize result
        int max_area = 0;

        // initialize loop index
        int i, n;
        n = heights.size();

        // traverse the array
        for (i = 0; i <= n - 1; i++) {
            // initialize p[i] = i
            int p = i;
            
            // otherwise, loop through the stack
            while (!s.empty()) {
                // get height & p from top of stack
                int height = s.top()[0];
                int idx = s.top()[1];

                // check push condition
                if (heights[i] > height) {
                    // push directly
                    s.push({heights[i], p});
                    // continue to next element in heights
                    break;
                }
                else if (heights[i] == height) {
                    // the rectangle for heights[i] can start with idx
                    p = idx;
                    // push directly
                    s.push({heights[i], p});
                    // continue to next element in heights
                    break;
                }
                // condition: heights[i] < height
                // in this scenario, current s.top() can no longer increase its rectangle width
                // so should pop
                else {
                    p = idx;
                    // get area for current s.top(); width = (i-1) - idx + 1 = i - idx
                    max_area = max(max_area, (i - idx) * height);
                    // pop stack
                    s.pop();
                    // continue while loop
                }
            }
            // empty stack; push directly
            if (s.empty()) {
                s.push({heights[i], p});
            }
        }
        
        // stack elements are all potential rectangles, so need to traverse stack & find max
        while (!s.empty()) {
            // update max_area; width should be (n-1) - p + 1 = n - p
            // the right-most index is now the last position in the array
            max_area = max({max_area, (n - s.top()[1]) * s.top()[0]});
            s.pop();
        }
        // return after traverse
        return max_area;
    }
};

#endif