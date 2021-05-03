#ifndef _77_133_CLONE_GRAPH_H_
#define _77_133_CLONE_GRAPH_H_
#include <iostream>
#include <vector>           //std::vector
#include <unordered_map>    //std::unordered_map
#include <queue>            //std::queue

using namespace std;

// node definition;
class Node {
public:
    int val = 0;
    vector<Node *> neighbors = vector<Node *>();

    Node() = default;
    Node(int _val) : val(_val), neighbors(vector<Node *>()){};
    Node(int _val, vector<Node *> _neighbors) : val(_val), neighbors(_neighbors){};
};

class Solution {
    // hash-table to store copied nodes;
    unordered_map<Node *, Node *> copied;

public:
    // dfs solution;
    Node* cloneGraph(Node* node) {
        // returns a deep-copy of the sub-graph starting from node=node;

        if (node == nullptr) {
            return NULL;
        }
        // if node has not been visited yet, traverse from node; else do nothing;
        if (copied.find(node) == copied.end()) {
            // copy node;
            copied[node] = new Node(node->val, {});
            // dfs visit neighbors;
            for (auto neighbor : node->neighbors)
                copied[node]->neighbors.push_back(cloneGraph(neighbor));
        }
        // return copied[node] at top-level as the reference to the deep-copied graph;
        return copied[node];
    }

    // bfs solution;
    Node* bfs_cloneGraph(Node* node) {
        // returns a deep-copy of the sub-graph starting from node; use bfs;

        // bfs queue; assume all nodes in queue has been visited -> only process their neighbors;
        queue<Node *> q;

        if (node == nullptr)
            return NULL;
        else {
            copied[node] = new Node(node->val, {});
        }

        q.push(node);

        while (!q.empty()) {
            Node *p = q.front();
            q.pop();

            // visit neighbors of p;
            for (auto n : p->neighbors) {
                // check if n has been visited; if not copy n;
                if (copied.find(n) == copied.end()) {
                    // copy node n;
                    copied[n] = new Node(n->val, {});
                    // add n to the bfs queue;
                    q.push(n);
                }
                // copy edge; note this is done regardless of whether n has been visited;
                copied[p]->neighbors.push_back(copied[n]);
            }
        }

        return copied[node];
    }
};


#endif
