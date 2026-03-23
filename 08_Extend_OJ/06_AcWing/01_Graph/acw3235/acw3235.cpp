#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph
{
public:
    struct Node
    {
        int to;
        int weight;

        Node(int t, int w) : to(t), weight(w) {}
    };

    Graph(int size) : graph(size) {}

    void addEdge(int from, int to, int weight)
    {
        graph[from].emplace_back(to, weight);
    }

    vector<int> dijk(int start)
    {
        int n = graph.size();
        vector<int> dist(n, INT_MAX);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({dist[start], start});

        while (!min_heap.empty())
        {
            auto [dist2start, curr] = min_heap.top();
            min_heap.pop();

            if (dist2start > dist[curr])
            {
                continue;
            }

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int new_dist = edge.weight + dist[curr];

                if (new_dist < dist[next_node])
                {
                    dist[next_node] = new_dist;
                    min_heap.push({new_dist, next_node});
                }
            }
        }

        return dist;
    }

    // 题目要求从无向图中选出来若干条边，使得选出来边的总权值和最小
    // 并且满足所有点到1号点的最短距离不变
    // 最短距离不变是大前提，是硬性条件，所以先用单源最短路径算法得到每个节点的dist[v]
    // 之后单独遍历每个节点，遍历邻边，如果weight + dist[u] = dist[v]，这条边就是待选边
    // 然后从待选边选出weight最小的

    // 与普通的最小生成树不同的是，要满足最短路径这个要求
    // 而这个前提要求也是能适用贪心的原因
    // 因为在用完dijk后，待选边的集合已经确定了，对于每个节点只需要在集合中选出最小的边即可
    int solution(int start)
    {
        vector<int> dist = dijk(0);
        int result = 0;
        int n = graph.size();
        for (int node = 0; node < n; node++)
        {
            if (node == start)
            {
                continue;
            }

            int min_edge = INT_MAX;
            for (const auto &edge : graph[node])
            {
                int next_node = edge.to;
                int weight = edge.weight;

                if (dist[node] == dist[next_node] + weight)
                {
                    if (weight < min_edge)
                    {
                        min_edge = weight;
                    }
                }
            }

            result += min_edge;
        }

        return result;
    }

private:
    vector<vector<Node>> graph;
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
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph.addEdge(a - 1, b - 1, c);
        graph.addEdge(b - 1, a - 1, c);
    }

    cout << graph.solution(0);

    return 0;
}