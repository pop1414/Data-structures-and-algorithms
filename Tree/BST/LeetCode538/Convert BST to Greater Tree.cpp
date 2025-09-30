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
class Solution1
{
public:
    TreeNode *convertBST(TreeNode *root)
    {
        int sum = 0;
        traverse(root, sum);
        return root;
    }
    void traverse(TreeNode *root, int &sum)
    {
        if (root == nullptr)
        {
            return;
        }
        traverse(root->right, sum);

        int nodeVal = root->val;
        root->val += sum;
        sum += nodeVal;

        traverse(root->left, sum);
    }
};

// 使用反序的morris遍历（中序遍历，无需递归空间，空间复杂度为O(1)）
class Solution2
{
public:
    TreeNode *convertBST(TreeNode *root)
    {
        traverse(root);
        return root;
    }
    void traverse(TreeNode *root)
    {
        int sum = 0;
        TreeNode *curNode = root;
        // right - root - left
        while (curNode != nullptr)
        {
            // 当现节点右子树为空，说明直接访问现节点即可
            if (curNode->right == nullptr)
            {
                // cout << curNode->val << "->";
                int nodeVal = curNode->val;
                curNode->val += sum;
                sum += nodeVal;
                // 然后往左子树遍历
                curNode = curNode->left;
            }
            else
            {
                // 找到现节点的前序节点
                TreeNode *preCur = curNode->right;
                // 注意考虑前序节点的左指针被利用（指向现节点，也就是前序节点的后序节点）
                while (preCur->left != nullptr && preCur->left != curNode)
                {
                    preCur = preCur->left;
                }
                // 被利用了，说明已经线程化过了，现节点的右子树已经访问过了，那么直接访问现节点即可
                if (preCur->left == curNode)
                {
                    // cout << curNode->val << "->";
                    int nodeVal = curNode->val;
                    curNode->val += sum;
                    sum += nodeVal;
                    curNode = curNode->left;
                    // 注意删除不必要的链接
                    preCur->left = nullptr;
                }
                // 未被利用，则前序节点的左指针指向现节点
                else
                {
                    preCur->left = curNode;
                    // 往右子树遍历
                    curNode = curNode->right;
                }
            }
        }
    }
};
