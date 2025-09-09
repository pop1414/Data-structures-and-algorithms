#include <bits/stdc++.h>

using namespace std;

// 本质是将问题转为二分查找
// 吃香蕉的速度为x，自变量
// 吃完香蕉所需的时间与x有关，分析后发现是有关x的单调递减函数f(x)
// target是h，即所需时间的最大，在最大值的范围内找到f(x)的最小值，即寻找左侧边界二分查找
class Solution
{
public:
    int minEatingSpeed(vector<int> &piles, int h)
    {
        int left = 1;
        int right = 1000000000 + 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (f(piles, mid) == h)
            {
                right = mid;
            }
            else if (f(piles, mid) > h)
            {
                left = mid + 1;
            }
            else if (f(piles, mid) < h)
            {
                right = mid;
            }
        }

        return left;
    }

    // 分析出f(x)是关键
    // 二分查找的f(x)是单调的数组，而在这里是随x变化单调递减的时间
    int f(vector<int> &piles, int x)
    {
        // 传入的x为mid，即不断寻找最佳的速度
        int hour = 0;
        for (int i = 0; i < piles.size(); i++)
        {
            hour += piles[i] / x;
            if (piles[i] % x > 0)
            {
                hour++;
            }
        }
        return hour;
    }
};

// ===== 测试框架 =====
struct Case
{
    vector<int> piles;
    int h;
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
        // 基础样例（LeetCode 经典）
        {{3, 6, 7, 11}, 8, 4},
        {{30, 11, 23, 4, 20}, 5, 30},
        {{30, 11, 23, 4, 20}, 6, 23},

        // 单堆/极端小时数
        {{9}, 1, 9},
        {{9}, 10, 1},

        // 边界：恰好等于堆数（每堆至少 1 小时）
        {{1, 1, 1, 1}, 4, 1},

        // 小规模多堆
        {{2, 2}, 2, 2},
        {{2, 2}, 3, 2},
        {{3, 3, 3}, 3, 3},
        {{3, 3, 3}, 4, 3},

        // 含大数（测试上界与整除/取整）
        {{805306368, 805306368}, 2, 805306368},
        {{1000000000}, 1, 1000000000},
        {{1000000000, 1}, 2, 1000000000},

        // 更大但小时数宽松
        {{312884470}, 968709470, 1},

        // 多样化组合
        {{5, 8, 6}, 3, 8}, // k=8 -> ceil(5/8)=1, ceil(8/8)=1, ceil(6/8)=1, 共3小时
        {{5, 8, 6}, 4, 6}, // k=5 -> 1+2+2=5小时；k=4 -> 2+2+2=6>4
    };

    Solution sol;
    int pass = 0;

    for (size_t i = 0; i < cases.size(); ++i)
    {
        auto piles = cases[i].piles; // 不修改原用例
        int h = cases[i].h;
        int got = sol.minEatingSpeed(piles, h);
        bool ok = (got == cases[i].expect);

        if (ok)
            ++pass;

        cout << "Case " << (i + 1) << ": "
             << "piles=" << vec2str(cases[i].piles)
             << ", h=" << h
             << ", expect=" << cases[i].expect
             << ", got=" << got
             << " --> " << (ok ? "PASS" : "FAIL") << "\n";
    }

    cout << "\nSummary: " << pass << "/" << cases.size() << " passed.\n";
    return 0;
}
