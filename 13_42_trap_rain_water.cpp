#ifndef TRAP_RAIN_WATER
#define TRAP_RAIN_WATER
#include <iostream>
#include <vector>   //std::vector
#include <stack>    //std::stack
#include <algorithm>    // std::min

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        // initialize stack
        stack<int> s;
        // initialize result
        int volume = 0;
        int ptr;
        int n = height.size();
        // main loop
        for (ptr = 0; ptr < n; ptr ++) {
            // empty stack
            if (s.empty())
                s.push(height[ptr]);

            else {
                // push into stack
                if (height[ptr] <= s.top())
                    s.push(height[ptr]);
                // a convex structure is found, compute volumes & modify stack
                else {
                    // initialize sum & width
                    int sum = 0;
                    int width = 0;
                    int wall;
                    // loop for a left wall
                    while (!s.empty()) {
                        if (height[ptr] >= s.top()) {
                            // pop left-side wall from stack
                            wall = s.top();
                            // increment sum
                            sum += wall;
                            // increment width
                            width += 1;
                            // pop stack
                            s.pop();
                        }
                        else {
                            wall = height[ptr];
                            break;
                        }
                    }
                    // set wall; no need to distinguish whether stack is empty
                    wall = min(wall, height[ptr]);
                    // update volume
                    volume += wall * width - sum;
                    // fill up the volume if stack is not empty
                    if (!s.empty()) {
                        int i;
                        for (i = 1; i <= width; i++)
                            s.push(wall);
                    }
                    // push
                    s.push(height[ptr]);
                }
            }
        }
        // return
        return volume;
    }
};


int main() {
    Solution sol;
    vector<int> height = {4,2,3};
    int volume = sol.trap(height);
    cout << volume << endl;
}

#endif