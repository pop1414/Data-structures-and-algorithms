#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
       vector<int>diff(n, 0);
       increment(bookings, diff);
       vector<int> res(n);
       res[0] = diff[0];
        for (int i = 1 ; i < n; i++){
            res[i] = res[i - 1] + diff[i];
        }
       return res;
     
    }
    void increment(vector<vector<int>>& bookings, vector<int>& diff){
        int m = bookings.size();
        for (int i = 0; i < m; i++){
            int left = bookings[i][0] - 1;
            int right = bookings[i][1] - 1;
            int val = bookings[i][2];
            diff[left] += val;
            if (right + 1 < diff.size()){
                diff[right + 1] -=val;
            }
        }
    }
};

/* ---------- 工具 ---------- */
template <class T>
void printVec(const vector<T>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

void run_case(vector<vector<int>> bookings, int n, vector<int> expected, const string& name) {
    Solution s;
    auto got = s.corpFlightBookings(bookings, n);
    cout << name << ":\n";
    cout << "  bookings = ";
    for (auto &b : bookings) { cout << "("<<b[0]<<","<<b[1]<<","<<b[2]<<") "; }
    cout << "\n  n        = " << n << "\n";
    cout << "  got      = "; printVec(got); cout << "\n";
    cout << "  expected = "; printVec(expected); cout << "\n";
    cout << ((got == expected) ? "  PASS ✅\n\n" : "  FAIL ❌\n\n");
}

int main() {
    // Case 1: 官方样例
    // bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
    // 结果: [10,55,45,25,25]
    run_case({{1,2,10},{2,3,20},{2,5,25}}, 5, {10,55,45,25,25}, "Case 1: LC sample");

    // Case 2: 单次覆盖整个区间
    // [1,5,7] -> [7,7,7,7,7]
    run_case({{1,5,7}}, 5, {7,7,7,7,7}, "Case 2: full range");

    // Case 3: 只在末尾单点
    // [5,5,3] -> [0,0,0,0,3]
    run_case({{5,5,3}}, 5, {0,0,0,0,3}, "Case 3: tail point");

    // Case 4: 边界 + 重叠
    // [1,1,2], [1,2,1], [2,3,2] -> [3,3,2]
    run_case({{1,1,2},{1,2,1},{2,3,2}}, 3, {3,3,2}, "Case 4: overlaps & edges");

    // Case 5: 多次叠加
    // n=6
    // [1,3,5], [2,5,2], [3,6,1]
    // 结果：
    // idx: 1  2  3  4  5  6
    // val: 5  7  8  3  3  1
    run_case({{1,3,5},{2,5,2},{3,6,1}}, 6, {5,7,8,3,3,1}, "Case 5: multiple");

    return 0;
}