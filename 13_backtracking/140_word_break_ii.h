#ifndef _105_140_WORD_BREAK_II_H_
#define _105_140_WORD_BREAK_II_H_
#include <iostream>
#include <string>       //std::string
#include <vector>       //std::vector
#include <algorithm>    //std::find

using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {

        string v;
        vector<string> res;

        dfs(s, wordDict, v, res);
        return res;
    }

    void dfs(string& s, vector<string>& wordDict, string& v, vector<string>& res) {
        int sz = s.size();
        int n = v.size();
        for (int i = 1; i <= sz; ++i) {
            string lhs = s.substr(0, i);
            // LIVE condition
            if (find(wordDict.begin(), wordDict.end(), lhs) != wordDict.end()) {
                lhs.push_back(' ');
                v.insert(n, lhs);
                // Terminal condition
                if (i == sz) {
                    // remove last empty space
                    v.pop_back();
                    res.push_back(v);
                }
                else {
                    // expansion
                    string rhs = s.substr(i, sz - i);
                    dfs(rhs, wordDict, v, res);
                }
                // backtrack
                v.erase(n);
            }
        }
    }
};

#endif