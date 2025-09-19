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
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.empty())
        {
            return nullptr;
        }
        int n = lists.size();
        return mergeKLists3(lists, n, 0, n - 1);
    }

    ListNode *mergeKLists3(vector<ListNode *> &lists, int n, int left, int right)
    {
        if (left > right)
        {
            return nullptr;
        }
        if (left == right)
        {
            return lists[left];
        }
        int mid = left + (right - left) / 2;

        // 通过分治，此处是二分，将递归树高度降低
        ListNode *l1 = mergeKLists3(lists, n, left, mid);
        ListNode *l2 = mergeKLists3(lists, n, mid + 1, right);

        // 不断把左右两边的链表两两合并，往中间靠
        ListNode *l0 = merge(l1, l2);

        return l0;
    }

    ListNode *merge(ListNode *l1, ListNode *l2)
    {
        ListNode *head1 = l1;
        ListNode *head2 = l2;

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