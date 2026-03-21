#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

class UF
{
private:
    vector<int> parent;
    // 连通分量个数
    int cnt;

public:
    UF(int size)
    {
        this->cnt = size;
        parent.resize(size);
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
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

        parent[root_p] = root_q;

        // 注意连通分量个数要减少
        cnt--;
    }

    bool connected(int p, int q)
    {
        int root_p = find(p);
        int root_q = find(q);

        return root_p == root_q;
    }

    int size() const
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

        Node() : from(0), to(0), weight(0) {}
        Node(int f, int t, int w) : from(f), to(t), weight(w) {}
    };

    Graph(int size) : n(size) {}

    void addEdge(int from, int to, int weight)
    {
        graph.push_back(Node(from, to, weight));
    }

    int kruskal(int start)
    {
        sort(graph.begin(), graph.end(), [](const auto &edge_a, const auto &edge_b)
             { return edge_a.weight < edge_b.weight; });

        UF uf(this->n);
        int result = 0;
        int selected_edge = 0;

        for (const auto &edge : graph)
        {
            int from = edge.from;
            int to = edge.to;
            int weight = edge.weight;

            if (!uf.connected(from, to))
            {
                uf.union_(from, to);
                result += weight;
                selected_edge++;
            }

            // 如果边选够了，可以提前结束
            if (selected_edge == this->n - 1)
            {
                break;
            }
        }

        if (uf.size() != 1)
        {
            return -1;
        }

        return result;
    }

private:
    // 无需保持图的结构，只需要收集全部边就行
    vector<Node> graph;
    // 但是要注意保存节点个数
    int n;
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

    cout << graph.kruskal(0);
    return 0;
}