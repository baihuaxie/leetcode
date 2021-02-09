#ifndef _36_621_TASK_SCHEDULER_H_
#define _36_621_TASK_SCHEDULER_H_
#include <iostream>
#include <vector>   //std::vector
#include <map>      //std::map
#include <algorithm>    //std::max

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // initialize task map of task:counts
        map<char, int> tm;
        int max_count = 0;

        // get the task with max. count
        for (auto task: tasks) {
            tm[task]++;
            max_count = max(max_count, tm[task]);
        }

        // if optimal schedule contains idle unit
        // if task=A has highest count
        // schedule should look like: (A[...]*n)...(A[...]*n)A(...)
        // [...]*n means a block of n tasks;
        // provable that idle unit(s) must be in these blocks
        int units = (max_count - 1) * (n + 1);
        for (auto task: tm) {
            // if there is another task=B that has same initial count as A
            // need to schedule it after the last A
            if (task.second == max_count)
                units++;
        }

        // if optimal schedule contains no idle, units is just tasks.size()
        // return max of both scenarios as the result
        return max(units, (int)tasks.size());
    }
};

#endif
