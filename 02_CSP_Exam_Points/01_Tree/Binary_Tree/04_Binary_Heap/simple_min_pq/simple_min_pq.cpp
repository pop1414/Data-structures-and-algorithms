#include <iostream>
#include <vector>

using namespace std;

class SimpleMinPQ
{
public:
    SimpleMinPQ(int capacity)
    {
        heap.resize(capacity + 1);
        size = 0;
    }

    int getSize() const
    {
        return size;
    }

    bool empty()
    {
        return size == 0;
    }

    int peek()
    {
        return heap[1];
    }

    void push(int val)
    {
        size++;
        heap[size] = val;
        swim(size);
    }

    void pop()
    {
        heap[1] = heap[size];
        size--;
        sink(1);
    }

private:
    // 底层用数组实现
    // 因为二叉堆是完全二叉树
    vector<int> heap;

    // 堆中元素的个数
    // 从索引1开始，所以size与最后索引数值一样
    int size;

    static int parent(int node)
    {
        return node / 2;
    }

    static int leftChild(int node)
    {
        return 2 * node;
    }

    static int rightChild(int node)
    {
        return 2 * node + 1;
    }

    // 上浮操作，时间复杂度是树高 O(logN)
    void swim(int node)
    {
        // 边界是index > 1，堆顶不需要上浮
        // swin是push一个新节点后使用，目的让新节点移动到属于自己的位置
        // 所以只要比父节点小（min_heap）就要不断swin
        while (node > 1 && heap[node] < heap[parent(node)])
        {
            swap(heap[parent(node)], heap[node]);
            node = parent(node);
        }
    }

    // 下沉操作，时间复杂度是树高 O(logN)
    void sink(int node)
    {
        while (true)
        {

            int leftIndex = leftChild(node);
            int rightIndex = rightChild(node);
            int minIndex = node;
            
            // 分别于左右子节点进行对比，注意是minIndex与left/rightIndex进行对比
            if (leftIndex <= size && heap[minIndex] > heap[leftIndex])
            {
                minIndex = leftIndex;
            }
            if (rightIndex <= size && heap[minIndex] > heap[rightIndex])
            {
                minIndex = rightIndex;
            }

            // 说明最小的是自己，所以不动
            if (minIndex == node)
            {
                break;
            }

            swap(heap[node], heap[minIndex]);
            node = minIndex;
        }
    }
};

int main()
{

    SimpleMinPQ pq(5);
    pq.push(3);
    pq.push(2);
    pq.push(1);
    pq.push(5);
    pq.push(4);

    cout << pq.peek() << endl; // 1
    pq.pop();
    cout << pq.peek() << endl; // 2
    pq.pop();
    cout << pq.peek() << endl; // 3
    pq.pop();
    cout << pq.peek() << endl; // 4
    pq.pop();
    cout << pq.peek() << endl; // 5
    pq.pop();

    return 0;
}