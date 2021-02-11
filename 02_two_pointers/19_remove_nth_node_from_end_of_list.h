#ifndef _37_19_REMOVE_NTH_NODE_FROM_END_OF_LIST_H_
#define _37_19_REMOVE_NTH_NODE_FROM_END_OF_LIST_H_
#include <iostream>

using namespace std;

struct ListNode {
    // constructors
    ListNode() = default;
    ListNode(int x) : val(x), next(nullptr){};
    ListNode(int x, ListNode *next) : val(x), next(next){};
    // members
    int val = 0;
    ListNode *next = nullptr;
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // initialize two pointers
        ListNode *ptr1 = head;
        ListNode *ptr2 = head;

        int delayed = 0;

        // loop
        while (ptr2->next != nullptr) {
            ptr2 = ptr2->next;
            delayed++;
            // delay moving ptr1 by n steps
            if (delayed <= n)
                continue;
            ptr1 = ptr1->next;
        }

        // remove node pointed to by ptr1->next
        // 1) ptr1 is last node; this is only possible when there is only one node in the list
        if (ptr1->next == nullptr) {
            head = nullptr;
        }
        // 2) ptr1 is first node & needs to remove it
        else if (delayed < n)
            head = head->next;
        // 3) other cases; remove nth node pointed to by ptr1->next
        else
            ptr1->next = ptr1->next->next;
        return head;
    }
};


#endif