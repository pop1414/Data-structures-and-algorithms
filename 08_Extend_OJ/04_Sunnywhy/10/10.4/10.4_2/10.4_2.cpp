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

    void addEdge(int from, int to, int weight)
    {
        graph[from].emplace_back(to, weight);
    }

    Graph(int size) : graph(size) {}

    vector<int> dijkstra(int start)
    {
        //
        vector<int> dist(graph.size(), INT_MAX);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({dist[start], start});

        while (!min_heap.empty())
        {
            auto [start2curr_dist, curr] = min_heap.top();
            min_heap.pop();

            if (start2curr_dist > dist[curr])
            {
                continue;
            }

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int new_dist = edge.weight + start2curr_dist;

                if (new_dist < dist[next_node])
                {
                    dist[next_node] = new_dist;
                    min_heap.push({new_dist, next_node});
                }
            }
        }

        for (int &x : dist)
        {
            if (x == INT_MAX)
            {
                x = -1;
            }
        }

        return dist;
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

    int n, m, start;
    cin >> n >> m >> start;

    Graph graph(n);

    for (int i = 0; i < m; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;

        graph.addEdge(from, to, weight);
        graph.addEdge(to, from, weight);
    }

    vector<int> result = graph.dijkstra(start);

    for (int i = 0; i < result.size(); i++)
    {
        if (i == 0)
        {
            cout << result[i];
        }
        else
        {
            cout << " " << result[i];
        }
    }

    return 0;
}