#include <bits/stdc++.h>

using namespace std;

// 分割数组最大值，即将数组分割成k个连续的子数组
// 换种思路，数组元素表示货物，要将这些货物分为k天运走
// 某一天的货物重量为这k天最重的，要求改天的货物重量降至最小，且满足在k天中运完全部货物
// 其实就是要找到最小承载重量
class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {
        int sum = 0;
        int left = 0;
        for (int x : nums)
        {
            left = max(x, left);
            sum += x;
        } // left最小应该为元素的最大值
        int right = sum + 1; // right应该为数组元素和 + 1

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            int time = f(nums, mid);
            if (time == k)
            {
                right = mid;
            }
            else if (time > k)
            {
                left = mid + 1;
            }
            else if (time < k)
            {
                right = mid;
            }
        }
        return left;
    }

    int f(vector<int> &nums, int mid)
    {
        // mid是承载量，看看在该承载量下，需要多少天运完
        int day = 1; // 初始化为1，这个1其实是数组最后一部分的且不会超出承载量的货物
        int curWeights = 0;
        for (int x : nums)
        {
            if (curWeights + x > mid) // 先判断是否超重，超重了天数加1，重置curWeights
            {
                day++;
                curWeights = 0;
            }
            curWeights += x; // 无论是否超重，都可以将更新curWeights放在最后
        }
        return day;
    }
};

int main()
{
    Solution sol;
    vector<pair<vector<int>, int>> tests = {
        {{7, 2, 5, 10, 8}, 2},
        {{1, 2, 3, 4, 5}, 2},
        {{1, 4, 4}, 3},
        {{1, 2, 3, 4, 5}, 5},
        {{2, 3, 1, 2, 4, 3}, 3},
        {{1}, 1},
        {{1000000, 1000000, 1000000}, 2}};
    vector<int> expects = {18, 9, 4, 5, 6, 1, 2000000};

    for (int i = 0; i < tests.size(); i++)
    {
        auto nums = tests[i].first;
        int k = tests[i].second;
        int got = sol.splitArray(nums, k);
        cout << "Case " << i + 1 << ": nums=";
        for (int x : nums)
            cout << x << " ";
        cout << " k=" << k
             << " => got=" << got
             << " expect=" << expects[i]
             << " --> " << (got == expects[i] ? "PASS" : "FAIL") << endl;
    }
    return 0;
}