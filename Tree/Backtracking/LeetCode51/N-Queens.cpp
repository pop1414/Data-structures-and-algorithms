#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<string>> res;
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<int>> borad(n, vector<int>(n, 0));
        vector<int> cnt(n, 0); // 从上往下遍历，记录第几列有queen
        backtrace(0, borad, cnt, n);

        return res;
    }

    void backtrace(int row, vector<vector<int>> &borad, vector<int> &cnt, int n)
    {
        if (row == n)
        {
            transform(borad);
            return;
        }

        for (int j = 0; j < n; j++)
        {
            if (borad[row][j] == 0)
            {
                if (isvalid(borad, cnt, row, j))
                {
                    cnt[j] = 1;
                    borad[row][j] = 1;
                    backtrace(row + 1, borad, cnt, n);
                    cnt[j] = 0;
                    borad[row][j] = 0;
                }
            }
        }
        return; // 每一列都没有合法位置，那只能回溯上一行
    }

    bool isvalid(vector<vector<int>> &borad, vector<int> &cnt, int row, int col)
    {
        int n = borad.size();
        if (cnt[col] == 1)
        {
            return false;
        }

        // 左上
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (borad[i][j] == 1)
            {
                return false;
            }
        }

        // 右上
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        {
            if (borad[i][j] == 1)
            {
                return false;
            }
        }
        // 无下，是因为往下遍历，下方必没有queen
        return true;
    }

    void transform(vector<vector<int>> &borad)
    {
        int n = borad.size();
        vector<string> temp(n, string(n, '.')); // 这样初始化字符串数组
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (borad[i][j] == 1)
                {
                    temp[i][j] = 'Q';
                    break;
                }
            }
        }
        res.push_back(temp);
    }
};