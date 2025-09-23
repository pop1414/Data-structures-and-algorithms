#include <bits/stdc++.h>

using namespace std;

// 递归
class Solution1
{
public:
    int fib(int n)
    {
        vector<int> memo(n + 1, -1);
        return dp(n, memo);
    }

    int dp(int n, vector<int> &memo)
    {
        if (n == 1 || n == 0)
        {
            return n;
        }

        if (memo[n] != -1)
        {
            return memo[n];
        }

        memo[n] = dp(n - 1, memo) + dp(n - 2, memo);
        return memo[n];
    }
};

// 递推
class Solution2
{
public:
    int fib(int n)
    {
        vector<int> memo(n + 1, -1);
        // 注意边界条件
        if (n == 0)
        {
            return 0;
        }
        memo[0] = 0;
        memo[1] = 1;
        // 注意for循环范围
        for (int i = 2; i < n + 1; i++)
        {
            memo[i] = memo[i - 1] + memo[i - 2];
        }
        return memo[n];
    }
};