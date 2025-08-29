#include <bits/stdc++.h>

using namespace std;

class Difference
{
private:
    vector<int> diff;

public:
    Difference(vector<int> &nums)
    {
        int n = nums.size();
        diff.resize(n);
        diff[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            diff[i] = nums[i] - nums[i - 1];
        }
    }

    void increment(int i, int j, int val)
    {
        diff[i] += val;
        if (j + 1 < diff.size())
            diff[j + 1] -= val;
    }

    vector<int> result(){
        vector<int> res(diff.size());
        res[0] = diff[0];
        for (int i = 1; i < diff.size(); i++){
            res[i] = diff[i] + res[i - 1];
        }
        return res;
    }

};

// 工具函数：打印数组
void printVec(const vector<int>& v){
    cout << "[";
    for (size_t i = 0; i < v.size(); i++){
        if (i) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

// 测试一组
void run_case(vector<int> nums, vector<tuple<int,int,int>> ops, vector<int> expected, string name){
    Difference d(nums);
    for (auto &op : ops){
        int i,j,val;
        tie(i,j,val) = op;
        d.increment(i,j,val);
    }
    auto res = d.result();
    cout << name << ":\n";
    cout << "  Original  = "; printVec(nums); cout << "\n";
    cout << "  Operations= ";
    for (auto &op: ops) {
        int i,j,val;
        tie(i,j,val) = op;
        cout << "(i="<<i<<", j="<<j<<", +"<<val<<") ";
    }
    cout << "\n";
    cout << "  Result    = "; printVec(res); cout << "\n";
    cout << "  Expected  = "; printVec(expected); cout << "\n";
    cout << ((res==expected) ? "  PASS ✅\n\n":"  FAIL ❌\n\n");
}

int main(){
    // Case 1: 单次区间更新
    run_case({1,2,3,4,5}, {{1,3,2}}, {1,4,5,6,5}, "Case 1");

    // Case 2: 多次区间更新叠加
    // 先 [1,3]+2 -> [1,4,5,6,5]
    // 再 [0,2]+1 -> [2,5,6,6,5]
    run_case({1,2,3,4,5}, {{1,3,2},{0,2,1}}, {2,5,6,6,5}, "Case 2");

    // Case 3: 边界更新（更新最后一个元素）
    run_case({0,0,0,0}, {{3,3,5}}, {0,0,0,5}, "Case 3");

    // Case 4: 整段更新
    run_case({10,10,10}, {{0,2,-3}}, {7,7,7}, "Case 4");

    return 0;
}