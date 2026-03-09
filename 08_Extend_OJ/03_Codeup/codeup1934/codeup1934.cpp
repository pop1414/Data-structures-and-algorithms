#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc > 1)
    {
        FILE *fp = freopen(argv[1], "r", stdin);
        if (!fp)
        {
            cout << "WRONG!";
            exit(1);
        }
    }

    int n;

    while (cin >> n)
    {
        vector<int> nums;

        for (int i = 0; i < n; i++)
        {
            int num;
            cin >> num;
            nums.push_back(num);
        }

        int x;
        cin >> x;

        int index;
        for (index = 0; index < n; index++)
        {
            if (nums[index] == x)
            {
                cout << index << '\n';
                break;
            }
        }

        if (index == n)
        {
            cout << -1 << '\n';
        }
    }

    return 0;
}