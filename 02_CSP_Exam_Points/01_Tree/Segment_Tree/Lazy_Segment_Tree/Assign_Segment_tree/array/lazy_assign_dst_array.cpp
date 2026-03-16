#include <iostream>
#include <vector>
#include <optional>
#include <functional>
#include <algorithm>
#include <cassert>
#include <random>
#include <climits>

using namespace std;

struct Node
{
    long long val = 0;
    optional<long long> lazy;
    int leftChildIdx = -1;
    int rightChildIdx = -1;
};

class LazyDST
{
private:
    vector<Node> tree;
    long long defaultVal;
    long long maxRange;
    function<long long(long long, long long)> merger;
    // 标记是否为求和模式，影响覆盖操作时的 val 计算
    bool isSumMode;

    int allocateNode()
    {
        Node newNode;
        // 不要忘记初始化
        newNode.val = defaultVal;
        tree.push_back(newNode);
        return tree.size() - 1;
    }

    void pushDown(int rootIndex, long long L, long long R)
    {
        if (!tree[rootIndex].lazy.has_value())
        {
            return;
        }

        long long lazyVal = tree[rootIndex].lazy.value();

        if (tree[rootIndex].leftChildIdx == -1)
        {
            int newIndex = allocateNode();
            tree[rootIndex].leftChildIdx = newIndex;
        }
        if (tree[rootIndex].rightChildIdx == -1)
        {

            int newIndex = allocateNode();
            tree[rootIndex].rightChildIdx = newIndex;
        }

        int leftChild = tree[rootIndex].leftChildIdx;
        int rightChild = tree[rootIndex].rightChildIdx;

        long long mid = L + (R - L) / 2;
        long long leftLength = mid - L + 1;
        long long rightLength = R - (mid + 1) + 1;

        tree[leftChild].lazy = lazyVal;
        tree[rightChild].lazy = lazyVal;

        if (isSumMode)
        {
            // 如果是求和
            tree[leftChild].val = leftLength * lazyVal;
            tree[rightChild].val = rightLength * lazyVal;
        }
        else
        {
            // 如果是求最值
            tree[leftChild].val = lazyVal;
            tree[rightChild].val = lazyVal;
        }

        tree[rootIndex]
            .lazy.reset();
    }

    void update(long long L, long long R, int rootIndex, long long uL, long long uR, long long value)
    {
        if (L > uR || R < uL)
        {
            return;
        }

        if (L >= uL && R <= uR)
        {
            tree[rootIndex].lazy = value;
            if (isSumMode)
            {
                long long length = R - L + 1;
                tree[rootIndex].val = length * value;
            }
            else
            {
                tree[rootIndex].val = value;
            }
            return;
        }

        pushDown(rootIndex, L, R);

        long long mid = L + (R - L) / 2;

        if (uL <= mid)
        {
            // 往下递归前要确保节点存在
            if (tree[rootIndex].leftChildIdx == -1)
            {
                int newID = allocateNode();
                tree[rootIndex].leftChildIdx = newID;
            }
            update(L, mid, tree[rootIndex].leftChildIdx, uL, uR, value);
        }
        if (mid < uR)
        {
            if (tree[rootIndex].rightChildIdx == -1)
            {
                int newID = allocateNode();
                tree[rootIndex].rightChildIdx = newID;
            }
            update(mid + 1, R, tree[rootIndex].rightChildIdx, uL, uR, value);
        }

        long long leftChild = (tree[rootIndex].leftChildIdx != -1) ? tree[tree[rootIndex].leftChildIdx].val : defaultVal;

        long long rightChild = (tree[rootIndex].rightChildIdx != -1) ? tree[tree[rootIndex].rightChildIdx].val : defaultVal;
        // 递归后回溯到该节点后要更新值
        tree[rootIndex].val = merger(leftChild, rightChild);
    }

    long long query(long long L, long long R, int rootIndex, long long qL, long long qR)
    {
        if (L > qR || R < qL || rootIndex == -1)
        {
            return defaultVal;
        }

        if (L >= qL && R <= qR)
        {
            return tree[rootIndex].val;
        }

        pushDown(rootIndex, L, R);

        long long mid = L + (R - L) / 2;

        long long leftChild = query(L, mid, tree[rootIndex].leftChildIdx, qL, qR);
        long long rightChild = query(mid + 1, R, tree[rootIndex].rightChildIdx, qL, qR);

        return merger(leftChild, rightChild);
    }

public:
    LazyDST(long long max_range, function<long long(long long, long long)> mergeFunc, long long def_val, bool is_sum_mode) : maxRange(max_range), merger(mergeFunc), defaultVal(def_val), isSumMode(is_sum_mode)
    {
        tree.reserve(100000);
        allocateNode();
    }

    void update(long long uL, long long uR, long long value)
    {
        update(0, maxRange, 0, uL, uR, value);
    }
    long long query(long long qL, long long qR)
    {
        return query(0, maxRange, 0, qL, qR);
    }
};

// ==================== 测试用例部分 ====================

// 1. 测试：区间覆盖，区间求和
void test_range_sum()
{
    cout << "[TEST] Running Range Sum Test..." << endl;
    LazyDST sumTree(1e9, [](long long a, long long b)
                    { return a + b; }, 0, true);

    // [10, 20] 赋值为 5 -> sum = 11 * 5 = 55
    sumTree.update(10, 20, 5);
    assert(sumTree.query(10, 20) == 55);

    // 查询 [15, 25] -> [15, 20]为5(长6), [21, 25]为0 -> sum = 30
    assert(sumTree.query(15, 25) == 30);

    //[15, 25] 覆盖为 10
    sumTree.update(15, 25, 10);

    // 此时 [10, 14]为5(长5, sum=25), [15, 20]被覆盖为10(长6, sum=60), sum = 85
    assert(sumTree.query(10, 20) == 85);
    // [15, 25] (长11) -> 110
    assert(sumTree.query(15, 25) == 110);
    cout << "  -> Passed!" << endl;
}

// 2. 测试：区间覆盖，区间求最大值
void test_range_max()
{
    cout << "[TEST] Running Range Max Test..." << endl;
    const long long MIN_INF = LLONG_MIN; // 修正：使用标准常量
    LazyDST maxTree(1e9, [](long long a, long long b)
                    { return max(a, b); }, MIN_INF, false);

    // 初始化时整个区间都应该是 MIN_INF
    assert(maxTree.query(1, 100) == MIN_INF);

    // [10, 20] 赋值为 5
    maxTree.update(10, 20, 5);
    assert(maxTree.query(10, 20) == 5);
    assert(maxTree.query(1, 15) == 5); // 包含 [10, 15] 的 5，其余是 MIN_INF

    //[15, 25] 赋值为 100
    maxTree.update(15, 25, 100);
    // [10, 14]依然是5，[15, 25]是100
    assert(maxTree.query(10, 14) == 5);
    assert(maxTree.query(10, 30) == 100);
    cout << "  -> Passed!" << endl;
}

// 3. 动态开点超大坐标测试（验证不崩溃、不OOM）
void test_large_coordinates()
{
    cout << "[TEST] Running Large Coordinates Test..." << endl;
    long long MAX_COORD = 1e14; // 100万亿级别的坐标
    LazyDST largeTree(MAX_COORD, [](long long a, long long b)
                      { return a + b; }, 0, true);

    largeTree.update(MAX_COORD - 100, MAX_COORD, 7);
    assert(largeTree.query(MAX_COORD - 100, MAX_COORD) == 101 * 7);
    assert(largeTree.query(MAX_COORD - 50, MAX_COORD + 50) == 51 * 7); // 越界部分自动返回0
    cout << "  -> Passed!" << endl;
}

// 4. 对拍测试 (Stress Test)
// 随机生成大量操作，比较 线段树(DST) 和 暴力数组(Brute Force) 的输出
void test_stress()
{
    cout << "[TEST] Running Stress Test (Compare with Brute Force)..." << endl;

    const int N = 2000;
    const int OPS = 5000;

    // 创建普通数组作为对拍参照物，初始全为0
    vector<long long> brute_force_arr(N + 1, 0);

    // 创建三个线段树，分别测试求和、求最大值、求最小值
    LazyDST dstSum(N, [](long long a, long long b)
                   { return a + b; }, 0, true);
    LazyDST dstMax(N, [](long long a, long long b)
                   { return max(a, b); }, LLONG_MIN, false);
    LazyDST dstMin(N, [](long long a, long long b)
                   { return min(a, b); }, LLONG_MAX, false);

    // 关键修正：初始化线段树，将整个区间[0,N]覆盖为0，和暴力数组对齐
    dstSum.update(0, N, 0);
    dstMax.update(0, N, 0);
    dstMin.update(0, N, 0);

    mt19937_64 rng(1337); // 固定随机种子以便复现

    for (int i = 0; i < OPS; ++i)
    {
        int op = rng() % 2;
        int L = rng() % N;
        int R = rng() % N;
        if (L > R)
            swap(L, R);

        if (op == 0)
        {
            // Update: 区间覆盖 (设置一个正数)
            long long val = (rng() % 1000) + 1;

            // 1. 更新暴力数组
            for (int j = L; j <= R; ++j)
            {
                brute_force_arr[j] = val;
            }

            // 2. 更新三个线段树
            dstSum.update(L, R, val);
            dstMax.update(L, R, val);
            dstMin.update(L, R, val);
        }
        else
        {
            // Query: 区间查询验证

            // 1. 暴力求解当前区间的值
            long long bf_sum = 0;
            long long bf_max = LLONG_MIN; // 修正：初始化为最小
            long long bf_min = LLONG_MAX; // 修正：初始化为最大

            for (int j = L; j <= R; ++j)
            {
                bf_sum += brute_force_arr[j];
                bf_max = max(bf_max, brute_force_arr[j]);
                bf_min = min(bf_min, brute_force_arr[j]);
            }

            // 2. 线段树查询
            long long tree_sum = dstSum.query(L, R);
            long long tree_max = dstMax.query(L, R);
            long long tree_min = dstMin.query(L, R);

            // 3. 断言校验
            if (bf_sum != tree_sum)
            {
                cout << "SUM Error! BF:" << bf_sum << " Tree:" << tree_sum << " Range:[" << L << "," << R << "]\n";
                assert(false);
            }
            if (bf_max != tree_max)
            {
                cout << "MAX Error! BF:" << bf_max << " Tree:" << tree_max << " Range:[" << L << "," << R << "]\n";
                assert(false);
            }
            if (bf_min != tree_min)
            {
                cout << "MIN Error! BF:" << bf_min << " Tree:" << tree_min << " Range:[" << L << "," << R << "]\n";
                assert(false);
            }
        }
    }
    cout << "  -> Stress Test Passed! (" << OPS << " random operations fully matched)" << endl;
}

int main()
{
    cout << "=======================================" << endl;
    cout << "   Starting Dynamic Segment Tree Tests" << endl;
    cout << "=======================================" << endl;

    test_range_sum();
    test_range_max();
    test_large_coordinates();
    test_stress();

    cout << "=======================================" << endl;
    cout << "   ALL TESTS PASSED SUCCESSFULLY! 🚀" << endl;
    cout << "=======================================" << endl;

    class NumArray {
public:
    NumArray(vector<int>& nums) : dst(nums.size() - 1, [](long long a, long long b) {return a + b;}, 0, true){
        for(int i = 0; i < nums.size() - 1; i++){
            dst.update(i, i, nums[i]);
        }
    }
    
    void update(int index, int val) {
        dst.update(index, index, val);
    }
    
    int sumRange(int left, int right) {
        return dst.query(left, right);
    }
private:
    LazyDST dst;
};

    return 0;
}