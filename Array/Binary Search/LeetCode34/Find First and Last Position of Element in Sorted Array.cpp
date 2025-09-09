#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size(); // 下面使用的是[left, right)，左闭右开，因此right要比索引大1

        int beginIndex = -1;
        int endIndex = -1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
            {
                beginIndex = mid;
                right = mid; // 左闭右开，那么right收缩的时候，要考虑mid
            }
            else if (nums[mid] > target)
            {
                right = mid;
            }
            else if (nums[mid] < target)
            {
                left = mid + 1;
            }
        }

        left = 0;
        right = nums.size();
        // 同上
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
            {
                endIndex = mid;
                left = mid + 1;
            }
            else if (nums[mid] > target)
            {
                right = mid;
            }
            else if (nums[mid] < target)
            {
                left = mid + 1;
            }
        }

        return {beginIndex, endIndex};
    }
};

// ---- 测试代码 ----
struct Case
{
    vector<int> nums;
    int target;
    vector<int> expect;
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
        {{}, 1, {-1, -1}},
        {{1}, 1, {0, 0}},
        {{1}, 0, {-1, -1}},
        {{1, 2, 3, 4, 5}, 3, {2, 2}},
        {{1, 2, 2, 2, 3}, 2, {1, 3}},
        {{2, 2, 2, 2}, 2, {0, 3}},
        {{1, 1, 2, 3, 3}, 1, {0, 1}},
        {{1, 1, 2, 3, 3}, 3, {3, 4}},
        {{1, 2, 3, 4, 5}, 6, {-1, -1}},
        {{1, 3, 5, 7, 9}, 0, {-1, -1}},
        {{-5, -3, -3, -1, 0, 0, 0, 2}, 0, {4, 6}},
        {{1, 2, 3, 3, 3, 4, 5}, 3, {2, 4}},
        {{1, 2, 3, 4, 4, 4, 5, 6}, 4, {3, 5}},
        {{1, 2, 3, 4, 5}, 1, {0, 0}},
        {{1, 2, 3, 4, 5}, 5, {4, 4}},
        {{10, 20}, 5, {-1, -1}},
        {{10, 20}, 30, {-1, -1}},
        {{-2, -2, -2, -1, 3, 3, 9}, -2, {0, 2}},
    };

    Solution sol;
    int pass = 0;
    for (size_t i = 0; i < cases.size(); ++i)
    {
        auto nums = cases[i].nums; // 函数会读不改，这里复制无妨
        auto got = sol.searchRange(nums, cases[i].target);
        bool ok = (got == cases[i].expect);
        if (ok)
            ++pass;

        cout << "Case " << (i + 1) << ": "
             << "nums=" << vec2str(cases[i].nums)
             << ", target=" << cases[i].target
             << ", expect=" << vec2str(cases[i].expect)
             << ", got=" << vec2str(got)
             << " --> " << (ok ? "PASS" : "FAIL") << "\n";
    }
    cout << "\nSummary: " << pass << "/" << cases.size() << " passed.\n";
    return 0;
}