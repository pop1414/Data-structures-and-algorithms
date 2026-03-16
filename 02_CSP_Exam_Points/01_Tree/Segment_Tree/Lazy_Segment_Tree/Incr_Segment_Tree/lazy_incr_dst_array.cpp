#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct Node
{
    long long val = 0;
    long long lazy;
    int leftChildIdx = -1;
    int rightChildIdx = -1;
};

class LazyDST
{
private:
    vector<Node> tree;
    // 最大有效索引（Last Index）
    long long maxRange;
    function<long long(long long, long long)> merger;

    long long defaultVal;

    int allocateNode()
    {
        Node newNode;
        newNode.val = defaultVal;
        tree.push_back(newNode);
        return tree.size() - 1;
    }

    // rootIndex 当前节点的下标
    // L,R当前节点代表的区间
    void pushDown(int rootIndex, long long L, long long R)
    {
        // 没有懒标记需要pushdown，直接返回
        if (tree[rootIndex].lazy == 0)
        {
            return;
        }

        long long mid = L + (R - L) / 2;

        if (tree[rootIndex].leftChildIdx == -1)
        {
            int newID = allocateNode();
            tree[rootIndex].leftChildIdx = newID;
        }
        if (tree[rootIndex].rightChildIdx == -1)
        {
            int newID = allocateNode();
            tree[rootIndex].rightChildIdx = newID;
        }

        int leftChild = tree[rootIndex].leftChildIdx;
        int rightChild = tree[rootIndex].rightChildIdx;

        // 左子区间长度
        long long leftLength = mid - L + 1;
        // 更新左子节点聚合值
        tree[leftChild].val += leftLength * tree[rootIndex].lazy;
        // 为左子节点更新懒标记
        tree[leftChild].lazy += tree[rootIndex].lazy;

        long long rightLength = R - (mid + 1) + 1;
        tree[rightChild].val += rightLength * tree[rootIndex].lazy;
        tree[rightChild].lazy += tree[rootIndex].lazy;

        // 不要忘记去除自己的懒标签
        tree[rootIndex].lazy = 0;
    }

    void update(long long L, long long R, int rootIndex, long long uL, long long uR, int value)
    {
        // 无交集
        if (L > uR || R < uL)
        {
            return;
        }

        if (L >= uL && R <= uR)
        {
            long long length = R - L + 1;
            // 当前节点先自己接受更新
            tree[rootIndex].val += length * value;
            // 然后标记上懒标记
            tree[rootIndex].lazy += value;
            return;
        }

        pushDown(rootIndex, L, R);

        long long mid = L + (R - L) / 2;

        if (uL <= mid)
        {
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

        long long leftVal = (tree[rootIndex].leftChildIdx != -1) ? tree[tree[rootIndex].leftChildIdx].val : defaultVal;
        long long rightVal = (tree[rootIndex].rightChildIdx != -1) ? tree[tree[rootIndex].rightChildIdx].val : defaultVal;

        tree[rootIndex].val = merger(leftVal, rightVal);
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

        long long leftVal = query(L, mid, tree[rootIndex].leftChildIdx, qL, qR);
        long long rightVal = query(mid + 1, R, tree[rootIndex].rightChildIdx, qL, qR);

        return merger(leftVal, rightVal);
    }

public:
    LazyDST(long long max_range, function<long long(long long, long long)> mergeFunc, long long def_val) : maxRange(max_range), merger(mergeFunc), defaultVal(def_val)
    {
        tree.reserve(100000);
        // 创建根节点
        allocateNode();
    }

    void update(long long uL, long long uR, int value)
    {
        update(0, maxRange, 0, uL, uR, value);
    }
    int query(long long qL, long long qR)
    {
        return query(0, maxRange, 0, qL, qR);
    }
};

int main()
{
    return 0;
}