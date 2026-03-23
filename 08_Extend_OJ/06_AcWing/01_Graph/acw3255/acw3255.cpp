#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <tuple>

using namespace std;

class Graph
{
public:
    struct Node
    {
        int to;
        int weight;
        int type;

        Node(int t, int w, int ty) : to(t), weight(w), type(ty) {}
    };

    Graph(int size) : graph(size) {}

    void buildGraph(int n, int m)
    {

        // 两个邻接矩阵，用来存大路（0）与小路（1）
        vector<vector<int>> min_major(n, vector<int>(n, INT_MAX));
        vector<vector<int>> min_minor(n, vector<int>(n, INT_MAX));

        for (int i = 0; i < m; i++)
        {
            int type;
            int a, b, c;
            cin >> type >> a >> b >> c;

            // 小路
            if (type)
            {
                // 无向图
                // 去重边
                min_minor[a - 1][b - 1] = min(c, min_minor[a - 1][b - 1]);
                min_minor[b - 1][a - 1] = min(c, min_minor[b - 1][a - 1]);
            }
            else
            {

                min_major[a - 1][b - 1] = min(c, min_major[a - 1][b - 1]);
                min_major[b - 1][a - 1] = min(c, min_major[b - 1][a - 1]);
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int minor_cost = min_minor[i][j];
                int major_cost = min_major[i][j];
                if (minor_cost != INT_MAX)
                {
                    graph[i].emplace_back(j, minor_cost, 1);
                }
                if (major_cost != INT_MAX)
                {
                    graph[i].emplace_back(j, major_cost, 0);
                }
            }
        }
    }
    void addEdge(int from, int to, int weight, int type)
    {
        graph[from].emplace_back(to, weight, type);
    }

    /**
    int dijk(int start)
    {
        int n = graph.size();
        vector<int> dist(n, INT_MAX);
        dist[start] = 0;

        //<dist, node, type>
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> min_heap;
        min_heap.push({dist[start], start, 0});

        while (!min_heap.empty())
        {
            auto [dist2start, curr, type] = min_heap.top();
            min_heap.pop();

            if (dist2start > dist[curr])
            {
                continue;
            }

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int road_type = edge.type;
                int new_dist = 0;

                if (road_type == 1)
                {
                    if (type == 1)
                    {
                        new_dist = pow(sqrt(dist2start) + edge.weight, 2);
                    }

                    if (type == 0)
                    {
                        new_dist = pow(edge.weight, 2) + dist2start;
                    }
                }

                if (road_type == 0)
                {
                    new_dist = edge.weight + dist2start;
                }

                if (new_dist < dist[next_node])
                {
                    dist[next_node] = new_dist;
                    min_heap.push({new_dist, next_node, road_type});
                }
            }
        }

        return dist[n - 1];
    }
    */

    int dijk(int start)
    {
        int n = graph.size();
        // dist[node][s]
        // 拆点最重要的是升维，对于下一个节点，不同方式到达当前节点有可能会导致到达下一个节点的不同状态
        // 所以要存储当前节点的不同状态
        vector<vector<int>> dist(n, vector<int>(1005, INT_MAX));
        dist[start][0] = 0;

        // <cost,连续小路长度, curr>
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> min_heap;
        min_heap.emplace(0, 0, start);

        while (!min_heap.empty())
        {
            auto [cost, s, curr] = min_heap.top();
            min_heap.pop();

            if (cost > dist[curr][s])
            {
                continue;
            }

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int w = edge.weight;
                int road_type = edge.type;

                int new_cost = 0;
                int new_s = 0;

                if (road_type == 0)
                {
                    new_s = 0;
                    new_cost = cost + w;
                }

                if (road_type == 1)
                {
                    new_s = s + w;
                    // cost是由小道产生的连续疲劳值+基础疲劳值
                    // 先得到基础批量值，再加上新小道产生的连续疲劳值
                    if (new_s >= 1005)
                    {
                        continue;
                    }
                    new_cost = cost - (s * s) + (new_s * new_s);
                }

                if (new_cost < dist[next_node][new_s])
                {
                    dist[next_node][new_s] = new_cost;
                    min_heap.emplace(new_cost, new_s, next_node);
                }
            }
        }

        int min_cost = INT_MAX;
        for (int n_dist : dist[n - 1])
        {
            if (n_dist < min_cost)
            {
                min_cost = n_dist;
            }
        }

        return min_cost;
    }

private:
    vector<vector<Node>>
        graph;
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

    int n, m;
    cin >> n >> m;
    Graph graph(n);
    // 节点从1开始
    // 小道为1
    graph.buildGraph(n, m);

    cout << graph.dijk(0);

    return 0;
}