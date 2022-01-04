#ifndef _107_2048_NEXT_GREATER_NUMERICALLY_BALANCED_NUMBER_H_
#define _107_2048_NEXT_GREATER_NUMERICALLY_BALANCED_NUMBER_H_
#include <iostream>
#include <vector>       //std::vector
#include <cmath>        //std::pow

using namespace std;

class Solution {
    // a hashmap s.t. hmap[i] == number of occurrences of the digit i+1;
    int hmap[10];

public:
    int nextBeautifulNumber(int n) {

        int num_digits = getNumDigits(n);

    }

    // return the number of digits for integer n;
    int getNumDigits(int n) {
        int i = 0;
        while (1) {
            if (n / pow(10, i) == 0)
                return i;
        }
    }

    // check if current res is balanced;
    bool isBalanced(vector<int>& res) {
        for (auto digit : res) {
            if (hmap[digit-1] != digit)
                return false;
        }
        return true;
    }

    bool dfs(vector<int>& res, int& num_digits) {
        
        if (res.size() == num_digits) {
            return isBalanced(res);
        }

        // loop through the digit 1~9
        for (int i = 1; i <= 9; ++i) {
            // LIVE condition
            if (hmap[i-1] < i) {
                res.push_back(i);
                hmap[i - 1]++;
                // Terminal condition
                if (dfs(res, num_digits))
                    return true;
                // backtrack
                res.pop_back();
                hmap[i - 1]--;
            }
        }
    }
};

#endif