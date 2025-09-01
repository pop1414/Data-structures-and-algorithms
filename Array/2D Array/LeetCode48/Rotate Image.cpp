#include<bits/stdc++.h>

using namespace std;

//顺时针90°：转置 + 水平镜像
//逆时针90°：转置 + 垂直镜像
//180°：水平镜像 + 垂直镜像

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        //题目默认n x n
        int n = matrix.size();
        transpose(matrix, n);
        matrixReverse(matrix, n);
    }

    void transpose(vector<vector<int>>& matrix, int n){
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){//j = i + 1，可以跳过对角线的情况，只遍历上三角
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
    }

    void matrixReverse(vector<vector<int>>& matrix, int n){
        for (int i = 0; i < n; i++){
            for(int j = 0; j < n / 2; j++){//水平镜像
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][n - 1 - j];
                matrix[i][n - 1 - j] = temp;
            }
        }
    }
};

int main() {
    Solution sol;

    vector<vector<vector<int>>> tests = {
        {{1,2},{3,4}},
        {{1,2,3},{4,5,6},{7,8,9}},
        {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}},
        {{42}},
        {{-1,-2},{-3,-4}}
    };

    for (int t = 0; t < tests.size(); t++) {
        cout << "样例 " << t+1 << " 输入矩阵:\n";
        for (auto &row : tests[t]) {
            for (auto &x : row) cout << x << " ";
            cout << "\n";
        }
        sol.rotate(tests[t]);
        cout << "旋转后矩阵:\n";
        for (auto &row : tests[t]) {
            for (auto &x : row) cout << x << " ";
            cout << "\n";
        }
        cout << "-----------------\n";
    }
    return 0;
}

