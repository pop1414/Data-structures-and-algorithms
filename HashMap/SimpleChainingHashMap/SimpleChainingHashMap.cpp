#include <iostream>
#include <list>
#include <vector>
#include <cassert>
class SimpleChainingHashMap
{
    struct Node
    {
        int key;
        int value;
        Node(int key_, int value_) : key(key_), value(value_) {}
    };

    std::vector<std::list<Node>> table;

public:
    SimpleChainingHashMap(int capacity) : table(capacity) {}

    int hash(int key) const
    {
        int index = key % table.size();
        return index;
    }
    // add || set
    void put(int key_, int value_)
    {
        int index = hash(key_);
        std::list<Node> &list = table[index]; // 不同key对应的同一index的单链

        // 链表为空，插入新节点
        if (list.empty())
        {
            list.push_back(Node(key_, value_));
            return;
        }

        // 如果该index有节点
        if (!list.empty())
        {
            // 遍历这个index的链表
            for (Node &temp : list)
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

    SimpleChainingHashMap map(5); // 容量为 5 的哈希表
    map.put(1, 10);
    map.put(2, 20);
    map.put(3, 30);
    std::cout << map.get(2) << std::endl; // 查询键 2
    map.put(2, 25);                       // 更新键 2 的值
    std::cout << map.get(2) << std::endl; // 再次查询键 2
    map.remove(2);                        // 删除键 2
    std::cout << map.get(2) << std::endl; // 查询已删除的键 2

    // 测试 1: 基本插入与查询
    {
        SimpleChainingHashMap map(10);
        map.put(1, 100);
        map.put(2, 200);
        assert(map.get(1) == 100); // 存在键
        assert(map.get(2) == 200);
        assert(map.get(3) == -1); // 不存在的键
        std::cout << "Test 1: Basic Insert & Get passed.\n";
    }

    // 测试 2: 值更新
    {
        SimpleChainingHashMap map(5);
        map.put(10, 50);
        assert(map.get(10) == 50);
        map.put(10, 999); // 更新已有键
        assert(map.get(10) == 999);
        std::cout << "Test 2: Value Update passed.\n";
    }

    // 测试 3: 删除操作
    {
        SimpleChainingHashMap map(5);
        map.put(3, 300);
        map.remove(3);
        assert(map.get(3) == -1); // 删除后应不存在
        map.remove(99);           // 删除不存在的键（无崩溃）
        std::cout << "Test 3: Remove Operation passed.\n";
    }

    // 测试 4: 哈希冲突处理（容量为3，键4和7的哈希值相同）
    {
        SimpleChainingHashMap map(3);
        map.put(4, 40); // 4 % 3 = 1
        map.put(7, 70); // 7 % 3 = 1 → 哈希冲突
        assert(map.get(4) == 40);
        assert(map.get(7) == 70);
        map.remove(4);
        assert(map.get(7) == 70); // 删除冲突链表中的节点后，其他节点仍可访问
        std::cout << "Test 4: Hash Collision Handling passed.\n";
    }

    // 测试 5: 边界条件（容量为1）
    {
        SimpleChainingHashMap map(1);
        map.put(0, 123);
        map.put(1, 456); // 哈希到同一位置
        assert(map.get(0) == 123);
        assert(map.get(1) == 456);
        map.remove(0);
        assert(map.get(1) == 456); // 删除后链表剩余节点仍有效
        std::cout << "Test 5: Edge Case (Capacity=1) passed.\n";
    }

    // 测试 6: 负数键处理（需确保哈希函数正确处理负数）
    {
        SimpleChainingHashMap map(5);
        map.put(-3, 100);
        assert(map.get(-3) == 100);
        map.put(-8, 200); // (-8 % 5 + 5) % 5 = 2
        assert(map.get(-8) == 200);
        std::cout << "Test 6: Negative Key Handling passed.\n";
    }
    //test7
    {
        SimpleChainingHashMap map(3);
        map.put(-1, 100);
        assert(map.get(-1) == 100); // 改进后应通过，未改进可能失败
    }
    std::cout << "All tests passed successfully!\n";
    return 0;
}