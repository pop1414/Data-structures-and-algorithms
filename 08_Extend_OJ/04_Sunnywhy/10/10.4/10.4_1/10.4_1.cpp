#include <iostream>
#include <queue>
#include <vector>
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

    int dijkstra(int start, int target)
    {

        if (start == target)
        {
            return 0;
        }

        vector<int> dist(graph.size(), INT_MAX);
        dist[start] = 0;

        // dist, node
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({dist[start], start});

        while (!min_heap.empty())
        {
            auto [start2curr_dist, curr] = min_heap.top();
            min_heap.pop();

            // 节点第一次被弹出小堆，其对应的距离就是起点到该节点的最短距离
            // 节点何时会被压入堆中，当遍历的时候发现比现有的数据更优
            // 而之后小堆会一直弹出之前压入的潜在最优路径
            // 在目标节点被弹出来之前，说明其余节点的路径是较短的，一直会更新其余节点(curr)的最优路径，当其余节点的最优路径更新后，目标节点如果于curr节点有联系，那么有可能就会更新数据
            // 而当目标节点被弹出来的时候，说明其余节点的较短路径都已经遍历过了，与它们有联系的节点路径也被更新过了，那么此时说明目标节点的路径是最优的
            if (curr == target)
            {
                // 此时dist[curr] == start2curr_dist
                // 代码写这个更好，不需要访问数组
                return start2curr_dist;
            }

            if (start2curr_dist > dist[curr])
            {
                continue;
            }

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int new_dist = dist[curr] + edge.weight;

                if (new_dist < dist[next_node])
                {
                    dist[next_node] = new_dist;
                    // 更新最优路径，说明这是潜在最优路径
                    min_heap.push({dist[next_node], next_node});
                }
            }
        }

        return -1;
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

    int n, m, start, target;
    cin >> n >> m >> start >> target;
    // 读取整数的时候，换行符不影响
    // cin >> 读取整数时会自动跳过空格、换行、制表符等空白字符
    // cin.ignore();

    Graph graph(n);

    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;

        graph.addEdge(from, to, weight);
        graph.addEdge(to, from, weight);
    }

    cout << graph.dijkstra(start, target);

    return 0;
}