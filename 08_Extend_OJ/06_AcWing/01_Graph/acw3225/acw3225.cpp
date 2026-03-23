#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
public:
    struct Node
    {
        int to;
        int weight;
        bool visited;

        Node(int t, int w) : to(t), weight(w), visited(false) {}
    };

    Graph(int size) : n(size), graph(size) {}

    void addEdge(int from, int to, int weight)
    {
        graph[from].emplace_back(to, weight);
    }

    // 无向图与有向图有区别
    // 访问u的边的时候，要把边变成已访问，不然访问v的时候，这条反边会再访问一次
    vector<int> findEulerPath(int start)
    {

        if (!hasEuler())
        {
            return vector<int>();
        }

        vector<int> path;
        stack<int> st;

        for (auto &edges : graph)
        {
            sort(edges.begin(), edges.end(), [](const auto &edge_a, const auto &edge_b)
                 { return edge_a.to < edge_b.to; });
        }

        st.push(start);
        while (!st.empty())
        {
            int curr = st.top();
            // 是否有未访问的边
            bool has_unvisited = false;

            for (auto &edge : graph[curr])
            {
                if (!edge.visited)
                {
                    edge.visited = true;
                    // 有未访问的边
                    has_unvisited = true;
                    int next_node = edge.to;
                    st.push(next_node);

                    // 找到反边设为已标记
                    for (auto &re_edge : graph[next_node])
                    {
                        if (re_edge.to == curr)
                        {
                            // 找到了直接退出
                            re_edge.visited = true;
                            break;
                        }
                    }

                    // 找到一条未访问的边就退出循环，进入新压入的节点循环
                    break;
                }
            }

            // 没有未访问的边，即所有的邻边都被访问了
            if (!has_unvisited)
            {
                st.pop();
                path.push_back(curr);
            }
        }

        reverse(path.begin(), path.end());

        return path;
    }

private:
    vector<vector<Node>> graph;
    int n;

    // 无向图，所有的节点的度都为偶数，起点与终点相同；存在两个奇数节点，一个为起点，一个为终点
    // 有向图，所有节点入度出度相同，起点与终点相同；存在两个节点入度出度不同，起点出度比入度多一，终点反之
    bool hasEuler()
    {
        // 要先判断是否连通
        if (!is_connected())
        {
            return false;
        }

        vector<int> degree(this->n, 0);

        for (int node = 0; node < this->n; node++)
        {
            // node的度
            degree[node] += graph[node].size();
        }

        int odd = 0;
        for (int d : degree)
        {
            // 判断奇数节点个数
            if (d % 2 != 0)
            {
                odd++;
                // 大于2就不存在欧拉路径
                if (odd > 2)
                {
                    return false;
                }
            }
        }

        // 题目限定从1开始出发，如果1不是合法起点就返回-1
        if (odd == 2 && degree[0] % 2 == 0)
        {
            return false;
        }

        return true;
    }

    // bfs
    bool is_connected()
    {
        int start = 0;
        queue<int> q;

        vector<int> visited(this->n, 0);
        // 入队设置已访问
        q.push(start);
        visited[start] = 1;
        int selected_node = 0;

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            selected_node++;

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                if (!visited[next_node])
                {
                    q.push(next_node);
                    visited[next_node] = 1;
                }
            }
        }

        if (selected_node != this->n)
        {
            return false;
        }

        return true;
    }
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
    // uf.connected(0, n - 1)
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b;
        graph.addEdge(a - 1, b - 1, 1);
        graph.addEdge(b - 1, a - 1, 1);
    }

    vector<int> result = graph.findEulerPath(0);
    if (result.empty())
    {
        cout << -1;
    }
    else
    {
        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i] + 1;
            if (i != result.size() - 1)
            {
                cout << " ";
            }
        }
    }

    return 0;
}