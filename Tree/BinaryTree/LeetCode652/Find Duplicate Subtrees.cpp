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
    unordered_map<string, int> mp; //< <x, l, r>, id > tuple默认无哈希，所以转化为string
    unordered_map<int, int> cnt;   //<id, count>
    vector<TreeNode *> ans;
    vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
    {
        traverse(root);
        return ans;
    }
    // 返回序号id，空为0
    int traverse(TreeNode *root)
    {
        if (!root)
        {
            return 0;
        }

        int l = traverse(root->left);
        int r = traverse(root->right);

        string key = to_string(root->val) + "," + to_string(l) + "," + to_string(r);

        int id;

        // 如果该子树已被存储了，获取其id
        if (mp.count(key))
        {
            id = mp[key];
        }
        // 否则，存储一个新的子树id
        else
        {
            id = mp.size() + 1;
            mp[key] = id;
        }

        // 不管存不存在，cnt都会++，当加完后==2，即这次访问的时候为1，说明是第一次重复子树，加入ans中；其他情况加入会重复答案
        cnt[id]++;
        if (cnt[id] == 2)
            ans.push_back(root);

        return id;
    }
};