#include <iostream>
#include <list>
#include <vector>

template <typename K, typename V>
class MyChainingHashMap
{
    struct KVNode
    {
        K key;
        V value;
        KVNode(K key_, V value_) : key(key_), value(value_) {}
    };

    std::vector<std::list<KVNode>> table;

    size_t size;
    static const size_t INIT_CAP = 4;

    size_t hash(K key) const
    {
        size_t index = std::hash<K>{}(key) % table.size();
        return index;
    }

    void resize(size_t newCap)
    {
        // 防止为0，影响取模运算
        newCap = std::max(newCap, 1);
        MyChainingHashMap<K, V> newMap(newCap);
    }

public:
    MyChainingHashMap(size_t capacity) : table(capacity) {}

    // add || set
    void put(K key_, V value_)
    {
        size_t index = hash(key_);
        std::list<KVNode> &list = table[index]; // 不同key对应的同一index的单链

        // 链表为空，插入新节点
        if (list.empty())
        {
            list.push_back(KVNode(key_, value_));
            return;
        }

        // 如果该index有节点
        if (!list.empty())
        {
            // 遍历这个index的链表
            for (KVNode &temp : list)
            {
                // 找到了, 修改节点信息
                if (temp.key == key_)
                {
                    temp.value = value_;
                    return;
                }
            }

            // 没找到，插入新节点
            list.push_back(Node(key_, value_));
            return;
        }
    }
    // 查
    int get(int key_)
    {
        int index = hash(key_);
        std::list<Node> &list = table[index];
        for (const Node &temp : list)
        {
            // 找到了，返回值
            if (temp.key == key_)
            {
                return temp.value;
            }
        }
        // 没找到返回-1
        return -1;
    }
    // 删
    void remove(int key_)
    {
        int index = hash(key_);
        std::list<Node> &list = table[index];
        if (list.empty())
        {
            return;
        }

        auto isRemove = [key_](const Node &aNode)
        { return aNode.key == key_; };
        list.remove_if(isRemove);
    }
};

int main()
{

    return 0;
}