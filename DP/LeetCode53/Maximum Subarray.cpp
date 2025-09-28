#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int>dp (n, 0);
        dp[0] = nums[0];
        int maxNum = dp[0];
        for(int i = 1; i < n; i++){
            if(dp[i - 1] < 0){
                dp[i] = nums[i];
                maxNum = max(dp[i], maxNum);
            }
            else{
                dp[i] = nums[i] + dp[i - 1];
                maxNum = max(dp[i], maxNum);
            }
        }

        return maxNum; 
    }
};