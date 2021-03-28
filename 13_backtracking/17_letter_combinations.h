#ifndef _57_17_LETTER_COMBINATIONS_H_
#define _57_17_LETTER_COMBINATIONS_H_
#include <iostream>
#include <string>           //std::string
#include <map>              //std::map
#include <vector>           //std::vector
#include <utility>          //std::pair

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // use a map to store digit-letter correspondence
        map<char, string> dict;
        dict.insert(pair<char, string>('2', "abc"));
        dict.insert(pair<char, string>('3', "def"));
        dict.insert(pair<char, string>('4', "ghi"));
        dict.insert(pair<char, string>('5', "jkl"));
        dict.insert(pair<char, string>('6', "mno"));
        dict.insert(pair<char, string>('7', "pqrs"));
        dict.insert(pair<char, string>('8', "tuv"));
        dict.insert(pair<char, string>('9', "wxzy"));

        // initialize results
        vector<string> res;
        string v;

        // initialize root node
        string::const_iterator root = digits.cbegin();

        // backtracking
        dfs(root, digits, dict, res, v);

        return res;
    }

    void dfs(string::const_iterator ptr, string& digits, map<char, string>& dict, vector<string>& res, string& v) {

        // loop through child nodes
        for (auto n : dict[*ptr]) {
            // all nodes are initialized to be live
            v.push_back(n);
            
            // bounding condition
            if (ptr != digits.cend() - 1) {
                // expansion node, call search
                dfs(ptr + 1, digits, dict, res, v);
            }
            else {
                // n is dead node
                res.push_back(v);
                v.pop_back();
            }
        }
        // *ptr is now dead, so need to pop;
        v.pop_back();
    }
};

#endif