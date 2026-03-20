#include <iostream>
#include <vector>
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

    Graph(vector<vector<int>> &points)
    {
        int n = points.size();
        graph.resize(n);

        for (int node = 0; node < n; node++)
        {
            int x1 = points[node][0];
            int y1 = points[node][1];
            for (int next_node = node + 1; next_node < n; next_node++)
            {
                int x2 = points[next_node][0];
                int y2 = points[next_node][1];

                int val = cul_dist(x1, y1, x2, y2);

                addEdge(node, next_node, val);
                addEdge(next_node, node, val);
            }
        }
    }

    void addEdge(int from, int to, int weight)
    {
        graph[from].emplace_back(to, weight);
    }

    //
    int prim(int start)
    {
        int n = graph.size();
        int result = 0;
        int selected_node = 0;

        vector<int> key(n, INT_MAX);
        key[start] = 0;

        vector<int> in_mst(n, 0);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>
            min_heap;

        min_heap.push({key[start], start});

        while (!min_heap.empty())
        {
            auto [dist2mst, curr] = min_heap.top();
            min_heap.pop();

            if (in_mst[curr] == 1 || dist2mst > key[curr])
            {
                continue;
            }

            selected_node++;
            in_mst[curr] = 1;
            result += key[curr];

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int weight = edge.weight;

                if (in_mst[next_node] == 0 && key[next_node] > weight)
                {

                    key[next_node] = weight;
                    min_heap.push({weight, next_node});
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
    // prim要点是点亮各个顶点，所以用vector<vector<Node>> graph(Node: int to, int weight)存储
    // kruskal要点是排序所有边，所有用vector<Node> edges存储(Node:int from, int to, int weight);
    vector<vector<Node>> graph;

    int cul_dist(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2);
    }
};

class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        Graph graph(points);
        return graph.prim(0);
    }
};

int main()
{
    return 0;
}