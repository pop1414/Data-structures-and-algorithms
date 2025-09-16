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
    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        return build(nums, 0, nums.size() - 1);
    }

    TreeNode *build(vector<int> &nums, int left, int right)
    {
        // 两种特殊情况
        if (left > right)
        {
            return nullptr;
        }

        if (left == right)
        {
            TreeNode *root = new TreeNode(nums[left]);
            return root;
        }

        // 从root往下建树
        // 先找到原数组/子数组[最大的值与对应的下标]
        auto [maxNum, bestIndex] = findMax(nums, left, right);
        TreeNode *root = new TreeNode(maxNum);
        // 然后递归遍历去建左右子树
        root->left = build(nums, left, bestIndex - 1);
        root->right = build(nums, bestIndex + 1, right);

        return root;
    }

    // 返回数组[最大的值与对应的下标]
    pair<int, int> findMax(vector<int> &nums, int left, int right)
    {
        int maxNum = nums[left];
        int bestIndex = left;
        for (int i = left + 1; i <= right; i++)
        {
            if (maxNum < nums[i])
            {
                maxNum = nums[i];
                bestIndex = i;
            }
        }
        return make_pair(maxNum, bestIndex);
    }
};