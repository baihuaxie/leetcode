#ifndef _106_212_WORD_SEARCH_II_H_
#define _106_212_WORD_SEARCH_II_H_
#include <iostream>
#include <string>       //std::string
#include <vector>       //std::vector
#include <utility>      //std::pair, make_pair
#include <algorithm>    //std::find


using namespace std;

struct TrieNode {
    /*
    in the Trie, a parent-child link is like e.g. "te" (u) -> "tea" (v); 
    - we need to have u->children['a'] = v
    - in a Trie any string like "te" or "tea" is never explicitly stored as nodal values/keys;
      instead the Trie just models the prefix relations b/t keys; to get the full key one would
      need to traverse to a leaf node;
    */
    struct TrieNode *children[26];
    bool isLeaf;
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        string s;
        vector<string> results;
        vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // build Trie from `words`;
        struct TrieNode *root = newNode();
        for (auto word : words) {
            insert(root, word);
        }

        // backtrack search;
        int m = board.size();
        int n = board[0].size();
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                dfs(r, c, board, root, s, results, dirs);
            }
        }

        return results;
    }

    // return a new TrieNode initialized to no children;
    struct TrieNode* newNode() {
        struct TrieNode *p = new TrieNode;
        for (int i = 0; i < 26; ++i) {
            p->children[i] = nullptr;
        }
        p->isLeaf = false;
        return p;
    }

    // insert a new TrieNode into the Trie if key is not present;
    void insert(TrieNode* root, string key) {
        struct TrieNode *p = root;
        for (auto c : key) {
            int index = c - 'a';
            // if p's children doesn't contain the character, insert a new TrieNode;
            if (!p->children[index])
                p->children[index] = newNode();
            p = p->children[index];
        }
        // mark last node as leaf;
        p->isLeaf = true;
    }

    // return true if a key (not necessarily leaf) is found in the Trie;
    bool search(TrieNode* root, string key) {
        struct TrieNode *p = root;
        for (auto c : key) {
            int index = c - 'a';
            if (!p->children[index])
                return false;
            p = p->children[index];
        }
        return true;
    }

    // return true if a key is a leaf node in the Trie;
    bool isWord(TrieNode* root, string key) {
        struct TrieNode *p = root;
        for (auto c : key) {
            int index = c - 'a';
            if (!p->children[index])
                return false;
            p = p->children[index];
        }
        return p->isLeaf;
    }

    // backtracking routine;
    void dfs(int r, int c, vector<vector<char>>& board, TrieNode* root, string& s, vector<string>& results,
             vector<pair<int, int>>& dirs) {

        // check that current position on the board is valid;
        int m = board.size();
        int n = board[0].size();
        if (r < 0 || r >= m || c < 0 || c >= n)
            return;
        char t = board[r][c];
        // check if current position has already been visited in current branch;
        if (t == '#')
            return;
        string tmp_s = s;
        tmp_s.push_back(t);

        // Live condition: current partial result is in the Trie;
        if (search(root, tmp_s)) {
            s.push_back(t);
            board[r][c] = '#';
            // terminal condition: current partial result is indeed a leaf node;
            if (isWord(root, s))  {
                // do not push redundant results;
                if (find(results.begin(), results.end(), s) == results.end())
                    results.push_back(s);
            }
            // loop four directions
            for (auto dir : dirs) {
                // expansion
                dfs(r + dir.first, c + dir.second, board, root, s, results, dirs);
            }
            // backtrack
            s.pop_back();
            board[r][c] = t;
        }
    }
};

#endif
