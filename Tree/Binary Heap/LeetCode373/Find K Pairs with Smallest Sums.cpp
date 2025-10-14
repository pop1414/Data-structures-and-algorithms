#include <bits/stdc++.h>

using namespace std;

struct numPair
{
    int num1;
    int num2;
    int idx1;
    int idx2;

    int getSum() const
    {
        return num1 + num2;
    }

    numPair(int n1, int n2, int i1, int i2) : num1(n1), num2(n2), idx1(i1), idx2(i2) {}
};

struct Compare
{
    bool operator()(const numPair &a, const numPair &b) const
    {
        return a.getSum() > b.getSum(); // 优先级队列默认让大的排后面
    }
};

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        priority_queue<numPair, vector<numPair>, Compare> minHeap;
        vector<vector<int>> res;

        for (int i = 0; i < min(k, (int)nums1.size()); i++)
        {
            minHeap.push(numPair(nums1[i], nums2[0], i, 0));
        }

        /**
        示例: nums1 = [1,7,11], nums2 = [2,4,6]

                nums2[0]  nums2[1]  nums2[2]
                    (2)       (4)       (6)
        nums1[0](1)  3        5        7
        nums1[1](7)  9        11       13
        nums1[2](11) 13       15       17

        让第一列全部进去
        然后让其中最小的出去，此时要补一个进去，那如何补
        关键在于这两个数组都是已排好序的
        补同一行的下一列，这样补的数肯定是余下中最小的

         */

        while (k-- > 0 && !minHeap.empty())
        {
            numPair top = minHeap.top();
            minHeap.pop();

            res.push_back({top.num1, top.num2});

            if (top.idx2 + 1 < nums2.size())
            {
                minHeap.push(numPair(nums1[top.idx1], nums2[top.idx2 + 1], top.idx1, top.idx2 + 1));
            }
        }

        return res;
    }
};