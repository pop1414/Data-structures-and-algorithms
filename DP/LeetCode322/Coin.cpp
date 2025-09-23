#include <bits/stdc++.h>

using namespace std;

// 递推，dp定义，n为金额（n < amount）这就确定了最外层的循环范围；第二层循环范围是根据能导致n状态变化来确定的，正好是coins的种类
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int coinCnt = coins.size();
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int i = 1; i < amount + 1; i++)
        {
            // 巧用INT_MAX
            int minDP = INT_MAX;
            for (int coin : coins)
            {
                // 是合法金额再进入判断
                if (i - coin >= 0)
                {
                    int temp = dp[i - coin];
                    minDP = min(minDP, temp);
                }
            }
            dp[i] = (minDP == INT_MAX) ? INT_MAX : minDP + 1;
        }
        // 如果是无穷，说明无结果返回-1
        return (dp[amount] == INT_MAX) ? -1 : dp[amount];
    }
};

// 递归
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        // -2未计算，-1不可达
        vector<int> memo(amount + 1, -2);
        memo[0] = 0;
        int res = dp(coins, amount, memo);
        return res;
    }

    int dp(vector<int> &coins, int n, vector<int> &memo)
    {

        if (n < 0)
        {
            return -1;
        }

        // 包括不可达
        if (memo[n] != -2)
        {
            return memo[n];
        }

        int minSub = INT_MAX;
        for (int coin : coins)
        {
            int sub = dp(coins, n - coin, memo);
            // 若可达，算min
            if (sub != -1)
            {
                minSub = min(minSub, sub);
            }
        }

        // 若子问题都不可达，返回不可达-1
        memo[n] = (minSub == INT_MAX) ? -1 : minSub + 1;

        return memo[n];
    }
};