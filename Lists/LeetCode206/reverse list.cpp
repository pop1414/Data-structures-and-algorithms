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
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr) // 找到最后一个不为null的节点
        {
            return head;
        }
        ListNode *last = reverseList(head->next); // 让其作为last
        head->next->next = head;                  // head->next为原链表的下一个节点，->next=head意味着多加了一个反向链接
        head->next = nullptr;                     // 断开原链表的链接
        return last;
    }
};

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

// 测试
int main()
{
    // 创建链表 1 -> 2 -> 3 -> 4 -> 5
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "原链表: ";
    printList(head);

    Solution sol;
    ListNode *reversed = sol.reverseList(head);

    cout << "反转后链表: ";
    printList(reversed);

    return 0;
}