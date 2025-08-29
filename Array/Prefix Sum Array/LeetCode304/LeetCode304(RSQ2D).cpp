#include <bits/stdc++.h>

// 二维数组的前缀和数组，在操作上最好要多加一圈外围0，且在构建前缀和数组的时候，因为二维的特性，要多减去一次，上行左列的重复部分：perSum[i - 1][j - 1]
// 多加一层外围0，则构建的时候ij要从1开始且，边界要注意<=n,m；ij访问matrix的时候要注意matrix[i - 1][j - 1]
// 反解原矩阵的左上角为 (x1, y1)，右下角为 (x2, y2) 的子矩阵的和，公式为sum = S[x2][y2]- S[x1-1][y2] - S[x2][y1-1] + S[x1-1][y1-1]  （要注意外围0的下标）

using namespace std;
class NumMatrix
{
public:
    vector<vector<int>> preSum;
    NumMatrix(vector<vector<int>> &matrix)
    {
        int row = matrix.size();
        int col = matrix[0].size();
        preSum.resize(row + 1, vector<int>(col + 1, 0)); // 扩大范围就不需要过多考虑边界范围
        for (int i = 1; i <= row; i++)
        {
            for (int j = 1; j <= col; j++)
            {
                preSum[i][j] = matrix[i - 1][j - 1] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        int preRow1 = row1 + 1;
        int preRow2 = row2 + 1;
        int precol1 = col1 + 1;
        int precol2 = col2 + 1;
        int res;
        res = preSum[preRow2][precol2] - preSum[preRow2][precol1 - 1] - preSum[preRow1 - 1][precol2] + preSum[preRow1 - 1][precol1 - 1];
        return res;
    }
};

int main()
{
    vector<vector<int>> mat = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };

    NumMatrix nm(mat);

    cout << "sumRegion(2,1,4,3) = " << nm.sumRegion(2, 1, 4, 3) << endl; // 8
    cout << "sumRegion(1,1,2,2) = " << nm.sumRegion(1, 1, 2, 2) << endl; // 11
    cout << "sumRegion(1,2,2,4) = " << nm.sumRegion(1, 2, 2, 4) << endl; // 12
    cout << "sumRegion(0,0,4,4) = " << nm.sumRegion(0, 0, 4, 4) << endl; // 58
    cout << "sumRegion(3,3,4,4) = " << nm.sumRegion(3, 3, 4, 4) << endl; // 13

    return 0;
}