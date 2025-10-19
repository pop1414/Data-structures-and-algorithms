#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        return DFSTraverse(graph);
    }

    bool DFSTraverse(vector<vector<int>> &graph)
    {
        vector<int> vertices = getAllVertices(graph);

        vector<int> color(vertices.size(), -1); // -1未染色， 染色0或

        for (int vertex : vertices)
        {
            // 还未遍历过，主要是为了解决非连通图
            // 连通图通过一个节点很有可能就直接遍历完所有的节点
            // 而还要for循环所有节点就是为了处理非连通图
            if (color[vertex] == -1)
            {
                if (!DFS(vertex, 0, color, graph))
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool DFS(int from, int col, vector<int> &color, vector<vector<int>> &graph)
    {
        color[from] = col;

        vector<int> neighbors = graph[from];

        // 内层递归着色
        for (int neighbor : neighbors)
        {
            if (color[neighbor] == -1)
            {
                // 往下遍历的时候出现false，那就中断遍历邻居
                if (!DFS(neighbor, 1 - col, color, graph))
                {
                    return false;
                }
            }
            else
            {
                if (color[from] == color[neighbor])
                {
                    return false;
                }
            }
        }

        // 遍历了所有邻居都没问题
        return true;
    }

    vector<int> getAllVertices(vector<vector<int>> &graph)
    {
        unordered_set<int> vertexSet;

        for (int i = 0; i < graph.size(); i++)
        {
            vertexSet.insert(i);
        }

        return vector<int>(vertexSet.begin(), vertexSet.end());
    }
};