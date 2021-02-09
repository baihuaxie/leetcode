#ifndef _24_84_LARGEST_RECTANGLE_IN_HISTOGRAM_H_
#define _24_84_LARGEST_RECTANGLE_IN_HISTOGRAM_H_
#include <iostream>
#include <vector>   //std::vector
#include <stack>    //std::stack
#include <algorithm>    //std::max

using namespace std;

class Solution {
public:
    int largestRectangleArea(const vector<int>& heights) {
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