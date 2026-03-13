#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct Node
{
    int val = 0;
    int leftChildIdx = -1;
    int rightChildIdx = -1;
};

class DynamicSegmentTree
{
private:
    vector<Node> tree;
    function<int(int, int)> merger;
    long long maxRange;

    int defaultVal;

    int allocateNode()
    {
        Node newNode;
        newNode.val = defaultVal;
        tree.push_back(newNode);
        return tree.size() - 1;
    }

    void update(long long l, long long r, int rootIndex, long long index, int val)
    {
        // 找到了叶子节点，赋值
        if (l == r)
        {
            tree[rootIndex].val = val;
            return;
        }

        long long mid = l + (r - l) / 2;
        if (index <= mid)
        {
            if (tree[rootIndex].leftChildIdx == -1)
            {
                tree[rootIndex].leftChildIdx = allocateNode();
            }
            update(l, mid, tree[rootIndex].leftChildIdx, index, val);
        }
        else
        {
            if (tree[rootIndex].rightChildIdx == -1)
            {
                tree[rootIndex].rightChildIdx = allocateNode();
            }
            update(mid + 1, r, tree[rootIndex].rightChildIdx, index, val);
        }

        int leftVal = (tree[rootIndex].leftChildIdx != -1) ? tree[tree[rootIndex].leftChildIdx].val : defaultVal;
        int rightVal = (tree[rootIndex].rightChildIdx != -1) ? tree[tree[rootIndex].rightChildIdx].val : defaultVal;

        // 其余不是叶子节点的都是通过merger函数来赋值
        tree[rootIndex].val = merger(leftVal, rightVal);
    }

    int query(long long l, long long r, int rootIndex, long long qL, long long qR)
    {
        if (rootIndex == -1 || l > qR || r < qL)
        {
            return defaultVal;
        }

        if (l >= qL && r <= qR)
        {
            return tree[rootIndex].val;
        }

        long long mid = l + (r - l) / 2;

        int leftVal = query(l, mid, tree[rootIndex].leftChildIdx, qL, qR);
        int rightVal = query(mid + 1, r, tree[rootIndex].rightChildIdx, qL, qR);

        return merger(leftVal, rightVal);
    }

public:
    DynamicSegmentTree(long long max_range, function<int(int, int)> mergeFunc, int def_val) : maxRange(max_range), merger(mergeFunc), defaultVal(def_val)
    {
        tree.reserve(100000);
        // 先创建一个根节点
        allocateNode();
    }

    void update(long long index, int val)
    {
        update(0, maxRange, 0, index, val);
    }

    int query(long long qL, long long qR)
    {
        return query(0, maxRange, 0, qL, qR);
    }
};

class NumArray
{
public:
    NumArray(vector<int> &nums) : dst(nums.size() - 1, [](int a, int b)
                                      { return a + b; }, 0)
    {

        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            dst.update(i, nums[i]);
        }
    }

    void update(int index, int val)
    {
        dst.update(index, val);
    }

    int sumRange(int left, int right)
    {
        return dst.query(left, right);
    }

private:
    DynamicSegmentTree dst;
};

int main()
{
    return 0;
}