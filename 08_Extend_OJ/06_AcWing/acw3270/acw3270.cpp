#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class UF
{
public:
    UF(int n)
    {
        // 一开始连通分量个数等于节点个数
        cnt = n;
        parent.resize(cnt);
        for (int i = 0; i < cnt; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (x != parent[x])
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union_(int p, int q)
    {
        int root_p = find(p);
        int root_q = find(q);

        if (root_p == root_q)
        {
            return;
        }

        // 应该是根节点合并
        parent[root_p] = root_q;

        cnt--;
    }

    bool connected(int p, int q)
    {
        int root_p = find(p);
        int root_q = find(q);

        return root_p == root_q;
    }

private:
    // 连通分量个数
    int cnt;
    vector<int> parent;
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

    Graph(int size, int r) : n(size), root(r) {}

    void addEdge(int from, int to, int weight)
    {
        edges.push_back(Node(from, to, weight));
    }

    int kruskal()
    {
        sort(edges.begin(), edges.end(), [](const auto &edge_a, const auto &edge_b)
             { return edge_a.weight < edge_b.weight; });

        int max_time = -1;

        UF uf(n);
        int selected_edges = 0;

        for (const auto &edge : edges)
        {
            int from = edge.from;
            int to = edge.to;
            int weight = edge.weight;

            if (!uf.connected(from, to))
            {
                uf.union_(from, to);
                if (weight > max_time)
                {
                    max_time = weight;
                }
                selected_edges++;
            }

            // 重点是找到1与n的路径中的最小边
            if (selected_edges == n - 1)
            {
                break;
            }
        }

        

        return max_time;
    }

private:
    vector<Node> edges;
    int n;
    int root;
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

    int n, m, root;
    cin >> n >> m >> root;
    Graph graph(n, root);
    // uf.connected(0, n - 1)
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph.addEdge(a - 1, b - 1, c);
        graph.addEdge(b - 1, a - 1, c);
    }

    cout << graph.kruskal();

    return 0;
}