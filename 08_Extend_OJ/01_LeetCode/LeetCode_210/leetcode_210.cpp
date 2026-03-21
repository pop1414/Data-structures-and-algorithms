#include <iostream>
#include <vector>
#include <algorithm>

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

    Graph(int numCourses, vector<vector<int>> &prerequisites)
    {
        graph.resize(numCourses);

        for (const auto &edge : prerequisites)
        {
            int from = edge[1];
            int to = edge[0];

            addEdge(from, to, 1);
        }
    }

    void addEdge(int from, int to, int weight)
    {
        graph[from].emplace_back(to, weight);
    }

    vector<int> hasCycleDFS(int n)
    {
        vector<int> onPaths(n, 0);
        vector<int> visited(n, 0);
        vector<int> postOrder;

        bool hasCycle = false;

        auto traverse = [&](auto &self, bool &hasCycle, int node) -> void
        {
            if (hasCycle)
            {
                return;
            }

            if (onPaths[node])
            {
                hasCycle = true;
                return;
            }

            if (visited[node])
            {
                return;
            }

            onPaths[node] = 1;
            visited[node] = 1;

            for (const auto &edge : graph[node])
            {
                int next_node = edge.to;
                self(self, hasCycle, next_node);
            }

            onPaths[node] = false;
            postOrder.push_back(node);
        };

        for (int node = 0; node < n; node++)
        {
            traverse(traverse, hasCycle, node);
        }

        if (hasCycle)
        {
            return vector<int>();
        }

        reverse(postOrder.begin(), postOrder.end());

        return postOrder;
    }

private:
    vector<vector<Node>> graph;
};

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        Graph graph(numCourses, prerequisites);
        return graph.hasCycleDFS(numCourses);
    }
};