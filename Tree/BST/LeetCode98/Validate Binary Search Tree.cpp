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
    bool isValidBST(TreeNode *root)
    {
        return validate(root, LLONG_MIN, LLONG_MAX);
    }
    bool validate(TreeNode *root, long long minVal, long long maxVal)
    {
        if (root == nullptr)
        {
            return true;
        }

        // 要看节点是否合法，将节点的值限制在一定范围内
        // 根据左右子树的不同，传入的最大最小值不一样
        if (root->val <= minVal || root->val >= maxVal)
        {
            return false;
        }

        // 实际上就是后根位置传子树的信息，不过是写到一块儿了
        return validate(root->left, minVal, root->val) && validate(root->right, root->val, maxVal);
    }
};