#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = i;
        }
        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                // 注意访问字符串时候的下标
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // dp[i - 1][j - 1]为替换;dp[i - 1][j]变为[i][j]，j长度不变，而i却多了一个，说明这多了一个的要删除; dp[i][j - 1]变为[i][j]，i长度不变，而j却多了一个，说明要新插入一个
                else
                {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
            }
        }
        return dp[n][m];
    }
};