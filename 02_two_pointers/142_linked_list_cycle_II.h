#ifndef _40_142_LINKED_LIST_CYCLE_II_H_
#define _40_142_LINKED_LIST_CYCLE_II_H_
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
    ListNode *detectCycle(ListNode *head) {

        /*
        concept:
        let T0 be starting node of cycle & T1 be the node where ptr1 first meets ptr2
        let L be length of the cycle; we have
            2*(T1-T0) + (T0 mod L) = (T1-T0) + L
        or that T0 = (n+1)*L - (T1-T0), where n is a non-negative integer (can just be 1)
        the R.H.S. means that if a pointer starts from T1 at pace=1, it would return to the 
        starting node T0 after T0 steps -> use another pointer ptr3 to step from head T0 steps,
        then these two pointers must meet at T0
        */

        // initialize two pointers
        ListNode *ptr1 = head, *ptr2 = head, *ptr3=head;

        // loop; terminate if there is no cycle
        while (ptr2 != nullptr && ptr2->next != nullptr) {
            // move ptr1 at pace=1 & ptr2 at pace=2
            ptr1 = ptr1->next;
            ptr2 = ptr2->next->next;
            // position T1: when ptr1 first meets ptr2
            if (ptr1 == ptr2) {
                // start moving ptr3 from head at pace=1
                while (ptr1 != ptr3) {
                    ptr1 = ptr1->next;
                    ptr3 = ptr3->next;
                }
                return ptr1;
            }
        }
        return nullptr;
    }
};

#endif