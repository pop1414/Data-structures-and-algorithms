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

    bool SPFA(int start)
    {
        int n = graph.size();
        vector<int> dist(n, INT_MAX);
        dist[start] = 0;

        queue<int> q;
        q.push(start);
        vector<int> in_queue(n, 0);
        in_queue[start] = 1;

        vector<int> cnt(n, 0);
        cnt[start]++;

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            in_queue[curr] = 0;

            if (dist[curr] == INT_MAX)
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

                    if (in_queue[next_node] == 0)
                    {
                        in_queue[next_node] = 1;
                        q.push(next_node);
                        cnt[next_node]++;

                        if (cnt[next_node] >= n)
                        {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
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
            return -1;
        }
    }
    
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {

        int n, m;
        cin >> n >> m;
        Graph graph(n);
        for (int j = 0; j < m; j++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            if (w >= 0)
            {
                graph.addEdge(u - 1, v - 1, w);
                graph.addEdge(v - 1, u - 1, w);
            }
            else
            {
                graph.addEdge(u - 1, v - 1, w);
            }
        }

        if (graph.SPFA(0))
        {
            cout << "YES";
        }
        else
        {
            cout << "NO";
        }

        if (i != T - 1)
        {
            cout << '\n';
        }
    }

    return 0;
}