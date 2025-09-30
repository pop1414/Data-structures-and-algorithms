#include <bits/stdc++.h>

using namespace std;

// BST的中序遍历就是一个升序数组
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
    int res;
    int kthSmallest(TreeNode *root, int k)
    {
        int rank = 1;
        traverse(root, k, rank);
        return res;
    }
    void traverse(TreeNode *root, int k, int &rank)
    {
        if (rank == -1)
        {
            return;
        }
        if (root == nullptr)
        {
            return;
        }
        traverse(root->left, k, rank);

        if (rank == k)
        {
            res = root->val;
        }

        rank++;
        traverse(root->right, k, rank);
    }
};