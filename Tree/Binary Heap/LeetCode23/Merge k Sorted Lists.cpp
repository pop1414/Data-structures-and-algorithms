#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class MinHeap
{

private:
    vector<int> heap;

    int parent(int i)
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
        while (i > 0 && heap[i] < heap[parent(i)])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i)
    {
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

    MinHeap(const vector<int> &arr) : heap(arr)
    {
        for (int i = parent(heap.size() - 1); i >= 0; i--)
        {
            // 为何是下沉，假设arr是最大堆，我要变成最小堆
            // 从最后一个非叶节点开始
            // 此时heap[i]的位置不对，太大了，需要下沉
            heapifyDown(i);
        }
    }

    int pop()
    {
        int minVal = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();

        if (!heap.empty())
        {
            heapifyDown(0);
        }

        return minVal;
    }

    vector<int> heapSort()
    {
        vector<int> res;

        // 不可以用for循环带i，因为heap.size()是在不断减小的
        while (!heap.empty())
        {
            res.push_back(pop());
        }

        return res;
    }
};

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        vector<int> arr;
        for (int i = 0; i < lists.size(); i++)
        {
            ListNode *curr = lists[i];
            while (curr != nullptr)
            {
                arr.push_back(curr->val);
                curr = curr->next;
            }
        }

        MinHeap heap(arr);
        vector<int> res = heap.heapSort();

        ListNode *head = new ListNode(0);
        ListNode *curr = head;
        for (int i = 0; i < res.size(); i++)
        {
            ListNode *newNode = new ListNode(res[i]);
            curr->next = newNode;
            curr = curr->next;
        }

        return head->next;
    }
};