#include <iostream>
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

    priority_queue<long long, vector<long long>, greater<long long>> min_heap;
    int weight;
    for (int i = 0; i < n; i++)
    {
        cin >> weight;
        min_heap.push(weight);
    }

    int wpl = 0;
    while (min_heap.size() >= 2)
    {
        long long w1 = min_heap.top();
        min_heap.pop();
        long long w2 = min_heap.top();
        min_heap.pop();

        long long sum = w1 + w2;
        min_heap.push(sum);

        wpl += sum;
    }

    cout << wpl;

    return 0;
}