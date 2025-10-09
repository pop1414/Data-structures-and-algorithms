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
    vector<TreeNode *> generateTrees(int n)
    {
        return generate(1, n);
    }
    vector<TreeNode *> generate(int left, int right)
    {

        // 何时会有null
        // 当传入的left 与 right相同，单个节点左右都是null
        vector<TreeNode *> result;
        if (left > right)
        {
            result.push_back(nullptr);
            return result;
        }

        // 关键是这个for循环
        // i表示根节点
        for (int i = left; i <= right; i++)
        {
            // 生成左子树
            vector<TreeNode *> leftTree = generate(left, i - 1);

            // 生成右子树
            vector<TreeNode *> rightTree = generate(i + 1, right);

            // 因为是以i为根所以左右子树的递归生成都不包含i
            for (auto leftNode : leftTree)
            {
                for (auto rightNode : rightTree)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = leftNode;
                    root->right = rightNode;
                    // 将左右子树与root链接起来
                    result.push_back(root);
                }
            }
        }

        return result;
    }
};