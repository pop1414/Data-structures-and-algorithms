#include <iostream>
#include <string>
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

    string input;

    getline(cin, input);

    if (input.size() == 0)
    {
        cout << 0;
    }
    else
    {

        vector<long long> weights(26, 0);

        for (char c : input)
        {
            long long index = (long long)(c - 'A');
            weights[index]++;
        }

        priority_queue<long long, vector<long long>, greater<long long>> min_heap;

        for (long long weight : weights)
        {
            if (weight != 0)
            {
                min_heap.push(weight);
            }
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
    }

    return 0;
}