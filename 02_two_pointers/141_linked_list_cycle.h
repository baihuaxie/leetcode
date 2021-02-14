#ifndef _39_141_LINKED_LIST_CYCLE_H_
#define _39_141_LINKED_LIST_CYCLE_H_
#include <iostream>

using namespace std;

struct ListNode {
    // members
    int val = 0;
    ListNode *next = nullptr;
    // constructors
    ListNode() = default;
    ListNode(int x) : val(x), next(nullptr){};
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        // initialize two pointers
        ListNode *ptr1 = head, *ptr2 = head;

        // loop & move ptr2 at 2x pace of ptr1
        while (ptr2 != nullptr && ptr2->next != nullptr) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next->next;
            if (ptr1 == ptr2)
                return true;
        }
        return false;
    }
};

#endif
