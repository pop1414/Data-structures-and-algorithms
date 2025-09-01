#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {
        // slow用来写新数组，fast用来读旧数组
        int slow = 0;
        for (int fast = 0; fast < s.size(); fast++)
        {
            if (s[fast] != ' ')
            { // 当遇到一个单词
                if (slow != 0)
                { // 如果不是新数组开头，就添加一个空格
                    s[slow++] = ' ';
                }
                while (s[fast] != ' ' && fast < s.size())
                {
                    s[slow++] = s[fast++]; // 写新数组
                }
            }
        }
        s.resize(slow); // 最后新数组的大小就是slow

        reverse(s.begin(), s.end()); // 先反转整改数组

        for (int j = 0; j < slow; j++)
        { // 再反转单个单词
            if (s[j] != ' ')
            {
                int left, right;
                left = right = j;
                while (s[right] != ' ' && right < slow)
                { // 找到单词的左右边界，然后reverse
                    right++;
                }
                reverse(s.begin() + left, s.begin() + right);
                j = right;
            }
        }
        return s;
    }
};

int main()
{
    Solution sol;
    vector<pair<string, string>> tests = {
        {"  hello world  ", "world hello"},
        {"a   b   c", "c b a"},
        {"   hello   ", "hello"},
        {"     ", ""},
        {"I love   C++  and   algorithms", "algorithms and C++ love I"},
        {"a b c d", "d c b a"}};

    for (int i = 0; i < tests.size(); i++)
    {
        string input = tests[i].first;
        string expected = tests[i].second;
        string output = sol.reverseWords(input);
        cout << "样例 " << i + 1 << ":\n";
        cout << " 输入:    \"" << tests[i].first << "\"\n";
        cout << " 输出:    \"" << output << "\"\n";
        cout << " 期望:    \"" << expected << "\"\n";
        cout << (output == expected ? " ✅ 正确" : " ❌ 错误") << "\n\n";
    }
    return 0;
}