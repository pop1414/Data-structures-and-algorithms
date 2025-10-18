#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        Node *newGraph = new Node();

        // 将原图的顶点与新图的顶点链接起来
        unordered_map<Node *, Node *> cloned;
        DFS(node, cloned);

        return cloned[node];
    }

    void DFS(Node *node, unordered_map<Node *, Node *> &cloned)
    {
        // 说明原图节点已被克隆过
        if (cloned.find(node) != cloned.end())
        {
            return;
        }

        Node *newNode = new Node(node->val);

        cloned[node] = newNode;

        for (Node *neighbor : node->neighbors)
        {
            DFS(neighbor, cloned);
            // 由映射来得到新的节点
            newNode->neighbors.push_back(cloned[neighbor]);
        }
    }
};