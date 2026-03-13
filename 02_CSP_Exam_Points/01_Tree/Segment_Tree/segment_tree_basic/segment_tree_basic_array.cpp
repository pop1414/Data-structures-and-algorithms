#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept> // 修复：添加异常头文件

using namespace std;

class ArraySegmentTree
{
private:
    // 底层用数值实现，容量一般开4n
    vector<int> tree;
    // 原数组的元素个数
    int n;
    // 聚合函数(求和/最大值)
    function<int(int, int)> merger;

    // 私有辅助函数（核心3个+2个工具函数）

    // 从1开始索引
    int leftChild(int pos)
    {
        return 2 * pos;
    }
    int rightChild(int pos)
    {
        return 2 * pos + 1;
    }
    // 构建线段树
    // l,r表示当期节点对应原数组的区间
    // rootIndex表示当前节点在tree数组的索引(根节点是1)
    void build(const vector<int> &nums, int l, int r, int rootIndex)
    {
        // 区间长度为1，叶子节点
        if (l == r)
        {
            tree[rootIndex] = nums[l];
            return;
        }

        // 拆分区间：找中点，递归构建左右子树
        int mid = l + (r - l) / 2;
        int leftIndex = leftChild(rootIndex);
        int rightIndex = rightChild(rootIndex);

        build(nums, l, mid, leftIndex);
        build(nums, mid + 1, r, rightIndex);

        // 递归构建完左右子树后，当前节点值等于左右子树的聚合值
        // 只有叶子节点是直接赋值的，其余非叶子节点都是聚合值
        tree[rootIndex] = merger(tree[leftIndex], tree[rightIndex]);
    }
    // 单点更新
    // l,r表示当前节点对应原数组的区间
    // rootIndex表示当前节点对应tree数组的索引
    // index表示要更新的原数组下标
    void update(int l, int r, int rootIndex, int index, int value)
    {
        if (l == r)
        {
            tree[rootIndex] = value;
            return;
        }

        int mid = l + (r - l) / 2;
        int leftIndex = leftChild(rootIndex);
        int rightIndex = rightChild(rootIndex);

        if (index <= mid)
        {
            update(l, mid, leftIndex, index, value);
        }
        else
        {
            update(mid + 1, r, rightIndex, index, value);
        }

        tree[rootIndex] = merger(tree[leftIndex], tree[rightIndex]);
    }
    // 区间查询
    int query(int l, int r, int rootIndex, int qL, int qR)
    {
        // 完全匹配，当前区间正好是查询区间，直接返回当前节点值
        if (qL == l && qR == r)
        {
            return tree[rootIndex];
        }

        // 拆分区间
        int mid = l + (r - l) / 2;
        int leftIndex = leftChild(rootIndex);
        int rightIndex = rightChild(rootIndex);

        // 查询区间全在左子树
        if (qR <= mid)
        {
            return query(l, mid, leftIndex, qL, qR);
        }
        // 查询区间全在右子树
        else if (qL > mid)
        {
            return query(mid + 1, r, rightIndex, qL, qR);
        }
        // 横跨左右子树，拆分成[qL, mid] 与 [mid + 1, qR]
        else
        {
            int leftRes = query(l, mid, leftIndex, qL, mid);
            int rightRes = query(mid + 1, r, rightIndex, mid + 1, qR);

            return merger(leftRes, rightRes);
        }
    }

public:
    ArraySegmentTree(const vector<int> &nums, function<int(int, int)> mergeFunc) : n(nums.size()), merger(mergeFunc)
    {
        tree.resize(4 * n);
        build(nums, 0, n - 1, 1);
    }
    // 对外暴露接口（用户不用传l/r/rootIndex）
    void update(int index, int value)
    {
        update(0, n - 1, 1, index, value);
    }
    int query(int qL, int qR)
    {
        if (qL < 0 || qR >= n || qL > qR)
        {
            throw invalid_argument("Invalid range: [" + to_string(qL) + ", " + to_string(qR) + "]");
        }
        return query(0, n - 1, 1, qL, qR);
    }
};

int main()
{
    vector<int> arr = {1, 3, 5, 7, 9};
    ArraySegmentTree st(arr, [](int a, int b)
                        { return a + b; }); // 求和
    cout << st.query(1, 3) << endl;         // 预期15
    st.update(2, 10);
    cout << st.query(1, 3) << endl; // 预期20
    return 0;
}