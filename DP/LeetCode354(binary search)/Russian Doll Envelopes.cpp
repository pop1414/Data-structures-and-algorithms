#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int maxEnvelopes(vector<vector<int>> &envelopes)
    {
        int piles = 0;
        int n = envelopes.size();
        // 按照宽度升序排序，满足第一个条件，再比较高度；这样就化为比较高度的一维最长递增子序列
        // 当宽度相同的时候，按高度降序排序，因为这样同等宽度的信封，最多也就新创建一个堆，高度小的肯定不会再创建一个新堆
        sort(envelopes.begin(), envelopes.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0]; });
        vector<int> top(n);
        vector<int> topIndex(n);
        for (int i = 0; i < n; i++)
        {
            int left = 0;
            int right = piles;

            int poker = envelopes[i][1];

            while (left < right)
            {
                int mid = left + (right - left) / 2;

                if (top[mid] == poker)
                {
                    right = mid;
                }
                else if (top[mid] < poker)
                {
                    left = mid + 1;
                }
                else if (top[mid] > poker)
                {
                    right = mid;
                }
            }
            if (left == piles)
                piles++;

            top[left] = poker;
            topIndex[left] = i;
        }
        return piles;
    }
};