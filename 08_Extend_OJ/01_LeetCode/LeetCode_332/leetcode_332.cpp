#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

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

    Graph(vector<vector<string>> &tickets)
    {

        vector<string> airports;
        for (const auto &ticket : tickets)
        {
            string from = ticket[0];
            string to = ticket[1];

            airports.push_back(from);
            airports.push_back(to);
        }

        sort(airports.begin(), airports.end());
        // 去重必须要是排序好的容器
        airports.erase(unique(airports.begin(), airports.end()), airports.end());

        id2str = airports;
        for (int i = 0; i < id2str.size(); i++)
        {
            // id2str已经是排序好的（字典序）
            // 此时就可以强制ID顺序等于字典序
            str2node[id2str[i]] = i;
        }

        graph.resize(id2str.size());
        for (const auto &ticket : tickets)
        {
            addEdge(str2node[ticket[0]], str2node[ticket[1]], 1);
        }

        // 至此完成了建图，而ID的大小与字符串的字典序大小相同
        // 那么只要排序邻居，之后的遍历就是按照字典序大小遍历

        // 排序邻居，此时排序的是int，比string更快

        for (auto &neighbors : graph)
        {
            sort(neighbors.begin(), neighbors.end(), [&](const Edge &a, const Edge &b)
                 { return a.to < b.to; });
        }
    }

    void addEdge(int from, int to, int weight)
    {
        // 注意需要构建Edge对象，有两个成员变量，所以要传入两个参数
        graph[from].emplace_back(to, weight);
    }

    const vector<Edge> &getNeighbors(int v) const
    {
        return graph[v];
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

    vector<string> findEulerPath()
    {
        int startNode = str2node.at("JFK");
        vector<int> idPath = findEulerianPath(startNode);
        vector<string> result;
        for (int node : idPath)
        {
            string airport = id2str.at(node);
            result.push_back(airport);
        }
        return result;
    }

private:
    vector<vector<Edge>> graph;
    unordered_map<string, int> str2node;
    vector<string> id2str;

    vector<int> findEulerianPath(int startNode)
    {

        vector<int> path;
        // 欧拉路径节点数 = 边数 + 1
        path.reserve(this->getEdgeCount() + 1);
        // 用于记录每个节点还未被删除的边，通过next_edge_idx[curr]++来“删除”被访问的边
        // 现在的问题是，节点是由字符串存储的，无法用节点来作索引
        vector<int> next_edge_idx(graph.size(), 0);

        auto dfs = [&](auto &self, int curr) -> void
        {
            // 想要后面获得具体的边，就需要先得到当前节点的邻居集合
            const auto &neighbors = this->getNeighbors(curr);

            while (next_edge_idx[curr] < neighbors.size())
            {
                const auto &edge = neighbors[next_edge_idx[curr]++];
                int nextNode = edge.to;

                self(self, nextNode);
            }

            path.push_back(curr);
        };

        dfs(dfs, startNode);
        reverse(path.begin(), path.end());

        return path;
    }
};

class Solution
{
public:
    vector<string> findItinerary(vector<vector<string>> &tickets)
    {
        Graph graph(tickets);
        return graph.findEulerPath();
    }
};

int main()
{
    return 0;
}