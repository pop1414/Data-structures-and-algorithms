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

    // 定义：priority_queue<元素类型, 底层容器（默认vector）, 比较规则（默认less）>
    // 最大堆
    priority_queue<int> pq;
    vector<int> nums;

    int x;
    while (cin >> x)
    {
        nums.push_back(x);
    }

    for (int num : nums)
    {
        pq.push(num);
    }

    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }

    cout << '\n';

    return 0;
}