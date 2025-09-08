#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int left = 0;
        int right = 0;
        int bestLen = 0; // 初始化为0，当字符串为空时，无法进入第一个while循环，直接返回0

        unordered_map<char, int> window;

        bool sharp = false;

        while (right < s.size())
        {
            char c = s[right];
            right++;
            window[c]++;
            int len = right - left; // 提前计算长度是考虑了整个字符串都无重复字符，也就无法进入到第二个while循环中
            if (window[c] > 1)
            {
                sharp = true;
            }
            else // 当每次不存在重复字符时，比较最优长度
            {
                if (len > bestLen)
                {
                    bestLen = len;
                }
            }

            while (sharp)
            {
                len = right - left - 1;
                if (len > bestLen)
                {
                    bestLen = len;
                }
                char x = s[left];
                left++;
                window[x]--;
                if (c == x)
                {
                    sharp = false;
                }
            }
        }
        return bestLen;
    }
};

int main()
{
    Solution sol;

    // Test cases with expected and actual outputs
    vector<pair<string, int>> test_cases = {
        {"abcabcbb", 3},   // Expected: "abc"
        {"bbbbb", 1},      // Expected: "b"
        {"pwwkew", 3},     // Expected: "wke"
        {"", 0},           // Expected: ""
        {"a", 1},          // Expected: "a"
        {"au", 2},         // Expected: "au"
        {"dvdf", 3},       // Expected: "vdf"
        {"aab", 2},        // Expected: "ab"
        {"abcde", 5},      // Expected: "abcde"
        {"abcdeabcde", 5}, // Expected: "abcde"
        {"tmmzuxt", 5},    // Expected: "mzuxt"
        {"ohvhjdml", 6}    // Expected: "hvhjdml"
    };

    for (const auto &test_case : test_cases)
    {
        string s = test_case.first;
        int expected = test_case.second;
        int actual = sol.lengthOfLongestSubstring(s);
        cout << "Input: '" << s << "'" << endl;
        cout << "Expected: " << expected << ", Actual: " << actual << endl;
        cout << (expected == actual ? "Test Passed" : "Test Failed") << endl;
        cout << "-----------------------------------" << endl;
    }

    return 0;
}