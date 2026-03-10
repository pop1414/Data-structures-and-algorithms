#include <iostream>
#include <queue>
#include <vector>

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

    int x;
    vector<int> nums;

    while (cin >> x)
    {
        nums.push_back(x);
    }

    // 比较规则less<int>(谁小放下层)，3 < 5 ? -> true，3优先级低（放下层），最终堆顶5
    // greater<int>(谁大放下层)，3 > 5 ? -> false, 5优先级低(放下层)，最终堆顶3
    priority_queue<int, vector<int>, greater<int>> min_heap;

    for (int num : nums)
    {
        min_heap.push(num);
    }

    while (!min_heap.empty())
    {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }

    return 0;
}