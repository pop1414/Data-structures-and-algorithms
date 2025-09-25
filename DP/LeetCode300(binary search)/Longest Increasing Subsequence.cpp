#include <bits/stdc++.h>

using namespace std;

// dp[i]的定义是以i为结尾的子序列的最大长度
class Solution1
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n);
        // 一个数字的子序列为1
        dp[0] = 1;
        for (int i = 1; i < n; i++)
        {
            int maxdp = 1;
            // 从头开始遍历，找到比nums[i]小的数字nums[j]
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                {
                    // 得到最大的子序列
                    maxdp = max(maxdp, dp[j] + 1);
                }
            }
            // 找完所有可能比nums[i]小的，更新dp[i]
            dp[i] = maxdp;
        }
        // 找出最大的dp
        sort(dp.begin(), dp.end());
        return dp[n - 1];
    }
};

class x
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        // 堆数
        int piles = 0;
        vector<int> top(n, INT_MAX);
        for (int i = 0; i < n; i++)
        {
            int poker = nums[i];

            int left = 0;
            int right = piles;

            // 找到左边界的二分查找
            while (left < right)
            {
                int mid = left + (right - left) / 2;

                if (top[mid] == poker)
                    right = mid;
                else if (top[mid] > poker) 
                    right = mid;
                else if(top[mid] < poker)
                    left = mid + 1;
            }

            // 这个判断条件，可以处理piles = 0时候的情况；到这里的时候while循环退出（left>right)，而若left == piles，则说明新元素无处可放
            if(left == piles){
                piles++;
            }
            top[left] = poker;

        }
        return piles;
    }
};