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
    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }
        else if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }
        else
        {
            // 前两种已经包含了左右两边都是空的情况
            // 当左右两边为空时，直接删除（返回NULL），即返回左右两边任一一边
            if (root->left == nullptr)
            {
                TreeNode *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                TreeNode *temp = root->left;
                delete root;
                return temp;
            }
            // 两边都有子树，找到后驱节点，右子树中最小的
            else if (root->left && root->right)
            {
                // 需要同时找到后驱节点与后驱节点的父节点
                // 当后驱节点为root的右节点时，直接将后驱节点接过去
                TreeNode *after = root->right;
                TreeNode *afterFather = root->right;
                while (after->left != nullptr)
                {
                    if (after->left->left == nullptr)
                    {
                        afterFather = after;
                    }
                    after = after->left;
                }
                after->left = root->left;
                // 否则，要将后驱节点的右子树接到后驱节点父节点的左子树上
                if (after != root->right)
                {
                    afterFather->left = after->right;
                    after->right = root->right;
                }
                delete root;
                return after;
            }
        }
        return root;
    }
};