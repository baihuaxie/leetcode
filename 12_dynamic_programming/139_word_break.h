#ifndef _45_139_WORD_BREAK_H_
#define _45_139_WORD_BREAK_H_
#include <iostream>
#include <vector>           //std::vector
#include <unordered_set>    //std::unordered_set
#include <string>           //std::string

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // dp[i] == true if substring s[0:i+1] (excluding) is valid
        int n = s.size();
        vector<bool> dp(n, false);

        // put wordDict elements into set for constant time access
        unordered_set<string> words;
        for (auto s : wordDict) {
            words.insert(s);
        }

        // loop
        for (int i = 0; i < n; i++) {
            // if s[0:i+1] is in wordDict
            if (words.count(s.substr(0, i+1)) != 0) {
                dp[i] = true;
            }
            else {
                for (int j = i - 1; j >= 0; j--) {
                    // check only when s[0:j+1] is valid
                    if (dp[j]) {
                        if (words.count(s.substr(j+1, i - j)) != 0){
                            dp[i] = true;
                            break;
                        }
                    }
                }
            }
        }

        return dp[n - 1];
    }
};

#endif