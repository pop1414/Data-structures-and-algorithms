#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        if (k <= 1) // 目标k过小时，不可能会有满足的子数组
        {
            return 0;
        }

        int count = 0;
        int left = 0;
        int right = 0;
        int curProduct = 1;

        while (right < nums.size())
        {
            curProduct *= nums[right];

            while (curProduct >= k && left <= right) // <= 是为了能够除去自己，比如第一个元素 > k，那么缩小窗口的时候，就应该除去自己
            {
                curProduct /= nums[left++];
            }

            count += right - left + 1; // 是怎么得来的？

            // 对于有n个元素的集合：
            // 包含 1 个元素的子集有 n 个
            // 包含 2 个连续元素的子集有 n - 1 个
            // ...
            // 包含 n 个连续元素的子集有 1 个
            // 总共有 1 + 2 + 3 +... + n = （n+1）*n/2个连续元素的子集
            // 那么对于n-1个元素的集合：共有(n) * (n-1)/2个连续元素的子集。
            // (n+1)n/2 - n(n-1)/2 = n/2 * (2)=n
            // 对于n-1个元素的集合，增加第n个元素，则增加的连续元素子集数为n个。
            // 对于a[l] ... a[r - 1] 的集合，增加第r个元素a[r]，则增加的连续元素子集数为 a[l] ... a[r] 范围内的元素总数即 r - l +1个。

            right++;
        }

        return count;
    }
};

int main()
{
    Solution sol;

    // 测试用例 1: nums = {10, 5, 2, 6}, k = 100
    vector<int> nums1 = {10, 5, 2, 6};
    int k1 = 100;
    cout << "Test Case 1: " << sol.numSubarrayProductLessThanK(nums1, k1) << endl; // Expected: 8

    // 测试用例 2: nums = {1, 2, 3}, k = 0
    vector<int> nums2 = {1, 2, 3};
    int k2 = 0;
    cout << "Test Case 2: " << sol.numSubarrayProductLessThanK(nums2, k2) << endl; // Expected: 0

    // 测试用例 3: nums = {1, 2, 3, 4}, k = 10
    vector<int> nums3 = {1, 2, 3, 4};
    int k3 = 10;
    cout << "Test Case 3: " << sol.numSubarrayProductLessThanK(nums3, k3) << endl; // Expected: 7

    // 测试用例 4: nums = {1, 2, 3}, k = 6
    vector<int> nums4 = {1, 2, 3};
    int k4 = 6;
    cout << "Test Case 4: " << sol.numSubarrayProductLessThanK(nums4, k4) << endl; // Expected: 5

    // 测试用例 5: nums = {1, 1, 1, 1}, k = 4
    vector<int> nums5 = {1, 1, 1, 1};
    int k5 = 4;
    cout << "Test Case 5: " << sol.numSubarrayProductLessThanK(nums5, k5) << endl; // Expected: 10

    return 0;
}