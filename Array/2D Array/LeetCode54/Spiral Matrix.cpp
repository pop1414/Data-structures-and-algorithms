#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> res;
        int m = matrix.size();
        int n = matrix[0].size();

        int upper = 0;
        int lower = m - 1;
        int left = 0;
        int right = n - 1;

        int count = n * m;
        while (count > 0)
        {
            //左至右
            if (left <= right)
            {
                for (int j = left; j <= right; j++)
                {
                    // res.push_back(matrix[upper][j]);
                    cout << matrix[upper][j];
                    count--;
                }
                upper++;
            }
            //上至下
            if (upper <= lower)
            {
                for (int i = upper; i <= lower; i++)
                {
                    // res.push_back(matrix[i][right]);
                    cout << matrix[i][right];
                    count--;
                }
                right--;
            }
            //右至左
            if (upper <= lower)
            {
                for (int j = right; j >= left; j--)
                {
                    // res.push_back(matrix[lower][j]);
                    cout << matrix[lower][j];
                    count--;
                }
                lower--;
            }
            //下至上
            if (left <= right)
            {
                for (int i = lower; i >= upper; i--)
                {
                    // res.push_back(matrix[i][left]);
                    cout << matrix[i][left];
                    count--;
                }
                left++;
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> test = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    vector<int> res = s.spiralOrder(test);

    return 0;
}