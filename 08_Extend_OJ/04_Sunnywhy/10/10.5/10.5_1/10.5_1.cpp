#include <iostream>
#include <vector>
#include <climits>
#include <queue>

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

    int prim(int start)
    {
        int n = graph.size();
        // 节点到MST的最小距离，起始节点距离为0（起始节点选择随意）
        vector<int> key(n, INT_MAX);
        key[start] = 0;

        // 最小堆存放[node2mst_dist, node]
        // 存放的是潜在的可点亮的节点，选用最小堆体现了Prim算法的贪心思想
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({key[start], start});

        // 已经点亮的节点个数
        int selected_node = 0;
        // 节点是否在MST中
        vector<int> in_mst(n, 0);
        // 生成权重
        int result = 0;

        while (!min_heap.empty())
        {
            auto [node2mst_dist, curr] = min_heap.top();
            min_heap.pop();

            // 如果当前节点在MST中，
            if (in_mst[curr] == 1 || node2mst_dist > key[curr])
            {
                continue;
            }

            in_mst[curr] = 1;
            selected_node++;
            result += key[curr];

            // 此时当前节点已经被点亮，那么它的邻居节点都是潜在节点
            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int weight = edge.weight;

                if (in_mst[next_node] == 0 && weight < key[next_node])
                {
                    min_heap.push({weight, next_node});
                    key[next_node] = weight;
                }
            }
        }

        if (selected_node != n)
        {
            return -1;
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
    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
        graph.addEdge(to, from, weight);
    }

    cout << graph.prim(0);
    return 0;
}