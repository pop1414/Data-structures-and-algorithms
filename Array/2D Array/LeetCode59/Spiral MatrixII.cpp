#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
        int count = n * n;
        int number = 1;
        vector<vector<int>> res(n, vector<int>(n));
        int upper = 0;
        int left = 0;
        int lower = n - 1;
        int right = n - 1;

        while (count > 0)
        {

            if (left <= right)
            {
                for (int j = left; j <= right; j++)
                {
                    cout << number;
                    res[upper][j] = number++;

                    count--;
                }
            }
            upper++;

            if (upper <= lower)
            {
                for (int i = upper; i <= lower; i++)
                {
                    cout << number;
                    res[i][right] = number++;
                    count--;
                }
            }
            right--;

            if (left <= right)
            {
                for (int j = right; j >= left; j--)
                {
                    cout << number;
                    res[lower][j] = number++;
                    count--;
                }
            }
            lower--;

            if (upper <= lower)
            {
                for (int i = lower; i >= upper; i--)
                {
                    cout << number;
                    res[i][left] = number++;
                    count--;
                }
            }
            left++;
        }
        return res;
    }
};

int main()
{
    Solution s;
    s.generateMatrix(3);

    return 0;
}