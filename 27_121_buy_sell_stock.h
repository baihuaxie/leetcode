#ifndef _27_121_BUY_SELL_STOCK_H_
#define _27_121_BUY_SELL_STOCK_H_
#include <iostream>
#include <vector>   //std::vector
#include <algorithm>    //std::min, std::max

using namespace std;


class Solution {
public:
    int maxProfit(const vector<int>& prices) {

        int i;
        int n = prices.size() - 1;
        // initialize value function
        int V = prices[0];
        // results
        int max_profit = 0;

        for (i = 1; i <= n; i++) {
            // update value
            V = min(prices[i], V);
            // running result
            max_profit = max(max_profit, prices[i] - V);
        }

        return max_profit;
    }
};

#endif