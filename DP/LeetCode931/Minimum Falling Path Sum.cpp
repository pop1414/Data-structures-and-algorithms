#include <bits/stdc++.h>
#include <algorithm>
// using namespace std;

class Solution
{
public:
    int minFallingPathSum(std::vector<std::vector<int>> &matrix)
    {
        int n = matrix.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            dp[0][i] = matrix[0][i];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int mid = dp[i - 1][j];
                int left = INT_MAX;
                int right = INT_MAX;
                if (j - 1 >= 0)
                    left = dp[i - 1][j - 1];
                if (j + 1 < n)
                    right = dp[i - 1][j + 1];
                int mindp = 0;
                mindp = std::min(left, mid);
                mindp = std::min(mindp, right);
                dp[i][j] = mindp + matrix[i][j];
            }
        }
        int minres = INT_MAX;
        for (int j = 0; j < n; j++)
        {
            minres = std::min(dp[n - 1][j], minres);
        }
        return minres;
    }
};