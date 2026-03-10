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