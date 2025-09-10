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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *first = head;
        ListNode *second = head;
        for (int i = 0; i < n; i++)
        {
            first = first->next;
        }

        if (first == nullptr) // 如果first先移动后，变为null，说明删除的是头节点
        {
            return head->next;
        }

        ListNode *pre = nullptr;
        while (first != nullptr)
        {
            first = first->next;
            if (first == nullptr)
            {
                pre = second;
            }
            second = second->next;
        }

        pre->next = second->next;

        return head;
    }
};

// ===== 工具函数 =====

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
    cout << "[";
    while (head)
    {
        cout << head->val;
        head = head->next;
        if (head)
            cout << ",";
    }
    cout << "]" << endl;
}

int main()
{
    Solution sol;

    // 样例1
    ListNode *head1 = buildList({1, 2, 3, 4, 5});
    cout << "Original: ";
    printList(head1);
    ListNode *res1 = sol.removeNthFromEnd(head1, 2);
    cout << "After removing 2nd from end: ";
    printList(res1);
    cout << "Expected: [1,2,3,5]\n\n";

    // 样例2
    ListNode *head2 = buildList({1});
    cout << "Original: ";
    printList(head2);
    ListNode *res2 = sol.removeNthFromEnd(head2, 1);
    cout << "After removing 1st from end: ";
    printList(res2);
    cout << "Expected: []\n\n";

    // 样例3
    ListNode *head3 = buildList({1, 2});
    cout << "Original: ";
    printList(head3);
    ListNode *res3 = sol.removeNthFromEnd(head3, 2);
    cout << "After removing 2nd from end: ";
    printList(res3);
    cout << "Expected: [2]\n";

    return 0;
}