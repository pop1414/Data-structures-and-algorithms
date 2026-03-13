#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

using namespace std;

struct Node
{
    int val = 0;
    int leftChildIdx = -1;
    int rightChildIdx = -1;
};

class DynamicSegmentTree
{
    /**private:
    // 私有成员变量（动态版核心：节点池）

    // 预估最大节点数
    const int MAX_NODE = 1e5;
    // nodeL[nodeID] = 节点的左区间l
    vector<int> nodeL;
    // nodeR[nodeID] = 节点的右区间r
    vector<int> nodeR;
    // 对应基础版的tree数组
    vector<int> mergeVal;
    // leftChildIdx[nodeID] = 左子节点的ID(-1 = 无)
    vector<int> leftChildIdx;
    vector<int> rightChildIdx;
    // 下一个可用节点的ID(初始 = 1)
    int nextNodeID;

    function<int(int, int)> merger;
    // 节点默认值，求和=0;最大值=-∞
    int defaultValue;
    int rootID;

    // 私有函数

    // 基础版build是批量创建所有节点，动态版allocNode是单个创建需要的节点
    int allocNode(int l, int r, int val)
    {
        if (nextNodeID > MAX_NODE)
        {
            throw overflow_error("节点池已满！");
        }

        // 获取当前可用ID，指针后移
        int nodeID = nextNodeID++;
        // 初始化该节点所有属性值
        nodeL[nodeID] = l;
        nodeR[nodeID] = r;
        mergeVal[nodeID] = val;
        leftChildIdx[nodeID] = -1;
        rightChildIdx[nodeID] = -1;

        return nodeID;
    }
    void initChildrenNeeded(int nodeID);
    void update(int nodeID, int index, int value);
    int query(int nodeID, int qL, int qR);

public:
    DynamicSegmentTree(int start, int end, function<int(int, int)> mergeFunc, int defaultVal);
    void update(int index, int value);
    int query(int qL, int qR);
    */
private:
    // 根节点从0开始
    vector<Node> tree;
    long long maxRange;
    function<int(int, int)> merger;

    // 单位元，求和单位元为0，Max单位元为极小值，Min单位元为极大值
    int defaultVal;

    int allocateNode()
    {
        Node newNode;
        newNode.val = defaultVal;
        tree.push_back(newNode);
        return tree.size() - 1;
    }

    // L，R当前节点表示的理论区间范围
    // rootIndex：当前节点在tree数组下的真实下标
    // index：我们要修改的原数组下标
    void update(long long L, long long R, int rootIndex, long long index, int value)
    {
        if (L == R)
        {
            tree[rootIndex].val = value;
            return;
        }

        long long mid = L + (R - L) / 2;
        if (index <= mid)
        {
            if (tree[rootIndex].leftChildIdx == -1)
            {
                tree[rootIndex].leftChildIdx = allocateNode();
            }

            update(L, mid, tree[rootIndex].leftChildIdx, index, value);
        }
        else
        {
            if (tree[rootIndex].rightChildIdx == -1)
            {
                tree[rootIndex].rightChildIdx = allocateNode();
            }

            update(mid + 1, R, tree[rootIndex].rightChildIdx, index, value);
        }

        // 左孩子是否存在？存在->返回左孩子的val : 不存在->返回0
        int leftVal = (tree[rootIndex].leftChildIdx != -1) ? tree[tree[rootIndex].leftChildIdx].val : defaultVal;
        int rightVal = (tree[rootIndex].rightChildIdx != -1) ? tree[tree[rootIndex].rightChildIdx].val : defaultVal;

        tree[rootIndex].val = merger(leftVal, rightVal);
    }

    // L,R当前节点代表的理论区间范围
    // rootIndex
    // qL，qR实际要查询的区间
    int query(long long L, long long R, int rootIndex, long long qL, long long qR)
    {
        if (rootIndex == -1)
        {
            return defaultVal;
        }

        if (qL == L && qR == R)
        {
            return tree[rootIndex].val;
        }

        long long mid = L + (R - L) / 2;
        if (qR <= mid)
        {
            return query(L, mid, tree[rootIndex].leftChildIdx, qL, qR);
        }
        else if (qL > mid)
        {
            return query(mid + 1, R, tree[rootIndex].rightChildIdx, qL, qR);
        }
        else
        {
            int leftVal = query(L, mid, tree[rootIndex].leftChildIdx, qL, mid);
            int rightVal = query(mid + 1, R, tree[rootIndex].rightChildIdx, mid + 1, qR);

            return merger(leftVal, rightVal);
        }
    }

public:
    DynamicSegmentTree(long long max_range, function<int(int, int)> mergeFunc, int def_val) : maxRange(max_range), merger(mergeFunc), defaultVal(def_val)
    {
        tree.reserve(100000);
        // 预先分配根节点
        allocateNode();
    }
    // 对外接口
    void update(long long index, int val)
    {
        if (index < 0 || index > maxRange)
            return;
        update(0, maxRange, 0, index, val);
    }

    int query(long long qL, long long qR)
    {
        if (qL < 0 || qR > maxRange || qL > qR)
        {
            throw invalid_argument("Invalid query range!");
        }
        return query(0, maxRange, 0, qL, qR);
    }
};

#define EXPECT_EQ(actual, expected, test_name)                                   \
    do                                                                           \
    {                                                                            \
        if ((actual) == (expected))                                              \
        {                                                                        \
            std::cout << "[PASS] " << test_name << std::endl;                    \
        }                                                                        \
        else                                                                     \
        {                                                                        \
            std::cout << "[FAIL] " << test_name << " | Expected: " << (expected) \
                      << ", Actual: " << (actual) << std::endl;                  \
        }                                                                        \
    } while (0)

void runAllTests()
{
    long long MAX_N = 1e9; // 10^9 的超大区间
    // 初始化线段树，聚合函数为求和
    DynamicSegmentTree st(MAX_N, [](int a, int b)
                          { return a + b; }, 0);

    std::cout << "========== 1. 基础功能测试 (Basic) ==========" << std::endl;
    st.update(10, 50);
    st.update(20, 100);
    EXPECT_EQ(st.query(0, 30), 150, "查询包含所有更新点的区间");
    EXPECT_EQ(st.query(15, 25), 100, "查询只包含部分更新点的区间");
    EXPECT_EQ(st.query(0, 9), 0, "查询在更新点之前的区间");

    std::cout << "\n========== 2. 覆盖与未命中测试 (Overwrite & Empty) ==========" << std::endl;
    st.update(10, 200); // 覆盖原来的 50
    EXPECT_EQ(st.query(10, 10), 200, "单点查询验证覆盖是否成功");
    EXPECT_EQ(st.query(0, 30), 300, "区间查询验证覆盖后的总和 (200 + 100)");

    // 空气墙测试：查询一个极其遥远且从未碰过的区间
    EXPECT_EQ(st.query(500000, 600000), 0, "查询未分配的虚空区间应当返回 0");

    std::cout << "\n========== 3. 极限边界测试 (Edge Cases) ==========" << std::endl;
    st.update(0, 7);     // 极左边界
    st.update(MAX_N, 9); // 极右边界 (10^9)
    EXPECT_EQ(st.query(0, 0), 7, "极左边界单点查询");
    EXPECT_EQ(st.query(MAX_N, MAX_N), 9, "极右边界单点查询");
    EXPECT_EQ(st.query(0, MAX_N), 316, "查询整个 10^9 宇宙的总和 (7 + 200 + 100 + 9)");

    std::cout << "\n========== 4. 鲁棒性与异常拦截 (Robustness) ==========" << std::endl;
    // 测试负数区间
    bool caughtException1 = false;
    try
    {
        st.query(-5, 10);
    }
    catch (const std::invalid_argument &e)
    {
        caughtException1 = true;
    }
    EXPECT_EQ(caughtException1, true, "拦截负数起点查询越界");

    // 测试 L > R
    bool caughtException2 = false;
    try
    {
        st.query(100, 50);
    }
    catch (const std::invalid_argument &e)
    {
        caughtException2 = true;
    }
    EXPECT_EQ(caughtException2, true, "拦截 qL > qR 的非法区间");

    // 测试超出最大范围
    bool caughtException3 = false;
    try
    {
        st.query(0, MAX_N + 1);
    }
    catch (const std::invalid_argument &e)
    {
        caughtException3 = true;
    }
    EXPECT_EQ(caughtException3, true, "拦截超出 MAX_N 的查询越界");
}

void runRMQTests()
{
    long long MAX_N = 1e9;

    // 【核心实例化】：聚合函数用 std::max，单位元用 INT_MIN
    DynamicSegmentTree st(MAX_N, [](int a, int b)
                          { return std::max(a, b); }, INT_MIN);

    std::cout << "========== 1. 基础 RMQ 功能测试 (Basic Max) ==========" << std::endl;
    st.update(10, 50);
    st.update(20, 100);
    st.update(30, 75);
    EXPECT_EQ(st.query(0, 40), 100, "查询包含所有点的区间，应返回最大值 100");
    EXPECT_EQ(st.query(0, 15), 50, "查询只包含节点 10 的区间，应返回 50");
    EXPECT_EQ(st.query(25, 40), 75, "查询只包含节点 30 的区间，应返回 75");

    std::cout << "\n========== 2. 负数与空气墙测试 (Negative & Empty) ==========" << std::endl;
    // 这是一个极具杀伤力的测试：如果你的单位元错写成了 0，这里就会返回 0 而不是 -5！
    st.update(500, -5);
    EXPECT_EQ(st.query(400, 600), -5, "查询包含负数的区间，必须正确返回负数最大值");

    // 查询完全没有更新过的虚空区间
    EXPECT_EQ(st.query(1000, 2000), INT_MIN, "查询从未碰过的虚空区间，应返回单位元 INT_MIN");

    std::cout << "\n========== 3. “削峰”覆盖测试 (Overwrite to Smaller) ==========" << std::endl;
    // 目前[0, 40] 的最大值是 100 (在 index=20 处)
    // 我们现在把 index=20 的值“削弱”成 10
    st.update(20, 10);
    // 此时 [0, 40] 中剩下的点是：index 10 (50), index 20 (10), index 30 (75)
    // 最大值理应易主，变成 75！
    EXPECT_EQ(st.query(0, 40), 75, "覆盖最大值为较小值后，区间最大值应当正确更新为次大值");
    EXPECT_EQ(st.query(15, 25), 10, "单点查询被削弱的点，应返回新值 10");

    std::cout << "\n========== 4. 极限边界测试 (Edge Cases) ==========" << std::endl;
    st.update(0, 999);
    st.update(MAX_N, 888);
    EXPECT_EQ(st.query(0, 0), 999, "极左边界单点最大值");
    EXPECT_EQ(st.query(MAX_N, MAX_N), 888, "极右边界单点最大值");
    EXPECT_EQ(st.query(0, MAX_N), 999, "查询整个 10^9 宇宙的最大值");

    std::cout << "\n========== 5. 鲁棒性测试 (Robustness) ==========" << std::endl;
    bool caught = false;
    try
    {
        st.query(50, 10); // L > R
    }
    catch (const std::invalid_argument &e)
    {
        caught = true;
    }
    EXPECT_EQ(caught, true, "拦截 qL > qR 的非法查询");
}

int main()
{
    std::cout << "开始执行动态线段树单元测试...\n\n";
    runAllTests();
    runRMQTests();
    std::cout << "\n所有测试用例执行完毕。" << std::endl;
    return 0;
}
