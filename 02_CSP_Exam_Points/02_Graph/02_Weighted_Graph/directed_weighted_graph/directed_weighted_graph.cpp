#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <queue>

using namespace std;

class Graph
{
public:
    struct Edge
    {
        int to;
        int weight;

        Edge(int t, int w) : to(t), weight(w) {}
    };

    explicit Graph(int n) : graph(n) {}

    void addEdge(int from, int to, int weight)
    {
        graph[from].emplace_back(to, weight);
    }

    void removeEdge(int from, int to)
    {
        auto &edges = graph[from];
        for (auto it = edges.begin(); it != edges.end(); it++)
        {
            if (it->to == to)
            {
                graph[from].erase(it);
                break;
            }
        }
    }

    bool hasEdge(int from, int to) const
    {
        const auto &edges = graph[from];
        for (const auto &edge : edges)
        {
            if (edge.to == to)
            {
                return true;
            }
        }
        return false;
    }

    int weight(int from, int to) const
    {
        const auto &edges = graph[from];
        for (const auto &edge : edges)
        {
            if (edge.to == to)
            {
                return edge.weight;
            }
        }
        throw invalid_argument("No such edge");
    }

    int getEdgeCount() const
    {
        int cnt = 0;
        for (const auto &neighbors : graph)
        {
            cnt += neighbors.size();
        }
        return cnt;
    }

    // 遍历所有节点DFS
    // 时间复杂度是 O(V+E)
    // 必定会访问所有节点 O(V)，对于每个被访问的节点，都会遍历它的所有边 O(E)
    void traverse(int s, vector<bool> &visited) const
    {
        if (s < 0 || s > graph.size() - 1)
        {
            return;
        }

        if (visited[s])
        {
            return;
        }

        visited[s] = true;
        cout << "visit " << s << endl;
        //  遍历s节点所有的邻居，然后递归
        for (const auto &edge : graph[s])
        {
            traverse(edge.to, visited);
        }
    }

    vector<int> findEulerianPath(int startNode)
    {

        if (!hasEulerianPath())
        {
            return {};
        }

        if (graph.size() == 0)
        {
            return {};
        }

        if (startNode < 0 || startNode > graph.size() - 1)
        {
            throw std::out_of_range("Start node index is out of graph range.");
        }

        vector<int> next_edge_idx(graph.size(), 0);
        vector<int> path;
        path.reserve(this->getEdgeCount() + 1);

        // 如果一个连通图每个顶点的入度等于出度（欧拉回路条件，）那么该图可以分解为若干个边不重复的简单环的并集
        // 所以正确的走环成为关键
        // 总是先执行深度的递归DFS（走环），最后才将curr压入
        // 所以从curr延申出去的环，都会在curr被标记完成之前（所有边遍历完），被完整地加入到path中
        auto dfs = [&](auto &self, int curr) -> void
        {
            const auto &neighbors = this->neighbors(curr);

            while (next_edge_idx[curr] < neighbors.size())
            {
                const auto &edge = neighbors[next_edge_idx[curr]++];
                int nextNode = edge.to;

                self(self, nextNode);
            }

            // 只有当curr节点的所有边都被遍历完，那么才会压入
            // 那说明最先被压入的是无路可走的终点
            path.push_back(curr);
        };

        dfs(dfs, startNode);

        reverse(path.begin(), path.end());

        return path;
    }

    void findSimplePaths(int curr, int target, vector<int> &visited, vector<int> &path, vector<vector<int>> &allPaths)
    {
        // 前序，更新当前节点
        // 为什么不判断visited[curr]，因为递归的时候做了条件限制
        visited[curr] = 1;
        path.push_back(curr);

        if (curr == target)
        {
            allPaths.push_back(path);
        }
        else
        {
            const auto &neighbors = this->neighbors(curr);
            for (const auto &edge : neighbors)
            {
                int nextNode = edge.to;
                // 只会递归访问未被访问过的节点
                if (visited[nextNode] != 1)
                {
                    findSimplePaths(nextNode, target, visited, path, allPaths);
                }
            }
        }
        visited[curr] = 0;
        path.pop_back();
    }

    void bfs(int start)
    {
        vector<int> visited(graph.size(), 0);
        queue<int> q;

        // 入队即标记
        q.push(start);
        visited[start] = 1;

        int step = 0;
        while (!q.empty())
        {
            int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                int curr = q.front();
                q.pop();

                cout << curr << "->";
                // 找到未访问过的节点，然后入队
                for (const auto &edge : graph[curr])
                {
                    if (visited[edge.to] == 1)
                    {
                        continue;
                    }
                    // 入队即标记
                    q.push(edge.to);
                    visited[edge.to] = 1;
                }
            }
            step++;
        }
    }

    vector<int> dijkstra(int start)
    {
        // start是起始点
        // dist数组记录从起始点到其余点的距最短离，初始化为INT_MAX；自身为0，dist[start] = 0
        vector<int> dist(graph.size(), INT_MAX);
        dist[start] = 0;

        // 按照pair的第一个元素排序
        // 用最小堆来暂时存放顶点与到顶点的距离,使用最小堆是因为这个算法是贪心算法
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({dist[start], start});

        // 为何不用visited，因为某个节点暂时入堆了，但是并不意味着这是最短路径，可能之后更新别的节点的数据会找到更优的路径（会再次入堆）
        // 除此之外的条件都不会让已经访问的节点入堆（也是visited的作用）
        // 这里体现了无权bfs与带权路径dijkstra的区别，无权的可视为权1，那么最短路径肯定是随着bfs一层一层更新，但是带权路径不一定，可能会经过许多的节点之后才找到最优的路径

        while (!min_heap.empty())
        {
            auto [start2curr_dist, curr] = min_heap.top();
            min_heap.pop();

            // 如果堆中的数据不比已知的优，那么就可以直接剪枝
            // 因为是min_heap，取出来的数据可能是非常旧的数据，但已经找到最优路径了，这个数据就可以不要了（因为是贪心算法）
            if (dist[curr] < start2curr_dist)
            {
                continue;
            }

            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                // 算的是当前节点的邻节点的数据
                // 因为当前节点的数据是否最优，上面已经判断过了
                // 只有当前节点的数据最优，才能保证邻节点的数据有可能最优
                int new_dist = start2curr_dist + edge.weight;
                if (new_dist < dist[next_node])
                {
                    dist[next_node] = new_dist;
                    min_heap.push({new_dist, next_node});
                }
            }
        }

        return dist;
    }


    // prim不需要遍历所有
    int prim(int start)
    {
        int n = graph.size();

        int selected_node = 0;
        int result = 0;

        // 记录每个节点到MST的最小边权
        vector<int> key(n, INT_MAX);
        key[start] = 0;

        vector<int> in_mst(n, 0);

        // 最小堆放入的是潜在的下一个被点亮的节点
        // 按照到mst的距离由小到大排序（最小堆）：贪心算法
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({key[start], start});

        while (!min_heap.empty())
        {
            auto [dist2mst, curr] = min_heap.top();
            min_heap.pop();

            // 若已加入mst或者距离不是最优的，跳过（该节点不应该被加入）
            // 下面的压入潜在节点已经限定了不在mst中，那为啥从堆中取出来的节点还要再做一次判断
            // 与dijk类似，curr可能被压入多次，因为距离大，被搁置。点亮其他节点的时候，发现key[curr]还有更小的
            // 那么curr被压入的次数大于1（也就是之前压入的数据可能是过期的），而取出过期的数据的时候，curr已经在mst中，所以还需要再次判断
            if (dist2mst > key[curr] || in_mst[curr])
            {
                continue;
            }

            // 点亮一个节点
            in_mst[curr] = 1;
            selected_node++;
            result += key[curr];

            // 遍历该节点的边
            // 看看是否能找到下一个潜在的节点
            for (const auto &edge : graph[curr])
            {
                int next_node = edge.to;
                int weight = edge.weight;

                // 潜在的节点未被加入，而且距离为已知最优，放入堆中
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

    // 进行n - 1轮迭代，因为最短路径最多包含n - 1条边（若包含环，正权：肯定不是最优；负权：无最短路径）
    // 每一轮遍历所有的边，进行松弛操作
    // 进行第n轮遍历，若还有节点更新，说明图中存在负权环
    pair<vector<int>, bool> bellman_ford(int start)
    {
        int n = graph.size();
        // 记录距离的数组
        vector<int> dist(n, INT_MAX);
        dist[start] = 0;

        for (int round = 0; round < n - 1; round++)
        {
            // 算法限制每轮遍历只能走一条边，也就是松弛操作的根据是上一轮的数据
            // 那我们修改dist_copy的数据，根据dist进行松弛；
            vector<int> dist_copy = dist;

            bool has_update = false;

            for (int node = 0; node < n; node++)
            {
                // 节点不可达，换下一个数组
                if (dist[node] == INT_MAX)
                {
                    continue;
                }

                for (const auto &edge : graph[node])
                {
                    int next_node = edge.to;
                    int new_dist = dist[node] + edge.weight;

                    // 为何要与dist_copy比较，copy不是改动的数组吗，与变化的数据比较不会出现错误吗
                    // 只需要确保上一轮的数据不要做变动（new_dist基于dist[node]），而next_node可视为下一轮的数据
                    // 下一轮的数据在遍历的时候，是属于草稿阶段，可以随意修改，而且要与草稿对比，才知道本轮遍历的时候的最优
                    // 距离new_dist = 1；new_dist = 2，如果dist[next_node] > 2，用dist来比较，可能无法得到最优的1
                    if (new_dist < dist_copy[next_node])
                    {
                        dist_copy[next_node] = new_dist;
                        has_update = true;
                    }
                }
            }

            // 同步数组
            dist = dist_copy;
            if (!has_update)
            {
                break;
            }
        }

        bool has_negative_cycle = false;
        // 最后一轮只要松弛判断出现更小值（说明有负权环），直接break，不用修改dist数据
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

                if (new_dist < dist[next_node])
                {
                    has_negative_cycle = true;
                    break;
                }
            }

            if (has_negative_cycle)
            {
                break;
            }
        }

        return {dist, has_negative_cycle};
    }

    pair<vector<int>, bool> SPFA(int start)
    {
        int n = graph.size();
        vector<int> dist(n, INT_MAX);

        queue<int> q;
        vector<bool> in_queue(n, false);
        // 记录进队次数，用于检测是否有负权环
        vector<int> cnt(n, 0);

        dist[start] = 0;
        q.push(start);
        in_queue[start] = true;
        cnt[start]++;

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            in_queue[curr] = false;

            if (dist[curr] != INT_MAX)
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
                    if (!in_queue[next_node])
                    {
                        q.push(next_node);
                        in_queue[next_node] = true;
                        cnt[next_node]++;

                        // next_node入队待更新，要检测入队次数是否超过限定值
                        if (cnt[curr] >= n)
                        {
                            return {dist, true};
                        }
                    }
                }
            }
        }

        return {dist, false};
    }

    const vector<Edge> &neighbors(int v)
    {
        if (v < 0 || v > graph.size() - 1)
        {
            throw out_of_range("Vertex index is out of graph range.");
        }
        return graph[v];
    }

private:
    vector<vector<Edge>> graph;

    bool hasEulerianPath() const
    {
        int n = graph.size();
        vector<int> in_degree(n, 0);
        vector<int> out_degree(n, 0);
        int total_edges = 0;

        // 遍历所有节点
        for (int u = 0; u < n; u++)
        {
            out_degree[u] = graph[u].size();
            total_edges += out_degree[u];
            // 遍历当前节点的所有边
            for (const auto &edge : graph[u])
            {
                // 某一节点的入度只能由其他节点的边体现
                in_degree[edge.to]++;
            }
        }

        int start_nodes = 0;
        int end_nodes = 0;
        // 检查度数条件
        for (int i = 0; i < n; i++)
        {
            if (in_degree[i] == out_degree[i])
            {
                continue;
            }
            // 出度比入度多一，潜在的起点
            else if (out_degree[i] - in_degree[i] == 1)
            {
                start_nodes++;
            }
            // 入度比出度多一，潜在的终点
            else if (in_degree[i] - out_degree[i] == 1)
            {
                end_nodes++;
            }
        }

        return (start_nodes == 0 && end_nodes == 0) || (start_nodes == 1 && end_nodes == 1);
    }
};

int main()
{
    Graph graph(4);
    graph.addEdge(3, 1, 1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(3, 2, 3);

    vector<int> result = graph.findEulerianPath(3);
    for (int node : result)
    {
        cout << node << "->";
    }
    cout << '\n';

    vector<int> path;
    vector<int> visited(4, 0);
    vector<vector<int>> allPaths;
    graph.findSimplePaths(1, 2, visited, path, allPaths);

    // for (const auto &path : allPaths)
    // {
    //     for (int node : path)
    //     {
    //         cout << node << "->";
    //     }
    //     cout << '\n';
    // }

    graph.bfs(1);

    return 0;
}