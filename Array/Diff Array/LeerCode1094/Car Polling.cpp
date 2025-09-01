#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> diff = vector<int>(1001, 0);
    bool carPooling(vector<vector<int>> &trips, int capacity)
    {

        int val, left, right;

        int n = trips.size();
        for (int i = 0; i < n; i++)
        {
            val = trips[i][0];
            left = trips[i][1];
            right = trips[i][2];

            increment(left, right - 1, val); // 注意下标
        }

        return result(capacity);
    }
    void increment(int i, int j, int val)
    {
        diff[i] += val;
        diff[j + 1] -= val;
    }
    bool result(int capacity)
    {
        vector<int> res(diff.size());
        res[0] = diff[0];
        if (res[0] > capacity) // 记得比较res[0]
        {
            return false;
        }
        for (int i = 1; i < res.size(); i++)
        {
            res[i] = res[i - 1] + diff[i];
            if (res[i] > capacity)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution s, x, y, z;

    vector<vector<int>> trips1 = {{2, 1, 5}, {3, 3, 7}};
    cout << s.carPooling(trips1, 5) << endl; // 1

    vector<vector<int>> trips2 = {{2, 1, 5}, {3, 3, 7}};
    cout << x.carPooling(trips2, 4) << endl; // 0

    vector<vector<int>> trips3 = {{2, 1, 2}, {2, 2, 3}};
    cout << y.carPooling(trips3, 3) << endl; // 1

    vector<vector<int>> trips4 = {{3, 0, 1000}};
    cout << z.carPooling(trips4, 3) << endl; // 1
}
