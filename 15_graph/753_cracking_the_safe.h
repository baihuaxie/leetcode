#ifndef _96_753_CRACKING_THE_SAFE_H_
#define _96_753_CRACKING_THE_SAFE_H_
#include <algorithm> //std::reverse;
#include <iostream>
#include <map>     //std::map
#include <numeric> //std::iota
#include <string>  //std::string
#include <vector>  //std::vector

using namespace std;

class Solution {
public:
    string crackSafe(int n, int k) {
        // there are k^n combinations; we want to find a string with min. length that contains all combinations;
        // obviously the trick is to re-use common substrings between two combinations;

        // construct a graph of node # = k^{n-1} and each node has k out-going, directed edges;
        // each node represents a sub-string of length=n-1;
        // each edge is associated with a digit in range [0, k-1] so there are k edges for each node;
        // define a transformation t: pad a digit to the last position of the current node string, shift it
        // by one position to the left;
        // e.g., current node = 001, pad a digit=1 to the last position, becomes 0011; shift left would result in 011;
        // we say there is an edge from node u=001 to node v=011 with egde value e=1 since there exists such a transformation
        // t(u->v, e);
        // so the graph consists of k^{n-1} such nodes with each node having k outgoing edges to k neighbors that it can be
        // transformed into; there are a total of k^n edges;

        // such a graph must always contain an Eulerian circuit: each node must have k out-going edges b/c there are k digits to
        // pad to the last position; each node must also have k in-coming edges b/c there are also k digits to be shifted out in
        // the first position; thus the indegree==outdegree holds true for all nodes in the directed graph;

        // the problem is now to find an Eulerian path in this graph;
        // pick any node as the start node and set string=start; for each edge visited, pad its value to the string;
        // e.g. if n=3, k=2, start=00 and I visit two edges = 1, 0, after visits string=0010 which now contains
        // two combinations: 001 and 010;
        // so if all edges have been visited exactly once, we would obtain a string that contains all possible k^n combinations with
        // each combination appearing exactly once, this would be the minimum length string, with length = n-1+k^n;

        // graph[u] = {e, v} where e is edge value, v is the node that u can be transformed into via this edge value;
        map<string, vector<vector<string>>> graph;

        // get a vector of digits string {"0", "1", ..., "k-1"}
        vector<int> numbers(k);
        iota(numbers.begin(), numbers.end(), 0);
        vector<string> digits;
        for (auto d : numbers) {
            digits.push_back(to_string(d));
        }

        // obtain all combinations of length=n-1 from k digits as nodes in the graph;
        vector<string> nodes;
        string vec;
        combinations(nodes, vec, digits, n - 1);

        // build graph;
        for (auto u : nodes) {
            for (auto digit : digits) {
                string v = u + digit;
                graph[u].push_back({digit, v.substr(1, n - 1)});
            }
        }

        // pick start node;
        string start (n-1, '0');
        string sequence = start;
        string edges;

        // use Hierholzer's algorithm to find an Eulerian path;
        dfsEulerianPath(graph, "", start, edges);
        reverse(edges.begin(), edges.end());
        sequence += edges;

        return sequence;
    }

    void combinations(vector<string> &results, string& v, vector<string>& digits, int depth) {
        // returns all possible combinations using digits in range [0,k-1] with length=n-1;
        if (depth > 0) {
            for (auto digit: digits) {
                v += digit;
                combinations(results, v, digits, --depth);
                v.pop_back();
                depth++;
            }
        }
        else {
            results.push_back(v);
        }
    }

    void dfsEulerianPath(map<string, vector<vector<string>>>& graph, string e, string u, string& edges) {
        while (!graph[u].empty()) {
            vector<string> v = graph[u].back();
            graph[u].pop_back();
            dfsEulerianPath(graph, v[0], v[1], edges);
        }
        // Hierholzer's: add edge when backtrack from dfs (outdegree==0)
        edges += e;
    }
};


#endif