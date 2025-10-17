#include <bits/stdc++.h>

using namespace std;

class Graph
{

private:
    unordered_map<int, vector<pair<int, int>>> adjList; // 顶点-> (邻接节点，权重）

    int vertices;  // 顶点数
    bool directed; // 是否为有向图

    void DFS(int from, unordered_set<int> &vertexSet)
    {
        // 将当前节点设为已访问（正在访问）
        vertexSet.insert(from);

        auto neighbors = getNeighbors(from);
        for (const auto &[neighbor, weight] : neighbors)
        {
            // 如果邻居节点没有被访问过，那就DFS邻居节点
            if (vertexSet.find(neighbor) == vertexSet.end())
            {
                DFS(neighbor, vertexSet);
            }
        }
    }

    void findAllPathsDFS(int curr, unordered_set<int> &visited, vector<int> &onPath, vector<vector<int>> allPaths)
    {
        onPath.push_back(curr);

        allPaths.push_back(onPath);

        auto neighbors = getNeighbors(curr);
        for (const auto &[neighbor, weight] : neighbors)
        {
            // 邻居没有被访问过，DFS邻居
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                findAllPathsDFS(neighbor, visited, onPath, allPaths);
                visited.erase(neighbor);
            }
        }

        onPath.pop_back();
    }

public:
    // 默认设置为无向图
    Graph(int v = 0, bool dir = false) : vertices(v), directed(dir) {}

    void addEdge(int from, int to, int weight = 1)
    {
        adjList[from].push_back({to, weight});
        // 如果为无向图，再给反向加边
        if (!directed)
        {
            adjList[to].push_back({from, weight});
        }
    }

    void removeEdge(int from, int to)
    {
        // 取得从from节点的所有出边
        auto &edges = adjList[from];
        // remove_if,从头迭代到尾，每一条边如果p.fist == to说明要被删除
        edges.erase(remove_if(edges.begin(), edges.end(), [to](const pair<int, int> &p)
                              { return p.first == to; }),
                    edges.end());

        if (!directed)
        {
            auto &revEdges = adjList[to];
            revEdges.erase(remove_if(revEdges.begin(), revEdges.end(), [from](const pair<int, int> &p)
                                     { return p.first == from; }),
                           revEdges.end());
        }
    }

    bool isAdjacent(int from, int to)
    {
        if (adjList.find(from) == adjList.end())
        {
            return false;
        }

        auto &neighbors = adjList[from];
        for (auto &[neighbor, weight] : neighbors)
        {
            if (neighbor == to)
            {
                return true;
            }
        }

        return false;
    }

    optional<int> getEdgeWeight(int from, int to)
    {
        if (adjList.find(from) == adjList.end())
        {
            return nullopt;
        }

        auto &neighbors = adjList[from];
        for (const auto &[neighbor, weight] : neighbors)
        {
            if (neighbor == to)
            {
                return weight;
            }
        }
        return nullopt;
    }

    vector<pair<int, int>> getNeighbors(int from)
    {
        if (adjList.find(from) == adjList.end())
        {
            return {};
        }

        return adjList[from];
    }

    // 含有孤立点
    // vector<int> getAllVertices()
    // {
    //     // 用Set是因为处理两种情况的时候有些节点会重复
    //     unordered_set<int> vertecSet;
    //     // 处理所有作为起点的节点
    //     for (const auto &[vertex, _] : adjList)
    //     {
    //         vertecSet.insert(vertex);
    //     }
    //     // 处理孤立节点与只有入边的节点
    //     for (const auto &[vertex, neighbors] : adjList)
    //     {
    //         for (const auto &[neighbor, weight] : neighbors)
    //         {
    //             vertecSet.insert(neighbor);
    //         }
    //     }
    //     return vector<int>(vertecSet.begin(), vertecSet.end());
    // }

    // 无孤立点
    vector<int> getAllvertices()
    {
        // 可能有同时作为起点与终点的节点，所以用set
        unordered_set<int> vertexSet;

        // 所有起点
        for (const auto &[vertex, neighbors] : adjList)
        {
            vertexSet.insert(vertex);
            for (const auto &[neighbor, weight] : neighbors)
            {
                // 所有终点
                vertexSet.insert(neighbor);
            }
        }

        return vector<int>(vertexSet.begin(), vertexSet.end());
    }

    void DFSTraverse()
    {

        unordered_set<int> vertexSet;

        auto vertices = getAllvertices();

        for (int vertex : vertices)
        {
            if (vertexSet.find(vertex) == vertexSet.end())
            {
                DFS(vertex, vertexSet);
            }
        }
    }

    vector<vector<int>> findAllPaths(int start)
    {
        vector<vector<int>> allPaths;
        vector<int> onPath;
        unordered_set<int> visited;

        visited.insert(start);

        findAllPathsDFS(start, visited, onPath, allPaths);

        return allPaths;
    }

    void printGraph()
    {
        cout << "Graph structure (" << (directed ? "directed" : "undirected") << "):\n";
        for (const auto &[vertex, neighbors] : adjList)
        {
            cout << vertex << " -> ";
            for (const auto &[neighbor, weight] : neighbors)
            {
                cout << "(" << neighbor << ", w:" << weight << ") ";
            }
            cout << endl;
        }
    }

    unordered_map<int, int> BFS(int start)
    {
        unordered_set<int> visited;
        unordered_map<int, int> steps;
        queue<int> q;

        q.push(start);
        steps[start] = 0; // 初始化0为了方便记录步数
        visited.insert(start);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            auto neighbors = getNeighbors(curr);
            for (const auto &[neighbor, weight] : neighbors)
            {
                if (visited.find(neighbor) == visited.end())
                {
                    q.push(neighbor);
                    steps[neighbor] = steps[curr] + 1;
                    visited.insert(neighbor);
                }
            }
        }

        return steps;
    }
};

// 示例使用
int main()
{
    // 创建无向图
    cout << "=== Undirected Graph ===\n";
    Graph g1(5, false);
    g1.addEdge(0, 1, 2);
    g1.addEdge(0, 2, 3);
    g1.addEdge(1, 3, 1);
    g1.addEdge(2, 3, 4);
    g1.addEdge(3, 4, 2);

    g1.printGraph();
    cout << endl;

    // 测试基础操作
    cout << "=== Basic Operations ===\n";

    // 判断相邻
    cout << "Is 0 adjacent to 1? " << (g1.isAdjacent(0, 1) ? "Yes" : "No") << endl;
    cout << "Is 0 adjacent to 3? " << (g1.isAdjacent(0, 3) ? "Yes" : "No") << endl;

    // 获取边的权重
    auto weight = g1.getEdgeWeight(0, 1);
    if (weight)
    {
        cout << "Weight of edge (0 -> 1): " << *weight << endl;
    }
    else
    {
        cout << "Edge (0 -> 1) does not exist\n";
    }

    weight = g1.getEdgeWeight(0, 4);
    if (weight)
    {
        cout << "Weight of edge (0 -> 4): " << *weight << endl;
    }
    else
    {
        cout << "Edge (0 -> 4) does not exist\n";
    }

    // 获取邻居节点
    cout << "\nNeighbors of vertex 0:\n";
    auto neighbors = g1.getNeighbors(0);
    for (const auto &[neighbor, w] : neighbors)
    {
        cout << "  -> " << neighbor << " (weight: " << w << ")\n";
    }

    cout << "\nNeighbors of vertex 3:\n";
    neighbors = g1.getNeighbors(3);
    for (const auto &[neighbor, w] : neighbors)
    {
        cout << "  -> " << neighbor << " (weight: " << w << ")\n";
    }

    // BFS测试
    cout << "\n=== BFS with Step Count ===\n";
    auto stepsFromZero = g1.BFS(0);
    cout << "Summary of steps from node 0:\n";
    for (const auto &[node, step] : stepsFromZero)
    {
        cout << "Node " << node << ": " << step << " steps\n";
    }

    // 创建有向图
    cout << "\n=== Directed Graph ===\n";
    Graph g2(4, true);
    g2.addEdge(0, 1, 5);
    g2.addEdge(0, 2, 3);
    g2.addEdge(1, 2, 2);
    g2.addEdge(2, 3, 7);

    g2.printGraph();
    cout << endl;

    // 有向图测试
    cout << "Is 0 adjacent to 1? " << (g2.isAdjacent(0, 1) ? "Yes" : "No") << endl;
    cout << "Is 1 adjacent to 0? " << (g2.isAdjacent(1, 0) ? "Yes" : "No") << endl;

    cout << "\nNeighbors of vertex 0 (out-edges):\n";
    neighbors = g2.getNeighbors(0);
    for (const auto &[neighbor, w] : neighbors)
    {
        cout << "  -> " << neighbor << " (weight: " << w << ")\n";
    }

    // BFS测试 - 有向图
    cout << "\n=== BFS with Step Count (Directed Graph) ===\n";
    auto stepsFromZeroDirected = g2.BFS(0);
    cout << "Summary of steps from node 0:\n";
    for (const auto &[node, step] : stepsFromZeroDirected)
    {
        cout << "Node " << node << ": " << step << " steps\n";
    }

    return 0;
}