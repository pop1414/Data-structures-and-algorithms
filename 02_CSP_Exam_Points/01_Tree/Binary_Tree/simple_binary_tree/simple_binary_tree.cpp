#include <iostream>
#include <queue>

using namespace std;

template <typename T>
struct TreeNode
{
    T val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
};

template <typename T>
TreeNode<T> *createNode(T val)
{
    return new TreeNode(val);
}

template <typename T>
void deleteTree(TreeNode<T> *root)
{
    if (!root)
    {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

// 前中后序遍历都算作DFS，先深入子树，再回溯
// 层序遍历算作BFS，通过队列控制层级
// DFS适用于寻找所有路径
// BFS适用于寻找最短路径
// DFS只有遍历完所有节点后，算法才会结束；而BFS在遍历到第一个叶节点时就结束算法了
template <typename T>
void preOrder(TreeNode<T> *root)
{
    if (!root)
    {
        return;
    }

    cout << root->val;

    preOrder(root->left);
    preOrder(root->right);
}

template <typename T>
void inOrder(TreeNode<T> *root)
{
    if (!root)
    {
        return;
    }

    inOrder(root->left);

    cout << root->val;

    inOrder(root->right);
}

template <typename T>
void postOrder(TreeNode<T> *root)
{
    if (!root)
    {
        return;
    }

    postOrder(root->left);
    postOrder(root->right);

    cout << root->val;
}

template <typename T>
void levelOreder(TreeNode<T> *root)
{
    if (!root)
    {
        return;
    }

    queue<TreeNode<T> *> q;
    q.push(root);

    int depth = 0;
    while (!q.empty())
    {
        int sz = q.size();
        for (int i = 0; i < sz; i++)
        {
            TreeNode<T> *cur = q.front();
            q.pop();

            cout << cur->val;

            if (cur->left)
            {
                q.push(cur->left);
            }
            if (cur->right)
            {
                q.push(cur->right);
            }
        }
        depth++;
    }
}

int main()
{

    return 0;
}