#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int numTrees(int n)
    {
        // dp[i]为当节点数为i时有几种情况
        vector<int> dp(n + 1, 0);
        // NULL也是一种，一个节点一种
        dp[0] = 1;
        dp[1] = 1;
        int sum = 0;
        for (int i = 2; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                // 所以状态转移方程就是，当节点数为i时，从1节点开始，让每个节点作为根节点
                // 然后从1~i累加就得到节点数为i时的情况
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};