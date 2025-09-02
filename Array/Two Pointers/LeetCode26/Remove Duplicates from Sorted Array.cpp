#include <iostream>
#include <vector>


using namespace std;


class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        //slow用来写，fast用来读
        int slow = 0;
        for(int fast = 1; fast < nums.size(); fast++){
            //数组是非严格递增
            //当fast往后遍历发现有不同的时候，说明要新写入数字，slow++
            if(nums[slow] != nums[fast]){
                slow++;
                nums[slow] = nums[fast];
            }
        }
        return slow + 1;
    }
};

void printVec(const std::vector<int>& v, int k) {
    std::cout << "[";
    for (int i = 0; i < k; ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]";
}

int main() {
    Solution sol;

    // 简单测试用例
    std::vector<std::vector<int>> tests = {
        {},                     // 空数组
        {1},                    // 单元素
        {2,2,2,2},              // 全相同
        {1,1,2,2,3},            // 混合重复
        {1,2,3,4}               // 全不重复
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        std::vector<int> nums = tests[i]; // 复制一份
        int k = sol.removeDuplicates(nums);
        std::cout << "Case " << i+1 << ": returned k = " << k << ", result prefix = ";
        printVec(nums, k);
        std::cout << "\n";
    }

    return 0;
}

