#include <bits/stdc++.h>

using namespace std;

// 0-1背包本质上是求解不同背包容量下的最优解，所以求解过程中求出来了很多w<W的最优解，最后返回结果的时候返回dp[N][W]
int maxValue(int W, vector<int> &wt, vector<int> &value)
{
    int n = wt.size();
    // dp[i][w], 前i个物品中，背包容量为w时，最大的val
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        // w从1开始是因为，dp[i][0] = 0
        for (int w = 1; w <= W; w++)
        {
            // 背包容量放不下i物品时
            if (w - wt[i - 1] < 0)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                // 不选i， 选i，value[i - 1]，i物品的价值下标要小心
                dp[i][w] = max(dp[i - 1][w], dp[i][w - wt[i - 1]] + value[i - 1]);
            }
        }
    }
    return dp[n][W];
}

int main()
{
    // 背包容量
    int W = 5;
    // 物品数量
    int n = 3;

    // 物品的重量
    vector<int> weights = {2, 3, 4};
    // 物品的价值
    vector<int> values = {3, 4, 5};

    // 求解并输出最大价值
    cout << "最大价值: " << maxValue(W, weights, values) << endl;

    return 0;
}