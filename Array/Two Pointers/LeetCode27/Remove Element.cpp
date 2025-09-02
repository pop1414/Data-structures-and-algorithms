#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        if(nums.empty()){
            return 0;
        }
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++)
        {
            // fast扫描到不是val的数值，其实就是修改完后数组中的数字，然后用slow来写
            if (nums[fast] != val)
            {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};

void printVec(const vector<int> &v, int k)
{
    cout << "[";
    for (int i = 0; i < k; i++)
    {
        if (i)
            cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

int main()
{
    Solution sol;

    vector<pair<vector<int>, int>> tests = {
        {{}, 1},
        {{1, 2, 3}, 4},
        {{2, 2, 2}, 2},
        {{3, 3, 1, 2}, 3},
        {{0, 1, 2, 2, 3, 4}, 2},
        {{1, 2, 3, 3}, 3},
        {{1, 2, 2, 3, 4, 2, 5}, 2}};

    for (size_t i = 0; i < tests.size(); i++)
    {
        vector<int> nums = tests[i].first;
        int val = tests[i].second;
        int k = sol.removeElement(nums, val);
        cout << "Case " << i + 1
             << ": val = " << val
             << ", k = " << k
             << ", result = ";
        printVec(nums, k);
        cout << "\n";
    }
}