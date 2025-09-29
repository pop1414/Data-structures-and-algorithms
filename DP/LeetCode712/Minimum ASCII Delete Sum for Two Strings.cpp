#include <bits/stdc++.h>

using namespace std;

// 思路同lcs相似，但是会有不同
class Solution
{
public:
    int minimumDeleteSum(string s1, string s2)
    {
        int n = s1.size();
        int m = s2.size();

        // dp定义为s1 0~i-1, s2 0~j-1删除不同的字符的最小值
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        // 所以初始化会有不同
        for (int j = 1; j <= m; j++)
        {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }
        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                // 相同说明不用删，也就不用加ASCII码
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    // 不同看删除哪个最小
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
                }
            }
        }
        return dp[n][m];
    }
};