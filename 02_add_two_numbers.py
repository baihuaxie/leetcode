'''
    problem statement:

    You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

    You may assume the two numbers do not contain any leading zero, except the number 0 itself.
'''


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

'''
    for singlely linked list based problems, always create:
        a) a ListNode class, containing two data fields: value and next pointer; plus the default constructor
        b) a SLinkedList class, containing one data field: the header
        -  add methods like addLast, addFirst, printList, etc.
        -  in these methods, should always operate on ListNode objects
    in test:
        -  always initialize a SLinkedList object, then use add methods to add nodes to construct a linked list
'''

class SLinkedList:
    '''
        singlely linked list.
    '''
    def __init__(self, header=None):
        self.header = header

    ''' insert a new node as header node '''
    def addFirst(self, newdata):
        newNode = ListNode(newdata)
        newNode.next = self.header
        self.header = newNode
        return

    ''' insert a new node at tail '''
    def addLast(self, newdata):
        newNode = ListNode(newdata)
        if self.header is None:
            self.header = newNode
            return
        ptr = self.header
        while ptr.next is not None:
            ptr = ptr.next
        ptr.next = newNode
        return

    ''' print list '''
    def printList(self):
        print_ptr = self.header
        while (print_ptr is not None):
            print(print_ptr.val)
            print_ptr = print_ptr.next

class Solution:
    '''
        here in 1st submission, didn't add the carry after while() loop for carry=1 cases; 
        this would result in errors like input(L1=5,L2=5), output (0), instead of the correct answer (0,1)
    '''
    def addTwoNumbers(self, L1: ListNode, L2: ListNode) -> ListNode:
        res = SLinkedList()
        carry = 0
        while (L1 is not None or L2 is not None):
            if (L1 is None):
                value = L2.val + carry
                L2 = L2.next
            elif (L2 is None):
                value = L1.val + carry
                L1 = L1.next
            else:
                value = L1.val + L2.val + carry
                L1 = L1.next
                L2 = L2.next
            res.addLast(value % 10)
            carry = value // 10
        if carry == 1:
            res.addLast(carry)
        return res.header


if __name__ == "__main__":
    List1 = SLinkedList()
    #List1.addFirst(3)
    #List1.addFirst(4)
    List1.addFirst(5)
    L1 = List1.header
    List2 = SLinkedList()
    #List2.addFirst(4)
    #List2.addFirst(6)
    #List2.addFirst(5)
    #List2.addFirst(9)
    List2.addFirst(5)
    L2 = List2.header
    sol = Solution()
    sol = sol.addTwoNumbers(L1, L2)
    sol = SLinkedList(sol)
    print(sol.printList())
