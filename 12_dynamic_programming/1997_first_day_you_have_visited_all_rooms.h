#ifndef _110_1997_FIRST_DAY_YOU_HAVE_VISITED_ALL_ROOMS_H_
#define _110_1997_FIRST_DAY_YOU_HAVE_VISITED_ALL_ROOMS_H_
#include <iostream>
#include <vector>       //std::vector
#include <math.h>         //std::pow

using namespace std;

class Solution {
public:
    int firstDayBeenInAllRooms_2d(vector<int>& nextVisit) {

        // let dp[i][j] = number of days needed from room i to room j, with i<=j;
        // it can be shown that such a number is a fixed one, since if I'm at any
        // given room t, all rooms preceding it must have been visited even number
        // of times, so the starting conditions would always be identical thus
        // resulting in identical sequence of room visits;
        // returns dp[0][n-1] as the answer;
        int n = nextVisit.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        dp[0][0] = 1;

        // update rule
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i <=j; ++i) {
                // to go to room j consists of the following steps:
                // 1) go to room j-1 -> takes dp[i][j-1] days;
                // 2) from room j-1 go to nextVisit[j-1] -> add 1 day if j-1 != nextVisit[j-1] else no add;
                // 3) from room nextVisit[j-1] go back to room j-1 again -> dp[nextVisit[j-1]][j-1];
                // 4) now I have visited room j-1 even number of times, so go to room j -> add 1 day;

                if (i == j)
                    dp[i][j] = dp[nextVisit[j]][j] + 1; 
                else if (i == j-1)
                    dp[i][j] = dp[i][j - 1] + 1;
                else if (nextVisit[j-1] == j-1)
                    dp[i][j] = dp[i][j - 1] + dp[nextVisit[j - 1]][j - 1] + 1;
                else
                    dp[i][j] = dp[i][j - 1] + 1 + dp[nextVisit[j - 1]][j - 1] + 1;    
            }
        }

        return dp[0][n - 1] % (int(pow(10, 9)) + 7);
    }

    int firstDayBeenInAllRooms(vector<int>& nextVisit) {

        // let dp[i][j] = number of days needed from room i to room j, with i<=j;
        // it can be shown that such a number is a fixed one, since if I'm at any
        // given room t, all rooms preceding it must have been visited even number
        // of times, so the starting conditions would always be identical thus
        // resulting in identical sequence of room visits;
        // returns dp[0][n-1] as the answer;
        int n = nextVisit.size();
        vector<int> dp(n, 0);

        dp[0] = 0;

        // update rule
        for (int i = 1; i < n; ++i) {
            dp[i] = (2 * dp[i - 1] - dp[nextVisit[i - 1]] + 2) % (int(pow(10, 9)) + 7);
        }

        return dp[n - 1];
    }
};


#endif