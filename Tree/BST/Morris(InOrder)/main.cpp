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
    void morrisInOrderTraversal(TreeNode *root)
    {
        TreeNode *curNode = root;
        while (curNode != nullptr)
        {
            if (curNode->left == nullptr)
            {
                cout << curNode->val << "->";
                curNode = curNode->right;
            }
            else
            {
                TreeNode *preCur = curNode->left;
                while (preCur->right != nullptr && preCur->right != curNode)
                {
                    preCur = preCur->right;
                }

                if (preCur->right == curNode)
                {
                    cout << curNode->val << "->";
                    curNode = curNode->right;
                    preCur->right = nullptr;
                }
                else
                {
                    preCur->right = curNode;
                    curNode = curNode->left;
                }
            }
        }
    }

    void traverseReverse(TreeNode *root)
    {
        int sum = 0;
        TreeNode *curNode = root;
        while (curNode != nullptr)
        {
            if (curNode->right == nullptr)
            {
                cout << curNode->val << "->";
                curNode = curNode->left;
            }
            else
            {
                TreeNode *preCur = curNode->right;
                while (preCur->left != nullptr && preCur->left != curNode)
                {
                    preCur = preCur->left;
                }
                if (preCur->left == curNode)
                {
                    cout << curNode->val << "->";
                    curNode = curNode->left;
                    preCur->left = nullptr;
                }
                else
                {
                    preCur->left = curNode;
                    curNode = curNode->right;
                }
            }
        }
    }
};

// Helper function to create a binary tree
TreeNode *createTree()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    return root;
}

int main()
{
    Solution solution;
    TreeNode *root = createTree();

    cout << "Morris Inorder Traversal: ";
    solution.morrisInOrderTraversal(root);
    cout << endl;
    cout << "Morris Inorder Traversal: ";
    solution.traverseReverse(root);
    cout << endl;

    return 0;
}
