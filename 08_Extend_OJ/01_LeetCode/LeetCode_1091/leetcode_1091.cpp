#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(vector<vector<int>> &grid)
{
    int n = grid.size();

    // 起点不存在
    if (grid[0][0] == 1)
    {
        return -1;
    }

    // 8个方向，左上至右下，必须走0，可能有不止一条路径，找到路径最短的（0最少）
    int step = 0;
    queue<pair<int, int>> q;
    vector<vector<int>> visited(n, vector<int>(n, 0));

    // 入队的时候就标记
    q.push({0, 0});
    visited[0][0] = 1;

    // 从0点开始，顺时针方向
    int dirs[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    while (!q.empty())
    {
        int sz = q.size();
        step++;
        for (int i = 0; i < sz; i++)
        {

            auto [x, y] = q.front();
            q.pop();

            // 到达了终点
            // 如果终点是1，那么根据下面的条件限制是不会进入队列的
            if (x == n - 1 && y == n - 1)
            {
                return step;
            }

            for (int i = 0; i < 8; i++)
            {
                int next_x = x + dirs[i][0];
                int next_y = y + dirs[i][1];
                // 此处做限制，保证下面的数组索引合规
                if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= n)
                {
                    continue;
                }
                // 死路跳过(不要忘记判断已经访问过的)
                if (grid[next_x][next_y] == 1 || visited[next_x][next_y] == 1)
                {
                    continue;
                }

                // 入队的时候就标记
                q.push({next_x, next_y});
                visited[next_x][next_y] = 1;
            }
        }
    }

    // 始终没有到达终点
    return -1;
}

class Solution
{
public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {
        return bfs(grid);
    }
};

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
    vector<vector<int>> grid(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int num;
            cin >> num;
            grid[i][j] = num;
        }
    }

    Solution s;
    cout << s.shortestPathBinaryMatrix(grid);

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << grid[i][j];
    //     }
    //     cout << '\n';
    // }

    return 0;
}