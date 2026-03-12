#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class NumMatrix
{
public:
    NumMatrix(vector<vector<int>> &matrix)
    {
        int row = matrix.size();
        int col = matrix[0].size();

        preSum = vector<vector<int>>(row + 1, vector<int>(col + 1, 0));

        for (int i = 1; i < row + 1; i++)
        {
            for (int j = 1; j < col + 1; j++)
            {
                preSum[i][j] = preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        // 最大方块，row2, col2;preSum比原数组大，所以行与列都+1
        // 其余两个方块：
        // 1.行与row2同，列比col1少1，同理行为row2 + 1，列为col1 + 1 - 1
        // 2.行比row1少1，列与col2同，同理行为row1 + 1 - 1，列为col2 + 1
        // 最小方块，行与列都比row1，col1少1，同理为row1 + 1 - 1，col1 + 1- 1
        return preSum[row2 + 1][col2 + 1] - preSum[row2 + 1][col1] - preSum[row1][col2 + 1] + preSum[row1][col1];
    }

private:
    vector<vector<int>> preSum;
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

    int row, col;
    cin >> row >> col;
    // 忽略cin残留的换行符，否则getline会读空行
    cin.ignore();

    vector<vector<int>> matrix;
    string line;
    for (int i = 0; i < row; i++)
    {
        int num;
        vector<int> nums;
        getline(cin, line);
        istringstream iss(line);
        while (iss >> num)
        {
            nums.push_back(num);
        }
        matrix.push_back(nums);
    }

    int row1, col1, row2, col2;
    cin >> row1 >> col1 >> row2 >> col2;

    NumMatrix square(matrix);
    cout << square.sumRegion(row1, col1, row2, col2);
}