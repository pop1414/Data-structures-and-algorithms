#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res(2);
        int left = 0;
        int right = numbers.size() - 1;
        while(left <= right){
            int sum = numbers[left] + numbers[right];
            if(sum == target){
                res[0]= left + 1;//题目要求下标从1开始
                res[1] = right + 1;
                return res;
            }
            else if(sum < target){
                left++;
            }
            else if(sum > target){
                right--;
            }
        }
        return res;
    }
};

void printVec(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) cout << ", ";
        cout << v[i];
    }
    cout << "]";
}

// 额外验证：数组里是否存在第二组解（用于确保“唯一解”）
bool hasAnotherSolution(const vector<int>& a, int target, const pair<int,int>& chosen) {
    int n = (int)a.size();
    int l = 0, r = n - 1;
    int found = 0;
    pair<int,int> firstPair = {-1, -1};
    while (l < r) {
        long long s = (long long)a[l] + a[r];
        if (s == target) {
            if (found == 0) {
                firstPair = {l, r};
            }
            ++found;
            // 为了继续探索是否还有其他组合，移动一侧（这里随意选移动左侧）
            ++l;
        } else if (s < target) {
            ++l;
        } else {
            --r;
        }
        if (found > 1) break;
    }
    // 检查：唯一找到的一组是否等于 chosen（chosen 是 0-based）
    if (found == 1) {
        return !(firstPair.first == chosen.first && firstPair.second == chosen.second);
    }
    return found > 1; // >1 说明确实有多解
}

int main() {
    Solution sol;

    // 每个用例: numbers, target, expected (1-based indices)
    struct Case { vector<int> nums; int target; vector<int> expect; };
    vector<Case> tests = {
        {{2,7,11,15}, 9, {1,2}},                     // 唯一：2+7
        {{1,4,5,8,12}, 13, {1,5}},                   // 唯一：1+12
        {{-5,-1,0,3,9}, 4, {1,5}},                   // 唯一：-5+9
        {{1,2,3,7,10}, 11, {1,5}},                   // 唯一：1+10（第二个1）
        {{3,3,4,5,9,14}, 18, {3,6}},                 // 唯一：4+14
        {{-10,-1,2,4,6,13}, 3, {1,6}}                // 唯一：-10+13
    };

    for (size_t i = 0; i < tests.size(); i++) {
        auto nums = tests[i].nums;
        int target = tests[i].target;
        auto expect = tests[i].expect;

        auto got = sol.twoSum(nums, target);

        cout << "Case " << i+1 << ":\n";
        cout << "  numbers = "; printVec(nums);
        cout << ", target = " << target << "\n";
        cout << "  Expected = "; printVec(expect);
        cout << "\n  Got      = "; printVec(got);

        // 基本正确性检查
        bool pass_basic = (got.size()==2 && got[0]==expect[0] && got[1]==expect[1]);

        // 唯一性检查（把 1-based 转 0-based）
        pair<int,int> chosen = {got[0]-1, got[1]-1};
        bool multi = hasAnotherSolution(nums, target, chosen);

        cout << "\n  Result   = " << (pass_basic ? "PASS" : "FAIL");
        cout << (multi ? " (But found another pair -> NOT UNIQUE)" : "");
        cout << "\n\n";
    }
    return 0;
}