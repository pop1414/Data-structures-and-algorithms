#include <bits/stdc++.h>
using namespace std;
// 对于元素不变的数组，在原数组的基础上用O(N)的时间遍历数组，创建一个前缀数组preSum。
// example： nums：3，5，2，-2，4，1
//           preSum：0，3，8，10，8，12，13
// 注意preSum数组比原数组多一位，因为preSum[i] 记录 nums[0..i-1] 的累加和，preSum[0]默认为0
// 若想求原数组某个区间的和，例如i->j，只需用preSum[j + 1] - preSum[i]
class NumArray
{
public:
    vector<int> PreSum;
    NumArray(vector<int> &nums)
    {
        int size = nums.size();
        PreSum.resize(size + 1);
        PreSum[0] = 0; // 默认为0
        for (int i = 1; i < PreSum.size(); i++)
        {
            PreSum[i] = PreSum[i - 1] + nums[i - 1]; // ！！！
        }
    }

    int sumRange(int left, int right)
    {
        int res = 0;
        res = PreSum[right + 1] - PreSum[left]; // ！！！
        return res;
    }
};

int main()
{
    // 测试样例1：基本功能测试
    cout << "=== 测试样例1：基本功能 ===" << endl;
    vector<int> nums1 = {-2, 0, 3, -5, 2, -1};
    NumArray *numArray1 = new NumArray(nums1);
    cout << "数组: [-2, 0, 3, -5, 2, -1]" << endl;
    cout << "sumRange(0, 2): " << numArray1->sumRange(0, 2) << " (期望: 1)" << endl;
    cout << "sumRange(2, 5): " << numArray1->sumRange(2, 5) << " (期望: -1)" << endl;
    cout << "sumRange(0, 5): " << numArray1->sumRange(0, 5) << " (期望: -3)" << endl;
    delete numArray1;
    cout << endl;

    // 测试样例2：单个元素
    cout << "=== 测试样例2：单个元素 ===" << endl;
    vector<int> nums2 = {5};
    NumArray *numArray2 = new NumArray(nums2);
    cout << "数组: [5]" << endl;
    cout << "sumRange(0, 0): " << numArray2->sumRange(0, 0) << " (期望: 5)" << endl;
    delete numArray2;
    cout << endl;

    // 测试样例3：全为正数
    cout << "=== 测试样例3：全为正数 ===" << endl;
    vector<int> nums3 = {1, 2, 3, 4, 5};
    NumArray *numArray3 = new NumArray(nums3);
    cout << "数组: [1, 2, 3, 4, 5]" << endl;
    cout << "sumRange(1, 3): " << numArray3->sumRange(1, 3) << " (期望: 9)" << endl;
    cout << "sumRange(0, 4): " << numArray3->sumRange(0, 4) << " (期望: 15)" << endl;
    cout << "sumRange(2, 2): " << numArray3->sumRange(2, 2) << " (期望: 3)" << endl;
    delete numArray3;
    cout << endl;

    // 测试样例4：全为负数
    cout << "=== 测试样例4：全为负数 ===" << endl;
    vector<int> nums4 = {-1, -3, -2, -4};
    NumArray *numArray4 = new NumArray(nums4);
    cout << "数组: [-1, -3, -2, -4]" << endl;
    cout << "sumRange(0, 1): " << numArray4->sumRange(0, 1) << " (期望: -4)" << endl;
    cout << "sumRange(1, 3): " << numArray4->sumRange(1, 3) << " (期望: -9)" << endl;
    cout << "sumRange(2, 3): " << numArray4->sumRange(2, 3) << " (期望: -6)" << endl;
    delete numArray4;
    cout << endl;

    // 测试样例5：包含零的数组
    cout << "=== 测试样例5：包含零 ===" << endl;
    vector<int> nums5 = {0, 0, 0, 1, 2};
    NumArray *numArray5 = new NumArray(nums5);
    cout << "数组: [0, 0, 0, 1, 2]" << endl;
    cout << "sumRange(0, 2): " << numArray5->sumRange(0, 2) << " (期望: 0)" << endl;
    cout << "sumRange(3, 4): " << numArray5->sumRange(3, 4) << " (期望: 3)" << endl;
    cout << "sumRange(0, 4): " << numArray5->sumRange(0, 4) << " (期望: 3)" << endl;
    delete numArray5;
    cout << endl;

    // 测试样例6：边界测试
    cout << "=== 测试样例6：边界测试 ===" << endl;
    vector<int> nums6 = {10, -5, 3, 8, -2};
    NumArray *numArray6 = new NumArray(nums6);
    cout << "数组: [10, -5, 3, 8, -2]" << endl;
    cout << "sumRange(0, 0): " << numArray6->sumRange(0, 0) << " (期望: 10)" << endl;
    cout << "sumRange(4, 4): " << numArray6->sumRange(4, 4) << " (期望: -2)" << endl;
    cout << "sumRange(1, 2): " << numArray6->sumRange(1, 2) << " (期望: -2)" << endl;
    delete numArray6;

    return 0;
}