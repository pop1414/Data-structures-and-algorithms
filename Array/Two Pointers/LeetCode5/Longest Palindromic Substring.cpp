#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        string maxLength = "";
        for (int i = 0; i < s.size(); i++)
        {
            if (i != s.size() - 1 && s[i] == s[i + 1])
            {
                string s1 = isVaild(true, i, s);
                string s2 = isVaild(false, i, s);
                if (s2.size() <= s1.size())
                {
                    if (s1.size() > maxLength.size())
                    {
                        maxLength = s1;
                    }
                }
                else
                {
                    if (s2.size() > maxLength.size())
                    {
                        maxLength = s2;
                    }
                }
            }
            else
            {
                string s3 = isVaild(false, i, s);
                if (s3.size() > maxLength.size())
                {
                    maxLength = s3;
                }
            }
        }

        return maxLength;
    }

    string isVaild(bool flag, int index, string &s)
    {
        if (flag)
        {
            int left = index;
            int right = index + 1;
            while (left >= 0 && right <= s.size() - 1)
            {
                if (s[left] == s[right])
                {
                    left--;
                    right++;
                }
                else
                {
                    return s.substr(left + 1, right - left - 1);//（开始index， 字符串长度）
                }
            }
            return s.substr(left + 1, right - left - 1);
        }
        else
        {
            if (index - 1 >= 0 && index + 1 <= s.size() - 1)
            {
                int left = index - 1;
                int right = index + 1;
                while (left >= 0 && right <= s.size() - 1)
                {
                    if (s[left] == s[right])
                    {
                        left--;
                        right++;
                    }
                    else
                    {
                        return s.substr(left + 1, right - left - 1);
                    }
                }
                return s.substr(left + 1, right - left - 1);
            }
            else
            {
                return string(1, s[index]);//单字符转化为字符串
            }
        }
    }
};

int main()
{
    Solution s;
    s.longestPalindrome("cbbd");

    return 0;
}