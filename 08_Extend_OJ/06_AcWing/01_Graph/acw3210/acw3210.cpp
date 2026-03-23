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

    int Prim(int start)
    {
        int n = graph.size();
        vector<int> key(n, INT_MAX);
        key[start] = 0;

        // node2mst_dist, curr
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({key[start], start});

        vector<int> in_mst(n, 0);
        int result = 0;

        while (!min_heap.empty())
        {
            auto [node2mst_dist, curr] = min_heap.top();
            min_heap.pop();

            if (in_mst[curr] == 1)
            {
                continue;
            }

            in_mst[curr] = 1;
            result += node2mst_dist;
            key[curr] = node2mst_dist;

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int weight = edge.weight;

                if (in_mst[next_node] == 0 && key[next_node] > weight)
                {
                    min_heap.push({weight, next_node});
                    key[next_node] = weight;
                }
            }
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

    cout << graph.Prim(0);
    return 0;
}