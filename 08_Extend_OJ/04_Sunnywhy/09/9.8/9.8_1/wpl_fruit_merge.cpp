#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        FILE *fp = freopen(argv[1], "r", stdin);
        if (!fp)
        {
            exit(1);
        }
    }

    int n;
    cin >> n;

    // greater<long long>最小堆
    priority_queue<long long, vector<long long>, greater<long long>> min_heap;

    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        min_heap.push(x);
    }

    long long wpl = 0;

    // 至少要含有两个元素才能进行合并（进入该循环）
    // 如果只有一个元素，那么说明wpl已经计算完了，不应该进入该循环
    // 所以一开始写的条件while(!min_heap.empty())是错误的
    while (min_heap.size() >= 2)
    {
        long long num1 = min_heap.top();
        min_heap.pop();
        long long num2 = min_heap.top();
        min_heap.pop();

        long long sum = num1 + num2;
        wpl += sum;
        min_heap.push(sum);
    }

    cout << wpl;

    return 0;
}