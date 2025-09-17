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
    deque<vector<int>> res;
    queue<TreeNode *> q;// 双端队列
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        if (!root)
        {
            return vector<vector<int>>(res.begin(), res.end());// 用队列构造vector
        }

        levelOrder(root);
        return vector<vector<int>>(res.begin(), res.end());
    }

    void levelOrder(TreeNode *root)
    {
        q.push(root);

        while (!q.empty())
        {
            vector<int> temp;
            int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                TreeNode *cur = q.front();
                temp.push_back(cur->val);
                q.pop();

                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            res.push_front(temp);// 放入前端就可从底至上
        }
    }
};