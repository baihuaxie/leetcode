#ifndef _41_234_PALINDROME_LINKED_LIST_H_
#define _41_234_PALINDROME_LINKED_LIST_H_
#include <iostream>

struct ListNode {
    // members
    int val = 0;
    ListNode *next = nullptr;
    // constructors
    ListNode() = default;
    ListNode(int x) : val(x), next(nullptr){};
    ListNode(int x, ListNode *next) : val(x), next(next){};
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // step-1): find middle node
        ListNode *ptr1 = head;
        int counter = 0;
        
        if (head == nullptr)
            return true;

        while (ptr1->next != nullptr) {
            ptr1 = ptr1->next;
            counter++;
        }

        int m = (counter + 1) / 2;

        ptr1 = head;
        while (m > 0) {
            ptr1 = ptr1->next;
            m--;
        }

        // step-2): reverse 2nd half of linked list from the middle node
        ListNode *ptr2;
        ptr2 = ptr1->next;
        ListNode *ptr3;
        ptr1->next = nullptr;
        // after loop, ptr1 points to new head
        while (ptr2 != nullptr) {
            ptr3 = ptr2->next;
            ptr2->next = ptr1;
            ptr1 = ptr2;
            ptr2 = ptr3;
        }

        // step-3): compare corresponding nodal values
        while (ptr1 != nullptr) {
            if (head->val != ptr1->val)
                return false;
            head = head->next;
            ptr1 = ptr1->next;
        }
        return true;
    }
};


#endif