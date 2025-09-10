#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int shipWithinDays(vector<int> &weights, int days)
    {
        // 同是用二分查找解决问题，但是要注意left与right的初始值，不能一昧的设1与x + 1;诸如此类
        int left = 0;
        int right = 1;
        for (int ddy : weights)
        {
            left = max(left, ddy);
            right += ddy;
        }

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            int time = f(weights, mid);
            if (time == days)
            {
                right = mid;
            }
            else if (time > days)
            {
                left = mid + 1;
            }
            else if (time < days)
            {
                right = mid;
            }
        }
        return left;
    }

    int f(vector<int> &weights, int x)
    {
        int day = 1;
        int curWeights = 0;
        for (int w : weights) // 当觉得while循环中的i不好控制++，--可以换成cpp的for
        {
            if (curWeights + w > x)
            {
                day++;
                curWeights = 0;
            }
            curWeights += w;
        }
        return day;
    }
};

// ===== 测试框架 =====
struct Case
{
    vector<int> weights;
    int days;
    int expect;
};

string vec2str(const vector<int> &v)
{
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        s += to_string(v[i]);
        if (i + 1 < v.size())
            s += ", ";
    }
    s += "]";
    return s;
}

int main()
{
    vector<Case> cases = {
        // LeetCode 官方示例
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5, 15},
        {{3, 2, 2, 4, 1, 4}, 3, 6},
        {{1, 2, 3, 1, 1}, 4, 3},

        // 单一包裹
        {{10}, 1, 10},
        {{10}, 2, 10}, // 无论天数多大，至少要能装下最重的

        // 两个包裹
        {{5, 5}, 1, 10},
        {{5, 5}, 2, 5},

        // 边界情况
        {{7, 2, 5, 10, 8}, 2, 18}, // 分成 [7,2,5] 和 [10,8]
        {{7, 2, 5, 10, 8}, 5, 10}, // 每天一个，最大是 10

        // 大数测试
        {{100, 200, 300, 400, 500}, 5, 500},
        {{100, 200, 300, 400, 500}, 1, 1500}};

    Solution sol;
    int pass = 0;

    for (size_t i = 0; i < cases.size(); ++i)
    {
        auto weights = cases[i].weights;
        int got = sol.shipWithinDays(weights, cases[i].days);
        bool ok = (got == cases[i].expect);

        if (ok)
            ++pass;

        cout << "Case " << (i + 1) << ": "
             << "weights=" << vec2str(cases[i].weights)
             << ", days=" << cases[i].days
             << ", expect=" << cases[i].expect
             << ", got=" << got
             << " --> " << (ok ? "PASS" : "FAIL") << "\n";
    }

    cout << "\nSummary: " << pass << "/" << cases.size() << " passed.\n";
    return 0;
}