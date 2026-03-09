#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

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

    const int maxn = 100100;
    vector<int> school(maxn, 0);

    int school_id, score, max_id = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> school_id >> score;
        school[school_id] += score;
        if (school_id > max_id)
        {
            max_id = school_id;
        }
    }

    int max_score = INT_MIN;
    int winner = 1;
    for (int i = 1; i <= max_id; i++)
    {
        if (school[i] > max_score)
        {
            max_score = school[i];
            winner = i;
        }
    }

    cout << winner << " " << max_score;

    return 0;
}