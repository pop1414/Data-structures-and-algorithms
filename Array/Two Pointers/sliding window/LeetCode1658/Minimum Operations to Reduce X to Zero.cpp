#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums, int x)
    {
        int sum = 0;
        for (int x : nums)
        {
            sum += x;
        }
        int n = nums.size();

        int bestLen = 0;

        int subSum = sum - x; // 数组最左/右侧的元素和为目标x，那么可以反过来想，找到数组的一个子数组，和为sum - x，那总元素数-子数组元素数就等于减去的左右两侧元素个数，也就是操作数，那么这样就可以用滑动窗口
        int curSum = 0;

        int left = 0;
        int right = 0;

        bool move = false;

        if (subSum == 0)
        { // 这意味着整个数组加起来等于目标x，那就返回数组元素个数n
            return n;
        }

        while (right < n)
        {
            curSum += nums[right++];
            int len = right - left;
            if (curSum == subSum) // 找到符合条件的子数组，取最长的
            {
                if (len > bestLen)
                {
                    bestLen = len;
                }
            }
            else if (curSum > subSum) // 若和过大，则左侧需要收缩
            {
                move = true;
            }

            while (move && left < right)
            {
                curSum -= nums[left++];
                len = right - left;
                if (curSum == subSum)
                {
                    if (len > bestLen)
                    {
                        bestLen = len;
                    }
                }
                else if (curSum > subSum)
                {
                    move = true;
                }
                else // 和过小，往右侧扩大窗口
                {
                    move = false;
                }
            }
        }

        if (bestLen == 0)
        {
            return -1;
        }
        return n - bestLen;
    }
};

int main()
{
    Solution sol;

    // 测试用例
    vector<pair<vector<int>, int>> test_cases = {
        {{1, 1, 4, 2, 3}, 5},      // Expected: 2 (subarray [4, 1])
        {{5, 6, 7, 8, 9}, 4},      // Expected: -1 (no valid subarray)
        {{3, 2, 20, 1, 1, 3}, 10}, // Expected: 5 (subarray [20, 1, 1, 3])
        {{1, 1, 1, 1, 1}, 3},      // Expected: 3 (subarray [1, 1, 1])
        {{10, 5, 2, 7}, 9},        // Expected: 2 (subarray [5, 2])
        {{1, 1, 1, 1, 1}, 5},      // Expected: 5 (subarray [1, 1, 1, 1, 1])
    };

    for (const auto &test_case : test_cases)
    {
        vector<int> nums = test_case.first;
        int x = test_case.second;
        int result = sol.minOperations(nums, x);
        cout << "Input: [";
        for (int num : nums)
        {
            cout << num << " ";
        }
        cout << "] x = " << x << endl;
        cout << "Expected: " << (result == -1 ? "No solution" : to_string(result)) << endl;
        cout << "Actual: " << (result == -1 ? "No solution" : to_string(result)) << endl;
        cout << "-----------------------------------" << endl;
    }

    return 0;
}