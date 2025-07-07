#include <iostream>
#include <vector>

template <typename T>
class BinaryTree//二叉树类，，
{
private:
    struct TreeNode
    {
        T val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(T val_) : val(val_), left(nullptr), right(nullptr) {};
    };

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

    // 创建二叉树对象
    // BinaryTree tree;

    // 插入样例数据
    // tree.insert(50);
    // tree.insert(30);
    // tree.insert(70);
    // tree.insert(20);
    // tree.insert(40);
    // tree.insert(60);
    // tree.insert(80);

    // // 输出三种遍历序列和层序遍历序列
    // std::cout << "中序遍历: ";
    // tree.inorder();
    // std::cout << std::endl;

    // std::cout << "前序遍历: ";
    // tree.preorder();
    // std::cout << std::endl;

    // std::cout << "后序遍历: ";
    // tree.postorder();
    // std::cout << std::endl;

    // std::cout << "层序遍历: ";
    // tree.levelOrder();
    // std::cout << std::endl;
    return 0;
}