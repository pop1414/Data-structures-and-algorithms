#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

class UF
{
private:
    vector<int> parent;
    int cnt;

public:
    UF(int n)
    {
        parent.resize(n);
        cnt = n;
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int findRoot(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = findRoot(parent[x]);
        }

        return parent[x];
    }

    void union_(int p, int q)
    {
        int rootP = findRoot(p);
        int rootQ = findRoot(q);

        if (rootP == rootQ)
        {
            return;
        }

        parent[rootQ] = rootP;

        cnt--;
    }

    bool connected(int p, int q)
    {
        int rootP = findRoot(p);
        int rootQ = findRoot(q);

        return rootP == rootQ;
    }

    int count() const
    {
        return cnt;
    }
};

class Graph
{
public:
    struct Node
    {
        int from;
        int to;
        int weight;

        Node(int f, int t, int w) : from(f), to(t), weight(w) {}
    };

    Graph(vector<vector<int>> &points)
    {
        this->n = points.size();
        for (int node = 0; node < n; node++)
        {
            int x1 = points[node][0];
            int y1 = points[node][1];

            for (int next_node = node + 1; next_node < n; next_node++)
            {
                int x2 = points[next_node][0];
                int y2 = points[next_node][1];

                addEdge(node, next_node, cul_dist(x1, y1, x2, y2));
            }
        }
    }

    void addEdge(int from, int to, int weight)
    {
        edges.emplace_back(from, to, weight);
    }

    int kruskal()
    {

        int result = 0;
        int selected_edges = 0;

        sort(edges.begin(), edges.end(), [](const auto &edge_a, const auto &edge_b)
             { return edge_a.weight < edge_b.weight; });

        UF uf(this->n);
        for (const auto &edge : edges)
        {
            int u = edge.from;
            int v = edge.to;
            int w = edge.weight;

            // 如果两点未连通，则可以添加它们的边（否则就会形成环）
            if (!uf.connected(u, v))
            {
                uf.union_(u, v);
                result += w;
                selected_edges++;
            }

            // 选够了边，提前结束
            if (selected_edges == this->n - 1)
            {
                break;
            }
        }

        // 只有当连通分量个数为1，才说明完整的最小生成树形成了
        if (uf.count() != 1)
        {
            return -1;
        }

        return result;
    }

private:
    vector<Node> edges;
    int n;
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
        return graph.kruskal();
    }
};
