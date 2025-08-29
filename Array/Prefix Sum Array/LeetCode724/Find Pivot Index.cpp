#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> perSum;
    int pivotIndex(vector<int>& nums) {
        bool flag = false;
        bulidPre(nums);
        int n = nums.size();
        int leftSum;
        int rightSum;
        int i;
        for(i = 0; i < n; i++){
            if (i == 0){
                leftSum = 0;
                rightSum = perSum[n] - perSum[1];
            }
            else if (i == n - 1){
                rightSum = 0;
                leftSum = perSum[n - 1] - perSum[0];
            }else{
                leftSum = perSum[i] - perSum[0];
                rightSum = perSum[n] - perSum[i + 1];
            }

            if (leftSum == rightSum){
                flag = true;
                break;
            }


        }

        if(!flag){
            i = -1;
        }

        return i;
    }
    void bulidPre(vector<int>& nums){
        perSum.resize(nums.size() + 1);
        perSum[0] = 0;
        for (int i = 1; i < perSum.size(); i++){
            perSum[i] = nums[i - 1] + perSum[i - 1];
        }
    }
   
};

int main() {
    Solution s;

    // Case 1: 官方样例
    vector<int> nums1 = {1,7,3,6,5,6};
    cout << "Case 1: " << s.pivotIndex(nums1) << " (Expected 3)" << endl;

    // Case 2: 没有中心下标
    vector<int> nums2 = {1,2,3};
    cout << "Case 2: " << s.pivotIndex(nums2) << " (Expected -1)" << endl;

    // Case 3: 单个元素，索引 0 一定是中心
    vector<int> nums3 = {10};
    cout << "Case 3: " << s.pivotIndex(nums3) << " (Expected 0)" << endl;

    // Case 4: 中心下标在最左边 (index = 0)
    vector<int> nums4 = {2,1,-1};
    cout << "Case 4: " << s.pivotIndex(nums4) << " (Expected 0)" << endl;

    // Case 5: 多个解，取最左边的
    vector<int> nums5 = {0,0,0,0};
    cout << "Case 5: " << s.pivotIndex(nums5) << " (Expected 0)" << endl;

    // Case 6: 边界情况，空数组
    vector<int> nums6 = {};
    cout << "Case 6: " << s.pivotIndex(nums6) << " (Expected -1)" << endl;

    return 0;
}