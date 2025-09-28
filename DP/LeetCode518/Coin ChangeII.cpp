#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
        // 当金额为0时，有唯一一种解法就是，都不选
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }

        // !!!或许可以优化成for(int coin : coins)
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= amount; j++)
            {
                if (j - coins[i - 1] >= 0)
                {
                    // 选第i个金币，所以应该是dp[i][j -coins[i - 1]]
                    int choose = dp[i][j - coins[i - 1]];
                    int noChoose = dp[i - 1][j];
                    dp[i][j] = choose + noChoose;
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][amount];
    }
};

int main()
{

    vector<int> coins = {1, 2, 5};
    Solution s;
    cout << s.change(5, coins);
    return 0;
}