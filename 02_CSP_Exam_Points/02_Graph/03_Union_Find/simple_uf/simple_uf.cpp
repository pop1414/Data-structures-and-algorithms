#include <iostream>
#include <vector>

using namespace std;

class UF
{
private:
    vector<int> parent;
    // 连通分量个数
    int cnt;

    // 每个连通分量的节点个数
    vector<int> _size;

public:
    UF(int n)
    {
        parent.resize(n);
        _size.resize(n);
        cnt = n;
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            _size[i] = 1;
        }
    }

    // 实现了路径压缩
    int find(int x)
    {

        // 该递归函数一直找到root
        // 然后回溯的时候，把每个x的parent[x]都赋值为root
        // 即该连通分量压缩成了两层
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void union_(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);

        if (rootP == rootQ)
        {
            return;
        }

        parent[rootP] = rootQ;
        cnt--;

        _size[rootQ] += _size[rootP];
    }

    bool connected(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);

        return rootP == rootQ;
    }

    int count() const
    {
        return cnt;
    }

    int size(int x) const
    {
        return _size[x];
    }
};