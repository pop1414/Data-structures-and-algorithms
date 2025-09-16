#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    void flatten(TreeNode *root)
    {

        if (!root)
        {
            return;
        }

        // 操作叶节点是多余的
        if (!root->left && !root->right)
        {
            return;
        }

        flatten(root->left);
        flatten(root->right);

        // 左节点不存在时不用操作
        if (root->left)
        {
            TreeNode *temp = root->left;
            // 找到左子树链最后的节点
            while (temp->right)
            {
                temp = temp->right;
            }
            // 把右子树接上去
            temp->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
    }
};

int main()
{

    return 0;
}