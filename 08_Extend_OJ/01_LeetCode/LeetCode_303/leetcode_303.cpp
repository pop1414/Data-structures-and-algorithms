#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class NumArray
{
public:
    NumArray(vector<int> &nums)
    {
        int size = nums.size();
        // preSum[0]用来放0，是为了更好解决边界条件
        // 所有区间（包括以 0 为左边界的区间），都能用preSum[right + 1] - preSum[left] 计算
        // 所以preSum就需要容量就要比nums多一位
        preSum = vector<int>(size + 1, 0);
        for (int i = 1; i < size + 1; i++)
        {
            // preSum[i] = nums[0 ~ i - 1]
            preSum[i] = preSum[i - 1] + nums[i - 1];
        }
    }

    int sumRange(int left, int right)
    {
        int result = preSum[right + 1] - preSum[left];
        return result;
    }

private:
    vector<int> preSum;
};

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        FILE *fp = freopen(argv[1], "r", stdin);
        if (!fp)
        {
            exit(1);
        }
    }

    string line;
    getline(cin, line);
    // cin是从控制台读数据的水管
    // istringstream是从字符串里读数据的虚拟水管
    istringstream iss(line);

    int num;
    vector<int> nums;
    while (iss >> num)
    {
        nums.push_back(num);
    }

    int left, right;
    cin >> left >> right;

    for (int num : nums)
    {
        cout << num << " ";
    }
    cout << '\n';

    NumArray array = NumArray(nums);
    int result = array.sumRange(left, right);

    cout << result;
}