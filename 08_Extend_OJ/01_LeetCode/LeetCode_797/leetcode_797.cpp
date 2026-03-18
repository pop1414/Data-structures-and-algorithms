#include <iostream>
#include <vector>

using namespace std;

void findSimplePaths(int curr, int target, vector<int> &visited, vector<int> &path, vector<vector<int>> &allPaths, vector<vector<int>> &graph)
{
    visited[curr] = 1;
    path.push_back(curr);

    if (curr == target)
    {
        allPaths.push_back(path);
    }
    else
    {
        const auto &neighbors = graph[curr];
        for (int i = 0; i < neighbors.size(); i++)
        {
            int nextNode = neighbors[i];
            if (visited[nextNode] == 0)
            {
                findSimplePaths(nextNode, target, visited, path, allPaths, graph);
            }
        }
    }

    visited[curr] = 0;
    path.pop_back();
}

class Solution
{
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> visited(n, 0);
        vector<int> path;
        vector<vector<int>> allPaths;

        findSimplePaths(0, n - 1, visited, path, allPaths, graph);
        return allPaths;
    }
};