#include <iostream>
#include <vector>

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

    Graph(int size, vector<vector<int>> &flights) : graph(size)
    {
        for (const auto &flight : flights)
        {
            addEdge(flight[0], flight[1], flight[2]);
        }
    }

    void addEdge(int from, int to, int weight)
    {
        graph[from].emplace_back(to, weight);
    }

    int bellman_ford(int src, int dst, int k)
    {
        int n = graph.size();
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        // 注意题目描述的经过k站中转
        for (int round = 0; round <= k; round++)
        {
            bool has_update = false;
            // copy是草稿内容
            vector<int> dist_copy = dist;

            for (int node = 0; node < n; node++)
            {
                if (dist[node] == INT_MAX)
                {
                    continue;
                }

                for (const auto &edge : graph[node])
                {
                    int next_node = edge.to;
                    int new_dist = edge.weight + dist[node];

                    if (new_dist < dist_copy[next_node])
                    {
                        dist_copy[next_node] = new_dist;
                        has_update = true;
                    }
                }
            }

            dist = dist_copy;
            if (!has_update)
            {
                break;
            }
        }

        if (dist[dst] == INT_MAX)
        {
            return -1;
        }

        return dist[dst];
    }

private:
    vector<vector<Node>> graph;
};

class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                          int k)
    {
        Graph graph(n, flights);
        return graph.bellman_ford(src, dst, k);
    }
};