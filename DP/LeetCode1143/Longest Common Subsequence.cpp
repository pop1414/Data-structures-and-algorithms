#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {

        int n = text1.size();
        int m = text2.size();

        // dp定义是t1 0~i-1字符与t2 0~j-1字符的最大公共子序列长度
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (text1[i - 1] == text2[j - 1])
                {
                    // 如果相同，则在之前的基础上加1
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    // 如果不同，则此时指向的字符是无用的（对增大公共子序列的长度），所以要取之前的最大值
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[n][m];
    }
};

int main()
{

    string t1 = "abc";
    string t2 = "def";

    Solution s;
    s.longestCommonSubsequence(t1, t2);

    return 0;
}