
#include <bits/stdc++.h>

using namespace std;

// 给你一个 m x n 的矩阵 mat 和一个整数 k ，请你返回一个矩阵 answer ，其中每个 answer[i][j] 是所有满足下述条件的元素 mat[r][c] 的和：

// i - k <= r <= i + k,
// j - k <= c <= j + k 且
//(r, c) 在矩阵内。
// r，c对应的上下限就是row1, row2, col1, col2；所以就可套用二维矩阵前缀和解决问题，注意边界条件即可
class Solution
{
public:
    vector<vector<int>> perSum;
    vector<vector<int>> res;
    vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k)
    {
        int n = mat.size();
        int m = mat[0].size();
        int row1, col1, row2, col2;
        res.resize(n, vector<int>(m, 0)); //!!!res需要resize
        bulidperSum(mat, n, m);
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < m; c++)
            {

                if (r - k <= 0)
                {
                    row1 = 0;
                }
                else
                {
                    row1 = r - k;
                }

                if (c - k <= 0)
                {
                    col1 = 0;
                }
                else
                {
                    col1 = c - k;
                }

                if (r + k >= n)
                {
                    row2 = n - 1;
                }
                else
                {
                    row2 = r + k;
                }

                if (c + k >= m)
                {
                    col2 = m - 1;
                }
                else
                {
                    col2 = c + k;
                }

                res[r][c] = sumRegion(row1, col1, row2, col2);
            }
        }
        return res;
    }

    void bulidperSum(vector<vector<int>> &mat, int n, int m)
    {
        perSum.resize(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                perSum[i][j] = mat[i - 1][j - 1] + perSum[i - 1][j] + perSum[i][j - 1] - perSum[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        int r1 = row1 + 1;
        int r2 = row2 + 1;
        int c1 = col1 + 1;
        int c2 = col2 + 1;
        int res;
        res = perSum[r2][c2] - perSum[r2][c1 - 1] - perSum[r1 - 1][c2] + perSum[r1 - 1][c1 - 1];
        return res;
    }
};


/* -------------- 暴力对拍（校验正确性） -------------- */
vector<vector<int>> bruteBlockSum(const vector<vector<int>>& mat, int k) {
    int n = (int)mat.size(), m = (int)mat[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int r1 = max(0, r - k), r2 = min(n - 1, r + k);
            int c1 = max(0, c - k), c2 = min(m - 1, c + k);
            int sum = 0;
            for (int i = r1; i <= r2; i++)
                for (int j = c1; j <= c2; j++)
                    sum += mat[i][j];
            ans[r][c] = sum;
        }
    }
    return ans;
}

bool equalMat(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i)
        if (a[i] != b[i]) return false;
    return true;
}

void printMat(const vector<vector<int>>& v) {
    for (auto &row : v) {
        for (auto &x : row) cout << setw(4) << x << " ";
        cout << "\n";
    }
}

/* -------------- 测试用例集 -------------- */
void run_one(const vector<vector<int>>& mat, int k, const string& name) {
    cout << "==== " << name << "  (k = " << k << ") ====\n";
    Solution s;
    auto mat_copy = mat; // matrixBlockSum 按引用接收
    auto got = s.matrixBlockSum(mat_copy, k);
    auto expect = bruteBlockSum(mat, k);

    if (equalMat(got, expect)) {
        cout << "PASS ✅\n";
    } else {
        cout << "FAIL ❌\nGot:\n"; printMat(got);
        cout << "Expect:\n"; printMat(expect);
    }
    cout << "\n";
}

int main() {
    // 用例 1：经典 3x3，k = 1
    run_one({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    }, 1, "Case 1: 3x3");

    // 用例 2：LeetCode 常见 5x5，k = 2（非均匀）
    run_one({
        {3,0,1,4,2},
        {5,6,3,2,1},
        {1,2,0,1,5},
        {4,1,0,1,7},
        {1,0,3,0,5}
    }, 2, "Case 2: 5x5");

    // 用例 3：非方阵 2x4，k = 1（专门卡列界问题）
    run_one({
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    }, 1, "Case 3: 2x4 non-square");

    // 用例 4：k = 0（应等于原矩阵）
    run_one({
        {9, -1, 2},
        {0,  3, 4}
    }, 0, "Case 4: k=0 equals original");

    // 用例 5：1x1 矩阵，大 k（全覆盖）
    run_one({
        {42}
    }, 100, "Case 5: 1x1 big k");

    // 用例 6：随机对拍（多组随机，保证健壮性）
    std::mt19937 rng(123);
    for (int tc = 1; tc <= 5; ++tc) {
        int n = 1 + (rng() % 6);          // 1..6
        int m = 1 + (rng() % 6);          // 1..6
        int k = rng() % 5;                // 0..4
        vector<vector<int>> mat(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                mat[i][j] = (int)(rng()%21) - 10; // [-10, 10]

        run_one(mat, k, "Random Case " + to_string(tc));
    }

    return 0;
}