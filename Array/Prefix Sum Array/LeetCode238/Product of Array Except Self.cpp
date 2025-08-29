#include<bits/stdc++.h>
//前缀和变成前缀乘数组，因为不能使用除法，以避免除数为0的情况，引入后缀乘数组
//题目要求除了index的数字之外，数组元素乘积，index分为左右两侧，左侧为前缀，右侧为后缀
using namespace std;

class Solution {
public:
    vector<int>pre;
    vector<int>aft;
    vector<int>res;
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        build(nums, n);
        res.resize(n);
        for (int i = 0; i < n; i++){
            res[i] = pre[i] * aft[n - i - 1];//注意下标
        }
        return res;
    }
    void build(vector<int>& nums, int n){
        //大小为n的原因是，不需要整个数组所有元素的乘积，所以不需要求最后一个积
        pre.resize(n);
        aft.resize(n);
        //默认为1
        pre[0] = 1;
        aft[0] = 1;
        for (int i = 1; i < n; i++){
            pre[i] = pre[i - 1] * nums[i - 1];
            aft[i] = aft[i - 1] * nums[n - i];
        }
    }
};

// 打印工具
template <class T>
void printVec(const vector<T>& v){
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i){
        if (i) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

// 运行一组并打印期望
void run_case(vector<int> nums, vector<int> expected, const string& name){
    Solution sol;
    auto out = sol.productExceptSelf(nums);
    cout << name << ":\n";
    cout << "  nums      = "; printVec(nums); cout << "\n";
    cout << "  got       = "; printVec(out);  cout << "\n";
    cout << "  expected  = "; printVec(expected); cout << "\n";
    cout << ((out == expected) ? "  PASS ✅\n\n" : "  FAIL ❌\n\n");
}

int main(){
    // Case 1: 基础用例
    run_case({1,2,3,4}, {24,12,8,6}, "Case 1");

    // Case 2: 含一个 0
    // except self: [1*2*3=6, 0*2*3=0, 0*1*3=0, 0*1*2=0]
    run_case({0,1,2,3}, {6,0,0,0}, "Case 2");

    // Case 3: 含两个 0（全部为 0）
    run_case({0,0,2,3}, {0,0,0,0}, "Case 3");

    // Case 4: 有负数
    // 结果应为 [-1, 1, -1, 1]
    run_case({-1,1,-1,1}, {-1,1,-1,1}, "Case 4");

    // Case 5: 单元素（按题意为 1）
    run_case({5}, {1}, "Case 5");

    // Case 6: 稍大一点的数组
    // 总积 720 -> [360,240,180,144,120]
    run_case({2,3,4,5,6}, {360,240,180,144,120}, "Case 6");

    // 你也可以再补充更多随机用例对拍
    return 0;
}