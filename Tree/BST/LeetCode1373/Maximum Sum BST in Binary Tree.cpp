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
    struct SubTreeInfo
    {
        bool isBST; // 前提是BST
        int minVal; // 子树最小值
        int maxVal; // 子树最大值
        int subSum; // 子树和
    };

    int maxSum = 0;
    int maxSumBST(TreeNode *root)
    {
        traverse(root);
        return maxSum;
    }
    SubTreeInfo traverse(TreeNode *root)
    {
        if (root == nullptr)
        {
            // 为了方便比较空节点返回的最小最大值需要注意
            return {true, INT_MAX, INT_MIN, 0};
        }

        SubTreeInfo leftTree = traverse(root->left);
        SubTreeInfo rightTree = traverse(root->right);

        int val = root->val;
        int sum = val;
        // val比左子树最大还大，val比右子树最小还小，才是BST，前提是左右子树本身也是BST
        if (leftTree.isBST && rightTree.isBST && val > leftTree.maxVal && val < rightTree.minVal)
        {
            sum += leftTree.subSum + rightTree.subSum;
            maxSum = max(sum, maxSum);
            // 还有min，max，是为了考虑空节点返回的值是特例，不能无脑返回L.minVal与R.maxVal，这样分别返回的是INT_MAX,INT_MIN显然就错了
            return {true, min(val, leftTree.minVal), max(val, rightTree.maxVal), sum};
        }

        // 不是BST的情况，只有isBST这一项是有意义的
        return {false, 0, 0, 0};
    }
};

TreeNode *buildTree()
{
    // 根节点
    TreeNode *root = new TreeNode(4);

    // 第二层
    root->left = new TreeNode(8);
    root->right = nullptr;

    // 第三层
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(1);

    // 第四层
    root->left->left->left = new TreeNode(9);
    root->left->left->right = nullptr;

    root->left->right->left = new TreeNode(-5);
    root->left->right->right = new TreeNode(4);

    // 第五层
    root->left->right->left->left = new TreeNode(-3);
    root->left->right->left->right = nullptr;

    root->left->right->right->left = nullptr;
    root->left->right->right->right = new TreeNode(10);

    return root;
}

int main()
{
    Solution s;
    TreeNode *root = buildTree();
    s.maxSumBST(root);

    return 0;
}