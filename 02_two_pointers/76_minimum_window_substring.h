#ifndef _38_76_MINIMUM_WINDOW_SUBSTRING_H_
#define _38_76_MINIMUM_WINDOW_SUBSTRING_H_
#include <iostream>
#include <string>           //std::string
#include <unordered_set>    //std::unordered_multiset
#include <vector>           //std::vector

using namespace std;

class Solution {
public:
    string minWindow_ver1(string s, string t) {
        // put t into unordered_multiset for constant time access & insertion
        unordered_multiset<char> tset;
        for (auto c : t) {
            tset.insert(c);
        }
        int t_size = tset.size();

        // window: stores valid chars in [left,right) that do not exceed counts in tset
        // bypassed: stores valid chars in [left, right) that exceeded counts
        // e.g., AABBCC, tset=AABC => window = AABC, bypassed=BC
        unordered_multiset<char> window, bypassed;
        int window_size = 0;

        // initialize results; length = window length
        string::const_iterator result_left, result_right;
        int length = 0;

        // initialize two pointers to point to first valid character; window is [left, right);
        string::const_iterator left = s.cbegin(), right = s.cbegin();

        // loop until can no longer ready the window by expansion
        while (right < s.cend() || window_size >= t_size)
        {
            // expansion loop
            while (right < s.cend() && window_size < t_size)
            {
                // *right is a valid char -> put into window
                if (tset.count(*right) > window.count(*right)) {
                    window.insert(*right);
                    window_size++;
                }
                else {
                    // *right is valid char but exceeded count -> put into bypassed
                    if (tset.find(*right) != tset.end())
                        bypassed.insert(*right);
                }
                // expand window
                right++;
            }

            // check if window is ready (contains all valid chars)
            if (window_size == t_size && window.find(*left) != window.end()) {
                // update results
                if (length == 0 || right - left < length) {
                    result_left = left;
                    result_right = right;
                    length = right - left;
                }
                // in ready state always contract window to continue search
                if (bypassed.find(*left) != bypassed.end())
                    // move *left from bypassed to window (no change to window), then erase
                    bypassed.erase(bypassed.find(*left));
                else {
                    window.erase(window.find(*left));
                    window_size--;
                }
                left++;
            }

            // contraction
            while (tset.find(*left) == tset.end() && left <= right) 
                left++;
        }

        if (length == 0)
            return "";
        // if a valid substr is found; return string(left,right) returns range of [left, right)
        else {
            string substring (result_left, result_right);
            return substring;
        }
    }

    string minWindow(string s, string t) {
        // initialize hash map; 128 = ASCII encoded characters
        // hashmap[c] = # of required c - # of c in present window
        // vector<int> is much faster than unordered_multiset<char>
        vector<int> hashmap(128, 0);
        for (auto c:t)
            hashmap[c]++;

        // initialize two pointers; present window = [left, right)
        string::const_iterator left = s.cbegin(), right = s.cbegin();

        // intialize pointer to the result & length; result = [head, right)
        string::const_iterator head, tail;
        int length = s.size() + 1;

        // initialize counter; if counter==0 means present window contains all char's in t
        int counter = t.size();

        // expansion loop
        while (right < s.cend()) {
            
            if (hashmap[*right] > 0) {
                // only update counter if *right is not redundant
                counter--;
            }
            // move expansion pointer
            hashmap[*right]--;
            right++;

            // contraction loop
            while (counter == 0) {
                // update results
                if (right - left < length) {
                    head = left;
                    tail = right;
                    length = tail - head;
                }

                if (hashmap[*left] == 0) {
                    // contract window if *left no longer has enough counts
                    counter++;
                }
                // move contraction pointer
                hashmap[*left]++;
                left++;
            }
        }
        string substring (head, tail);
        return length == static_cast<int>(s.size() + 1) ? "" : substring;
    }

};

#endif