#include <iostream>
#include <cmath>

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

    double n;
    cin >> n;
    char c;
    cin >> c;

    for (int i = 0; i < round(n / 2); i++)
    {
        if (i == 0 || i == round(n / 2) - 1)
        {
            for (int j = 0; j < n; j++)
            {
                cout << c;
            }
            cout << '\n';
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                if (j == 0 || j == n - 1)
                {
                    cout << c;
                }
                else
                {
                    cout << " ";
                }
            }
            cout << '\n';
        }
    }

    return 0;
}