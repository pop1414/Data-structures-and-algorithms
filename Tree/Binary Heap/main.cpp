#include <bits/stdc++.h>

using namespace std;

// 堆支持重复数据
template <typename T>
class MinHeap
{

private:
    vector<T> heap;

    int parentIndex(int i)
    {
        return (i - 1) / 2;
    }

    int leftIndex(int i)
    {
        return 2 * i + 1;
    }

    int rightIndex(int i)
    {
        return 2 * i + 2;
    }

    void heapifyUp(int i)
    {
        // 上浮是持续上浮，找到最合适的位置
        while (i > 0 && heap[parentIndex(i)] > heap[i])
        {
            // 实际改变的是值，i只是用来寻找位置
            swap(heap[i], heap[parentIndex(i)]);
            i = parentIndex(i);
        }
    }

    void heapifyDown(int i)
    {
        // 需要比较左右子节点（即在三个数中寻找最小的，然后让它们两个互换,minIndex,i）
        int minIndex = i;
        int l = leftIndex(i);
        int r = rightIndex(i);

        if (l < heap.size() && heap[l] < heap[minIndex])
        {
            minIndex = l;
        }
        if (r < heap.size() && heap[r] < heap[minIndex])
        {
            minIndex = r;
        }
        if (i != minIndex)
        {
            swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    MinHeap() {}

    MinHeap(const vector<T> &arr) : heap(arr)
    {
        // 从最后一个不是叶节点的子节点往前（叶节点不需要处理）
        for (int i = parentIndex(heap.size() - 1); i >= 0; i--)
        {
            heapifyDown(i);
        }
    }

    void push(const T &val)
    {
        // 先放入到最后，然后上浮
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    // 删除并返回最小元素
    T pop()
    {
        if (empty())
        {
            throw runtime_error("empty!");
        }

        T minVal = heap[0];
        // 把最后的提上来，然后再让他下沉
        heap[0] = heap.back();
        heap.pop_back();

        // 注意堆中只有一个元素的情况
        if (!empty())
        {
            heapifyDown(0);
        }

        return minVal;
    }

    T top() const
    {
        if (empty())
        {
            throw runtime_error("empty!");
        }
        return heap[0];
    }

    bool empty() const
    {
        return heap.empty();
    }

    size_t size() const
    {
        return heap.size();
    }

    void print() const
    {
        for (const auto &val : heap)
        {
            cout << val << " ";
        }
        cout << endl;
    }
};

template <typename T>
class MaxHeap
{

private:
    vector<T> heap;

    int parentIndex(int i)
    {
        return (i - 1) / 2;
    }

    int leftIndex(int i)
    {
        return 2 * i + 1;
    }

    int rightIndex(int i)
    {
        return 2 * i + 2;
    }

    void heapifyUp(int i)
    {
        // 上浮是持续上浮，找到最合适的位置
        while (i > 0 && heap[parentIndex(i)] < heap[i])
        {
            // 实际改变的是值，i只是用来寻找位置
            swap(heap[i], heap[parentIndex(i)]);
            i = parentIndex(i);
        }
    }

    void heapifyDown(int i)
    {
        // 需要比较左右子节点（即在三个数中寻找最大的，然后让它们两个互换,minIndex,i）
        int maxIndex = i;
        int l = leftIndex(i);
        int r = rightIndex(i);

        if (l < heap.size() && heap[l] > heap[maxIndex])
        {
            maxIndex = l;
        }
        if (r < heap.size() && heap[r] > heap[maxIndex])
        {
            maxIndex = r;
        }
        if (i != maxIndex)
        {
            swap(heap[i], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    MaxHeap() {}

    MaxHeap(const vector<T> &arr) : heap(arr)
    {
        // 从最后一个不是叶节点的子节点往前（叶节点不需要处理）
        for (int i = parentIndex(heap.size() - 1); i >= 0; i--)
        {
            heapifyDown(i);
        }
    }

    void push(const T &val)
    {
        // 先放入到最后，然后上浮
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    // 删除并返回最小元素
    T pop()
    {
        if (empty())
        {
            throw runtime_error("empty!");
        }

        T minVal = heap[0];
        // 把最后的提上来，然后再让他下沉
        heap[0] = heap.back();
        heap.pop_back();

        // 注意堆中只有一个元素的情况
        if (!empty())
        {
            heapifyDown(0);
        }

        return minVal;
    }

    T top() const
    {
        if (empty())
        {
            throw runtime_error("empty!");
        }
        return heap[0];
    }

    bool empty() const
    {
        return heap.empty();
    }

    size_t size() const
    {
        return heap.size();
    }

    void print() const
    {
        for (const auto &val : heap)
        {
            cout << val << " ";
        }
        cout << endl;
    }
};

// 测试代码
int main()
{
    std::cout << "=== 最小堆测试 ===" << std::endl;
    MinHeap<int> minHeap;

    minHeap.push(5);
    minHeap.push(3);
    minHeap.push(8);
    minHeap.push(1);
    minHeap.push(9);

    std::cout << "插入元素后: ";
    minHeap.print();

    std::cout << "堆顶元素: " << minHeap.top() << std::endl;
    std::cout << "弹出元素: " << minHeap.pop() << std::endl;
    std::cout << "弹出后: ";
    minHeap.print();

    std::cout << "\n=== 最大堆测试 ===" << std::endl;
    std::vector<int> arr = {4, 10, 3, 5, 1};
    MaxHeap<int> maxHeap(arr);

    std::cout << "从数组构建堆: ";
    maxHeap.print();

    maxHeap.push(15);
    std::cout << "插入15后: ";
    maxHeap.print();

    std::cout << "堆顶元素: " << maxHeap.top() << std::endl;
    std::cout << "弹出元素: " << maxHeap.pop() << std::endl;
    std::cout << "弹出后: ";
    maxHeap.print();

    return 0;
}