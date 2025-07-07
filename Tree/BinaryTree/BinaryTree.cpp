#include <iostream>
#include <vector>

template <typename T>
class BinaryTree // 二叉树类，，
{
private:
    struct TreeNode
    {
        T val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(T val_) : val(val_), left(nullptr), right(nullptr) {};
    };
    ////demo
    TreeNode *root;

public:
    BinaryTree(const std::vector<T> &arr, int &index)
    {
        if (arr[index] == -1)
        {
            root = NULL;
            return root;
        }
        else
        {
            root = (T *)malloc(sizeof(T));

            root->c = Tree[*index];
        }
        (*index)++;
        root->left = CBT(Tree, root->left, index);
        (*index)++;
        root->right = CBT(Tree, root->right, index);
        return root;
        ;
    }
    void preOrder(TreeNode *root)
    {
        if (root == nullptr)
        {
            return;
        }

        std::cout << root->val << "->";
        preOrder(root->left);
        preOrder(root->right);
    }
    void inOrder(TreeNode *root)
    {
        if (root == nullptr)
        {
            return;
        }

        preOrder(root->left);
        std::cout << root->val << "->";
        preOrder(root->right);
    }
    void postOrder(TreeNode *root)
    {
        if (root == nullptr)
        {
            return;
        }

        preOrder(root->left);
        preOrder(root->right);
        std::cout << root->val << "->";
    }
    void levelOrderTraversal(TreeNode *root)
    {
        ;
    }
    ~BinTree() { ; }
};

int main()
{
    std::vector<int> arr;

    std::cout << 1111;
    return 0;
}