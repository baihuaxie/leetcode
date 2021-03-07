#ifndef _43_32_LONGEST_VALID_PARENTHESE_STACK_H_
#define _43_32_LONGEST_VALID_PARENTHESE_STACK_H_
#include <iostream>
#include <stack>        //std::stack
#include <string>       //std::string
#include <vector>       //std::vector
#include <algorithm>    //std::max_element

using namespace std;

class Solution {
public:
    int longestValidParentheses_doesnt_work(string s) {

        if (s.empty())
            return 0;
        // initialize stack; stores index of "("
        stack<int> stk;

        int n = s.size();

        // initialize value functions v & p
        // v[i] = length of longest valid parenthesis in range [0:i]
        // p[i] = index of right-most ")" in the longest valid parenthesis substring of range [0:i]
        vector<int> p(n, -1), v;
        int partial = 0, running = 0;

        // first character
        if (s[0] == '(')
            stk.push(0);

        // loop from i = 1
        for (int i = 1; i < n; i++) {
            if (s[i] == '(') {
                p[i] = p[i - 1];
                stk.push(i);
            }
            else {
                if (!stk.empty()) {
                    // range [j:i] is a valid parenthese substring
                    int j = stk.top();
                    stk.pop();
                    running = i - j + 1;
                    p[i] = i;
                    if (partial == 0)
                        partial = running;
                    else if (j != 0 && p[j-1] == j-1) {
                        partial += running;
                    }
                }
                else {
                    p[i] = p[i - 1];
                    v.push_back(max(partial, running));
                    partial = 0;
                }     
            }
        }

        v.push_back(partial);
        v.push_back(running);

        return *max_element(v.cbegin(), v.cend());
    }

    int longestValidParentheses(string s) {
        /*
        the problem to the naive idea:
        - if s[i]==")", the range [j:i] can be a valid parenthesis, if s[j] is the right-most unmatched "("
        - so there is a LIFO property => use stk to store the index of right-most unmatched "(", so j = stk.top()
        - but a valid parenthesis can look like either "((()))" or "()(())"; for the 2nd case, it is difficult to add
          the two partial substrings "()" and "(())" using this formula

        the modified idea:
        - let the range [j+1:i] be a valid parenthesis; assume we have access to the index=j such that j precedes a valid parenthesis
        - now for either case, i-j would be the length of the full substring
        - the trick to achieve this is to do a stk.pop() first before doing j = stk.top()

        additional details:
        - still use a stack to store the indices j;
        - if s[j]=="(", we can do stk.push(j) the same way as before
        - if s[j]==")", i.e., the valid parenthesis is preceded by a ")" character, we also need to push j into the stack, but only if
          s[j] is the right-most unmatched ")";
          - for if s[j] can be matched, it can not be used as the separating char for subsequent valid substrings => check if stk is empty first
          - it must be the right-most one for the range [j+1:i] to be fully valid => do stk.pop() first before stk.push()

        - still uses a running max to return the longest substrings
        */
        stack<int> stk;
        stk.push(-1);
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                int j = stk.top();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    ans = max(ans, i - stk.top());
                }
            }
        }
        return ans;
    }
};

#endif