#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
        }
        // 把数组分割成两个子数组且和相同，可以转化成0-1背包问题；
        // 可以假设每个物品价值与重量相同nums[i]
        // 转化为在容量允许的情况下，找到sum/2重量下，价值的最大值，看看是否为sum/2
        if (sum % 2 != 0)
        {
            return false;
        }
        int W = sum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        for (int i = 1; i <= n; i++)
        {
            for (int w = 1; w <= W; w++)
            {
                if (w - nums[i - 1] >= 0)
                {
                    // dp[i - 1][w - nums[i - 1]]易出错，记得注意重量
                    dp[i][w] = dp[i - 1][w - nums[i - 1]] + nums[i - 1];
                    dp[i][w] = max(dp[i][w], dp[i - 1][w]);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][W] == W;
    }
};