#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> res;

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<int> road;
        vector<int> visit(nums.size(), 0);
        backtrack(nums, road, visit);
        return res;
    }

    void backtrack(vector<int> &nums, vector<int> &road, vector<int> &visit)
    {

        if (road.size() == nums.size())
        {
            res.push_back(road);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (visit[i] != 1)
            {
                road.push_back(nums[i]);
                visit[i] = 1;
                backtrack(nums, road, visit);
                road.pop_back();
                visit[i] = 0;
            }
        }
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> tests = {
        {1},
        {1, 2},
        {1, 2, 3},
        {1, 2, 3, 4},
        {-1, 0, 1},
        {1, 2, 3, 4, 5}};

    for (auto &nums : tests)
    {
        auto ans = sol.permute(nums);
        cout << "输入: ";
        for (int x : nums)
            cout << x << " ";
        cout << "\n排列数量: " << ans.size() << endl;

        // 打印前 6 个结果
        cout << "前几个结果:" << endl;
        for (int i = 0; i < min((int)ans.size(), 6); i++)
        {
            for (int x : ans[i])
                cout << x << " ";
            cout << endl;
        }
        cout << "------------------------" << endl;
    }
    return 0;
}
