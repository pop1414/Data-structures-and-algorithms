#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        unordered_map<char, int> need, window;
        // 看看t字符串每种字符需要多少
        for (char c : t)
        {
            need[c]++;
        }

        int bestIndex = 0;
        int bestLen = INT_MAX;

        int valid = 0;

        int left = 0;
        int right = 0;

        while (right < s.size())
        {

            char c = s[right++];

            // s字符串出现了t字符串所需要的字符
            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c]) // 如果字符数量满足，表明该字符数量达标
                {
                    valid++;
                }
            }

            while (valid == need.size()) // 若所有字符数量都达标，就可以开始缩小窗口
            {

                if (right - left < bestLen)
                {
                    bestIndex = left;
                    bestLen = right - left; // 不是right - left + 1,是因为上面的right窗口是多一位的，保存的是right - 1的字符，但数值的right
                }

                char x = s[left++];

                // 缩小窗口时，发现会减少t字符所需要的字符
                if (need.count(x))
                {
                    window[x]--;
                    // 如果子串的字符数量不达标了，那么就停止缩小窗口；若还有余量就可以继续缩小窗口
                    if (window[x] < need[x])
                    {
                        valid--;
                    }
                }
            }
        }
        return s.substr(bestIndex, bestLen);
    }
};

int main()
{
    Solution s;
    s.minWindow("ADOBECODEBANC", "ABC");

    return 0;
}