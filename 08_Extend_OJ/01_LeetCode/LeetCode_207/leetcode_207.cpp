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

    bool hasCycleDFS(int n)
    {
        vector<int> onPaths(n, 0);
        vector<int> visited(n, 0);

        bool hasCycle = false;

        auto traverse = [&](auto &self, bool &hasCycle, int node)
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
        };

        for (int node = 0; node < n; node++)
        {
            traverse(traverse, hasCycle, node);
        }

        return hasCycle;
    }

private:
    vector<vector<Node>> graph;
};

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        Graph graph(numCourses, prerequisites);
        return !graph.hasCycleDFS(numCourses);
    }
};