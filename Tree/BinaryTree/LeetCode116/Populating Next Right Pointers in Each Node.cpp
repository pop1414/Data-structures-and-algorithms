#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    Node *connect(Node *root)
    {
        if (!root)
        {
            return root;
        }
        levelOrder(root);
        return root;
    }
    void levelOrder(Node *root)
    {
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int sz = q.size();

            for (int i = 0; i < sz; i++)
            {
                Node *cur = q.front();
                q.pop();
                if (i == sz - 1)
                {
                    cur->next = NULL;
                }
                else
                {
                    cur->next = q.front();
                }

                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
        }
    }
};

// 打印每一层的 next 链表
void printNextPointers(Node *root)
{
    Node *leftMost = root;
    while (leftMost)
    {
        Node *cur = leftMost;
        while (cur)
        {
            cout << cur->val << " -> ";
            if (cur->next)
                cout << cur->next->val << "   ";
            else
                cout << "NULL   ";
            cur = cur->next;
        }
        cout << endl;
        leftMost = leftMost->left; // 下一层最左节点
    }
}

int main()
{
    // 构造一棵完全二叉树
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution sol;
    root = sol.connect(root);

    // 打印每一层的 next 指针
    printNextPointers(root);

    return 0;
}