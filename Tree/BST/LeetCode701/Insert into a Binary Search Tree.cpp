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
    TreeNode *insertIntoBST(TreeNode *root, int val)
    {
        if (root == nullptr)
        {
            TreeNode *newNode = new TreeNode(val);
            root = newNode;
        }
        else
        {
            traverse(root, val);
        }
        return root;
    }
    void traverse(TreeNode *root, int val)
    {
        if (val < root->val)
        {
            if (root->left == nullptr)
            {
                TreeNode *newNode = new TreeNode(val);
                root->left = newNode;
                return;
            }
            else
            {
                traverse(root->left, val);
            }
        }
        if (val > root->val)
        {
            if (root->right == nullptr)
            {
                TreeNode *newNode = new TreeNode(val);
                root->right = newNode;
                return;
            }
            else
            {
                traverse(root->right, val);
            }
        }
    }
};