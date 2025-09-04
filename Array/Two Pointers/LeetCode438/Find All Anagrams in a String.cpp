#include <bits/stdc++.h>

using namespace std;

// 与LeetCode567是同类型的题，不过是要找到所有的排列子串，加入数组中
class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        int len = p.size();
        unordered_map<char, int> need, window;
        for (char c : p)
        {
            need[c]++;
        }
        int left = 0;
        int right = 0;

        int valid = 0;
        vector<int> res;

        while (right < s.size())
        {

            char c = s[right];
            right++;

            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                {
                    valid++;
                }
            }

            while (valid == need.size())
            {
                char x = s[left];
                int curLen = right - left;

                if (len == curLen)
                {
                    res.push_back(left);
                }
                left++;

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

        return res;
    }
};