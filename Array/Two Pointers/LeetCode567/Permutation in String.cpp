#include <bits/stdc++.h>

using namespace std;

// 解决的问题实质是，在大的字符串中，是否有一段长度跟小的字符串相同的子串，里面的字符种类与数量与小的字符串完全一样
class Solution
{
public:
    bool checkInclusion(string s1, string s2)
    {
        int len = s1.size();
        unordered_map<char, int> need, window;
        for (char c : s1)
        {
            need[c]++;
        }

        int left = 0;
        int right = 0;

        int valid = 0;

        bool flag = false;

        while (right < s2.size())
        {

            // 先找到字符种类与数量达标的窗口，参杂其他无关字符没关系
            char c = s2[right];

            right++;

            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                {
                    valid++;
                }
            }

            // 然后缩小窗口去除无关字符
            while (valid == need.size())
            {
                char x = s2[left];

                // 如有可能一直缩小，然后发现字符种类与字符数量都达标，而且长度一致，说明找到答案
                int curLen = right - left;
                if (curLen == len)
                {
                    return true;
                }

                left++;
                // 如果缩小过程发现不满足字符数量了，放弃，重新扩大窗口
                if (need.count(x))
                {
                    window[x]--;
                    if (window[x] < need[x])
                    {
                        valid--;
                    }
                }
            }
        }

        return flag;
    }
};