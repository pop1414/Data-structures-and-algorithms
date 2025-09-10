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
    ListNode *partition(ListNode *head, int x)
    {
        ListNode *slow = new ListNode(0);
        ListNode *tempSlow = slow;
        ListNode *fast = head;

        ListNode *bigger = new ListNode(0);
        ListNode *tempBigger = bigger;
        while (fast != nullptr)
        {
            int curVal = fast->val;
            if (curVal < x)
            {
                tempSlow->next = new ListNode(curVal);
                tempSlow = tempSlow->next;
            }
            else
            {
                tempBigger->next = new ListNode(curVal);
                tempBigger = tempBigger->next;
            }
            fast = fast->next;
        }
        tempSlow->next = bigger->next;
        return slow->next;
    }
};

// == == = 工具函数 == == =

// 从 vector 构造链表
ListNode *buildList(const vector<int> &vals)
{
    ListNode dummy;
    ListNode *cur = &dummy;
    for (int v : vals)
    {
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return dummy.next;
}

// 打印链表
void printList(ListNode *head)
{
    while (head)
    {
        cout << head->val;
        if (head->next)
            cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    Solution sol;

    // 样例1
    vector<int> vals1 = {1, 4, 3, 2, 5, 2};
    ListNode *head1 = buildList(vals1);
    cout << "Original: ";
    printList(head1);
    ListNode *res1 = sol.partition(head1, 3);
    cout << "Partitioned (x=3): ";
    printList(res1);
    cout << "Expected: 1 -> 2 -> 2 -> 4 -> 3 -> 5" << endl
         << endl;

    // 样例2
    vector<int> vals2 = {2, 1};
    ListNode *head2 = buildList(vals2);
    cout << "Original: ";
    printList(head2);
    ListNode *res2 = sol.partition(head2, 2);
    cout << "Partitioned (x=2): ";
    printList(res2);
    cout << "Expected: 1 -> 2" << endl;

    return 0;
}