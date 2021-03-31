#ifndef _58_22_GENERATE_PARENTHESES_H_
#define _58_22_GENERATE_PARENTHESES_H_
#include <iostream>
#include <string>       //std::string
#include <vector>       //std::vector
#include <map>          //std::map

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {

        // initialize hash map for parentheses counts
        map<char, int> mp;
        for (auto node : {'(', ')'})
            mp[node] = n;

        // initialize returns
        vector<string> results;
        string v;

        // call dfs search from root
        dfs(v, results, mp, '(');

        return results;
    }

    void dfs(string& v, vector<string>& results, map<char, int>& mp, char parent_node) {

        // binary search tree
        for (auto node : {'(', ')'}) {
            // bounding condition
            if (mp['('] == mp[')'] && node == ')')
                continue;
            else {
                // live node
                if (mp[node] > 0) {
                    v.push_back(node);
                    mp[node]--;
                }
                else
                    continue;
                // bounding condition for last node
                if (mp['('] == 0 && mp[')'] == 0) {
                    results.push_back(v);
                    v.pop_back();
                    mp[node]++;
                }
                else {
                    // expansion node
                    dfs(v, results, mp, node);
                }
            }
        }
        v.pop_back();
        mp[parent_node]++;
    }
};

#endif