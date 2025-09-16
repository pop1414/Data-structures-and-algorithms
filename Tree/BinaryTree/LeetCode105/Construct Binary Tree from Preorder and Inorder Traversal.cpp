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

// 先序遍历注定了，
class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

    // l1其实就是每次创建子树的根节点的值
    TreeNode *build(vector<int> &preorder, int l1, int r1, vector<int> &inorder, int l2, int r2)
    {

        if (l1 > r1)
        {
            return nullptr;
        }

        if (l1 == r1)
        {
            TreeNode *root = new TreeNode(preorder[l1]);
            return root;
        }

        TreeNode *root = new TreeNode(preorder[l1]);
        auto [index, len] = findIndex(inorder, preorder[l1], l2, r2);
        // 因为先序遍历的特性，root左子树的root为l1 + 1，然后囊括len（左子树元素的个数）；中序遍历就比较好区分，在l2~r2之间插入一个index作为划分
        root->left = build(preorder, l1 + 1, l1 + len, inorder, l2, index - 1);
        // 右子树的root为l1 + 1 + len（左子树元素的个数）；中序遍历就比较好区分，在l2~r2之间插入一个index作为划分
        root->right = build(preorder, l1 + len + 1, r1, inorder, index + 1, r2);

        return root;
    }

    // 在中序遍历找到root节点值的下标，l2~index为root的左子树元素，index + 1~r2为右子树元素
    // len为左子树元素个数
    pair<int, int> findIndex(vector<int> &inorder, int num, int l2, int r2)
    {
        for (int i = l2; i <= r2; i++)
        {
            if (inorder[i] == num)
            {
                int len = i - l2;
                return make_pair(i, len);
            }
        }
        return make_pair(-1, -1);
    }
};