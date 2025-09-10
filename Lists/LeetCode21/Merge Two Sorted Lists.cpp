#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *head1 = list1;
        ListNode *head2 = list2;

        ListNode *resHead = new ListNode();
        ListNode *temp = resHead;
        while (head1 != nullptr && head2 != nullptr)
        {
            if (head1->val < head2->val)
            {
                temp->next = new ListNode(head1->val);
                temp = temp->next;
                head1 = head1->next;
            }
            else
            {
                temp->next = new ListNode(head2->val);
                temp->next = new ListNode(head2->val);
                temp = temp->next;
                head2 = head2->next;
            }
        }

        if (head1 == nullptr)
        {
            temp->next = head2;
        }
        else
        {
            temp->next = head1;
        }

        return resHead->next;
    }
};