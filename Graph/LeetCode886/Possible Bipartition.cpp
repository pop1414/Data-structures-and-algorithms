#include <bits/stdc++.h>

using namespace std;

class graph
{

private:
    unordered_map<int, vector<pair<int, int>>> adjList; // 顶点 -> 邻居节点<节点，权重>

    // 这道题是无向图，所以value默认是1
    void addEdge(int from, int to, int value = 1)
    {
        if (adjList.find(from) == adjList.end())
        {
            adjList[from] = {};
        }

        if (adjList.find(to) == adjList.end())
        {
            adjList[to] = {};
        }

        adjList[from].push_back({to, value});
        adjList[to].push_back({from, value});
    }

    bool DFS(vector<vector<int>> &dislikes, vector<int> &color, int start, int col)
    {

        color[start - 1] = col;

        auto &neighbors = adjList[start];

        for (auto &[neighbor, weight] : neighbors)
        {
            // 未被染色
            if (color[neighbor - 1] == -1)
            {
                if (!DFS(dislikes, color, neighbor, 1 - col))
                {
                    return false;
                }
            }
            //  被染色过则比较颜色
            else
            {
                if (color[start - 1] == color[neighbor - 1])
                {
                    return false;
                }
            }
        }

        return true;
    }

public:
    graph(vector<vector<int>> &dislikes)
    {
        for (auto &group : dislikes)
        {
            int from = group[0];
            int to = group[1];

            addEdge(from, to);
        }
    }

    bool DFSTraverse(vector<vector<int>> &dislikes, int n)
    {

        vector<int> color(n, -1); // -1未染色，染色0或1

        for (int i = 1; i <= n; i++)
        {
            if (color[i - 1] == -1)
            {
                if (!DFS(dislikes, color, i, 0))
                {
                    return false;
                }
            }
        }

        return true;
    }
};

class Solution
{
public:
    bool possibleBipartition(int n, vector<vector<int>> &dislikes)
    {
        graph g(dislikes);
        return g.DFSTraverse(dislikes, n);
    }
};