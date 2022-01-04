#ifndef _106_212_WORD_SEARCH_II_IMPROVED_H_
#define _106_212_WORD_SEARCH_II_IMPROVED_H_
#include <iostream>
#include <string>       //std::string
#include <vector>       //std::vector
#include <utility>      //std::pair, make_pair
#include <algorithm>    //std::find


using namespace std;

struct TrieNode {

    TrieNode *children[26];
    // word = empty for non-leaf nodes;
    string word;

    // constructor
    TrieNode(): word("") {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        vector<string> results;
        vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // build Trie from `words`;
        struct TrieNode *root = new TrieNode();
        for (auto word : words) {
            insert(root, word);
        }

        // backtrack search;
        int m = board.size();
        int n = board[0].size();
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                dfs(r, c, board, root, results, dirs);
            }
        }

        return results;
    }

    // insert a new TrieNode into the Trie if key is not present;
    void insert(TrieNode* root, string key) {
        struct TrieNode *p = root;
        for (auto c : key) {
            int index = c - 'a';
            // if p's children doesn't contain the character, insert a new TrieNode;
            if (!p->children[index])
                p->children[index] = new TrieNode();
            p = p->children[index];
        }
        // mark last node as leaf;
        p->word = key;
    }

    // backtracking routine;
    void dfs(int r, int c, vector<vector<char>>& board, TrieNode* p, vector<string>& results, vector<pair<int, int>>& dirs) {

        /*  improved backtracking + trie:
            - Trie search() method is itself a dfs on the Trie data structure, originally I used this method for the Live condition,
              then each condition check requires O(m) where m == key.length();
            - but since both backtract and the Trie are dfs on trees (backtrack on its search tree, Trie the prefix tree),
              I can descend on both trees simultaneously; this makes the Live condition check O(1); 
        */

        // check that current position on the board is valid;
        int m = board.size();
        int n = board[0].size();
        if (r < 0 || r >= m || c < 0 || c >= n)
            return;

        char t = board[r][c];

        // Live condition: current partial result is in the Trie;
        if ((t != '#') && (p->children[t - 'a'] != nullptr)) {

            // descend in Trie;
            p = p->children[t - 'a'];

            // terminal condition: current result is indeed a leaf node && is not redundant;
            if (p->word.size() > 0)  {
                results.push_back(p->word);
                // set to empty to avoid adding redundant words;
                p->word = "";
            }

            board[r][c] = '#';

            // loop four directions
            for (auto dir : dirs) {
                // expansion
                dfs(r + dir.first, c + dir.second, board, p, results, dirs);
            }

            // backtrack
            board[r][c] = t;
        }
    }
};

#endif
