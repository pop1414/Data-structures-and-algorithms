#include <iostream>
#include <queue>

using namespace std;

// 场景：存储节点（id + 距离），按距离升序（最小堆）
struct Node
{
    int id;
    int dist;
};

struct CompareNode
{
    bool operator()(const Node &a, const Node &b)
    {
        // greater(谁大谁放下层)
        // 最小堆
        return a.dist > b.dist;
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

    priority_queue<Node, vector<Node>, CompareNode> custom_min_heap;
    vector<Node> nodes;
    int id, dist;
    while (cin >> id >> dist)
    {
        Node node = {id, dist};
        nodes.push_back(node);
        custom_min_heap.push(node);
    }

    if (!custom_min_heap.empty())
    {
        cout << custom_min_heap.top().id << " " << custom_min_heap.top().dist;
    }
    else
    {
        cout << "优先级队列为空，无数据可输出！" << endl;
    }

    return 0;
}