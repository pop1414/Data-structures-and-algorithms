#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int bestIndex = 0;
        int bestLenth = 1;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            //改变思路，辅助函数不直接返回字符串，而是回文串的左右index
            auto [l1, r1] = isValid(s, i, i + 1, n);//i + 1 >= n不必担心，辅助函数做了边界控制
            int len1 = r1 - l1 + 1;
            if (len1 > bestLenth)
            {
                bestLenth = len1;
                bestIndex = l1;
            }

            auto [l2, r2] = isValid(s, i, i, n);
            int len2 = r2 - l2 + 1;
            if (len2 > bestLenth)
            {
                bestLenth = len2;
                bestIndex = l2;
            }
        }
        return s.substr(bestIndex, bestLenth);
    }

    pair<int, int> isValid(string &s, int l, int r, int n)
    {
        while (l >= 0 && r <= n - 1 && s[l] == s[r])
        {
            l--;
            r++;
        }

        return {l + 1, r - 1};
    }
};

int main()
{
    Solution s;
    s.longestPalindrome("cbbd");

    return 0;
}