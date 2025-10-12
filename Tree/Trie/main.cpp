#include <bits/stdc++.h>

using namespace std;

// 根据ASCII索引来往下递归
// 需要size来记录树中的节点树
// TrieNode* getNode(string key)，返回key最后一个单词的对应的节点，如果无返回null
// optional<V> get(string key)，返回key对应的val（一般表示单词的出现次数或权重等），若无返回nullopt, 用getNode得到节点，然后用节点来判断
// bool containsKey(string key)，判断key是否在树中，用get看看是否为null
// bool hasKeyWithPrefix(string prefix)，判断是否存在有指定前缀的键
// string shortestPrefixOf(string query)，查找key最短的、是查询字符串前缀的键（注意，前提是键），如果没有返回""
// string longestPrefixOf(string query)，同理
// vector<string> keysWithPrefix(string prefix)，得到所有具有指定前缀的键
// vector<string> keysWithPattern(string pattern)，使用通配符模式搜索所有匹配的键
// bool hasKeysWithPattern(string pattern), 判断是否存在匹配通配符模式的键

template <typename V>
class TrieMap
{
private:
    struct TrieNode
    {
        optional<V> val;
        // 用hashmap模拟，树枝存储字符，节点存储val(optional)
        // 用的是智能指针，TrieNode无需*
        unordered_map<char, unique_ptr<TrieNode>> children;

        TrieNode() : val(nullopt) {}
        // 用于判断当前节点是否存在一个有效值，还是nullopt
        bool isEnd()
        {
            return val.has_value();
        }
    };

    unique_ptr<TrieNode> root;
    int size;

    /**
     * @brief 根据键查找对应的节点
     *
     * @param key 要查找的键
     * @return TrieNode* 找到的节点指针，若不存在返回nullptr
     */
    TrieNode *getNode(const string &key)
    {
        TrieNode *curr = root.get();
        for (char c : key)
        {
            if (curr->children.find(c) == curr->children.end())
            {
                return nullptr;
            }
            curr = curr->children[c].get();
        }

        return curr;
    }

    /**
     * @brief 递归收集所有以指定前缀开头的键
     *
     * @param node 当前遍历的根节点
     * @param prefix 当前累积的前缀字符串
     * @param results 存储结果的向量
     *
     * 是函数keysWithPrefix的辅助函数
     */
    void collectKeys(TrieNode *root, string prefix, vector<string> &results)
    {
        if (root == nullptr)
        {
            return;
        }

        if (root->isEnd())
        {
            results.push_back(prefix);
        }

        // DFS树
        for (auto &[c, child] : root->children)
        {
            collectKeys(child.get(), prefix + c, results);
        }
    }

    /**
     * @brief 通配符匹配的递归辅助函数
     *
     * @param node 当前遍历的节点
     * @param pattern 匹配模式
     * @param index 当前匹配到模式的位置
     * @param prefix 当前累积的字符串
     * @param results 存储匹配结果的向量
     */
    void collectKeysWithPattern(TrieNode *node, const string &pattern, int index, string prefix, vector<string> &results)
    {
        // 当树为空的时候直接返回
        if (!node)
        {
            return;
        }

        // 要找到的是键，所以当index满足条件的时候，就要判断是否找到了一个键
        if (index == pattern.size())
        {
            if (node->isEnd())
            {
                results.push_back(prefix);
            }
            return;
        }

        char c = pattern[index];
        // 当是通配符的时候，遍历所有子节点
        if (c == '.')
        {
            for (auto &[ch, child] : node->children)
            {
                // 注意传入的参数是子节点对应的字符，而不是通配符
                collectKeysWithPattern(child.get(), pattern, index + 1, prefix + ch, results);
            }
        }
        else
        {
            // 当字符对应的子节点存在时再往下递归
            if (node->children.find(c) != node->children.end())
            {
                collectKeysWithPattern(node->children[c].get(), pattern, index + 1, prefix + c, results);
            }
        }
    }

    /**
     * @brief 检查是否存在匹配模式指定的键
     *
     * @param node 当前遍历的节点
     * @param patter 匹配模式
     * @param index 当前匹配到模式的位置
     * @return bool 如果存在至少一个键返回true， 反之返回false
     *
     * 偷懒直接使用keysWithPattern也行，但是那个找到了全部的匹配键，时间复杂度高，这个只需要找到一个就行，不需要回溯，即不需要prefix来记录回溯的字符串，直接一股脑的往下递归，有就只遍历这一个，没有就没有
     */
    bool hasMatchingKey(TrieNode *node, const string &pattern, int index)
    {
        // 树为空的情况
        if (!node)
        {
            return false;
        }

        // 找到一个直接返回true
        if (index == pattern.size())
        {
            if (node->isEnd())
            {
                return true;
            }
        }

        char c = pattern[index];
        if (c == '.')
        {
            for (auto &[ch, child] : node->children)
            {
                // 如果没有找到，那就继续遍历
                if (hasMatchingKey(child.get(), pattern, index + 1))
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            if (node->children.find(c) != node->children.end())
            {
                // 不是通配符就只有一条路，直接return就行
                return hasMatchingKey(node->children[c].get(), pattern, index + 1);
            }
            else
            {
                return false;
            }
        }
    }

    /**
     * @brief 删除节点的递归辅助函数
     *
     * @param node 当前遍历的节点
     * @param key 要删除的键
     * @param index 当前处理到键的位置
     * @return bool 如果当前节点可以被删除返回 true，否则返回 false
     */
    bool removeHelper(TrieNode *node, const string &key, int index)
    {
        // 递归找到键值，后跟回溯判断是否删除
        if (index == key.length())
        {
            if (!node->isEnd())
            {
                return false; // key不存在
            }
            node->val = nullopt;
            size--;
            return node->children.empty(); // 如果有子节点就不能删
        }

        char c = key[index];
        if (node->children.find(c) == node->children.end())
        {
            return false;
        }

        bool shouldDeleteChild = removeHelper(node->children[c].get(), key, index + 1);

        if (shouldDeleteChild)
        {
            node->children.erase(c);                         // 删除子节点
            return !node->isEnd() && node->children.empty(); // 返回当前节点的信息，让父节点决定删不删除
        }

        // 如果子节点（上面的if）都没被删除，该节点更不可能被删除
        return false;
    }

public:
    TrieMap() : root(make_unique<TrieNode>()), size(0) {}

    void put(const string &key, V val)
    {
        if (key.empty())
            return;

        TrieNode *curr = root.get();
        // 先判断孩子是否存在，存在往下走，不存在先创建新孩子再往下走
        for (char c : key)
        {
            // 当前节点没有c这个树枝（即无孩子）
            if (curr->children.find(c) == curr->children.end())
            {
                curr->children[c] = make_unique<TrieNode>(); // 注意没有*
            }
            curr = curr->children[c].get(); // 注意不要少了get()
        }

        // 根据节点的值，来判断是否是新键插入（size++），还是旧键修改
        if (!curr->isEnd())
        {
            size++;
        }

        curr->val = val;
    }

    /**
     * @brief 删除键及其对应的值
     *
     * @param key 要删除的键
     *
     * 如果键不存在或为空字符串，则不执行任何操作。
     */
    void remove(const string &key)
    {
        if (key.empty())
        {
            return;
        }
        removeHelper(root.get(), key, 0);
    }

    /**
     * @brief 搜索键对应的值
     *
     * @param key 要查找的键
     * @return optional<V> 如果键存在返回对应的值，否则返回nullopt
     */
    optional<V> get(const string &key)
    {
        TrieNode *node = getNode(key);
        // 如果无节点或者节点的值为空
        if (node == nullptr || !node->isEnd())
        {
            return nullopt;
        }
        return node->val;
    }

    /**
     * @brief 判断键是否在map中
     *
     * @param key 要查找的键
     * @return bool 如果存在返回true，反之false
     */
    bool containsKey(const string &key)
    {
        // 不存在get返回nullopt,条件语句不成立，返回false；正确
        return get(key) != nullopt;
    }

    /**
     * @brief 判断是否存在具有指定前缀的键
     *
     * @param prefix 指定的键
     * @return bool 如果至少存在一个具有该前缀的键返回true，反之false
     */
    bool hasKeyWithPrefix(const string &prefix)
    {
        // 用getNode(prefix)找到了前缀在map中存在（!= nullptr），符合条件的键一定存在
        return getNode(prefix) != nullptr;
    }

    /**
     * @brief 在map中查找最短的、是查询query最短前缀的键
     *
     * @param query 查询字符串
     * @return string 返回map中是query前缀的最短键，无返回空字符串
     */
    string shortestPrefixOf(const string &query)
    {
        TrieNode *curr = root.get();
        for (int i = 0; i < query.length(); i++)
        {
            char c = query[i];
            if (curr->children.find(c) == curr->children.end())
            {
                return "";
            }

            // 因为是树枝（字母）索引，所以先要索引到达节点，再判断是否为键
            curr = curr->children[c].get();

            if (curr->isEnd())
            {
                return query.substr(0, i + 1);
            }
        }
        return "";
    }

    /**
     * @brief 在map中查找最长的、是查询query最短前缀的键
     *
     * @param query 查询字符串
     * @return string 返回map中是query前缀的最长键，无返回空字符串
     */
    string longestPrefixOf(const string &query)
    {
        TrieNode *curr = root.get();
        int maxLen = 0;
        for (int i = 0; i < query.length(); i++)
        {
            char c = query[i];
            if (curr->children.find(c) == curr->children.end())
            {
                break;
            }

            curr = curr->children[c].get();
            if (curr->isEnd())
            {
                maxLen = i + 1;
            }
        }
        return query.substr(0, maxLen);
    }

    /**
     * @brief 搜索所有具有指定前缀的键
     *
     * @param prefix 指定前缀
     * @return vector<string> 包含所有匹配键的向量
     */
    vector<string> keysWithPrefix(const string &prefix)
    {
        vector<string> results;
        // 先找到指定前缀对应的节点
        TrieNode *curr = getNode(prefix);
        if (curr == nullptr)
        {
            return results;
        }

        // 先对指定前缀进行判断
        if (curr->isEnd())
        {
            results.push_back(prefix);
        }

        // 然后对前缀节点为根节点的子树进行DFS
        for (auto &[c, child] : curr->children)
        {
            collectKeys(child.get(), prefix + c, results);
        }

        return results;
    }

    /**
     * @brief 使用通配符模式搜索所有的键
     *
     * @param pattern 匹配模式，其中'.'可以匹配任意单个字符
     * @return vector<string> 包含所有匹配键的向量
     */
    vector<string> keysWithPattern(const string &pattern)
    {
        TrieNode *curr = root.get();
        vector<string> results;

        collectKeysWithPattern(curr, pattern, 0, "", results);

        return results;
    }

    /**
     * @brief 判断是否存在匹配通配符模式的键
     * @param pattern 匹配模式
     * @return bool 如果存在返回true， 反之返回false
     */
    bool hasKeysWithPattern(const string &pattern)
    {
        return hasMatchingKey(root.get(), pattern, 0);
    }

    int getSize() const
    {
        return size;
    }

    bool empty()
    {
        return size == 0;
    }

    void clear()
    {
        // 给root，size重新赋值就行
        root = make_unique<TrieNode>();
        size = 0;
    }

    /**
     * @brief 获取map中所有的键
     *
     * @return vector<string> 包含所有键的向量
     */
    vector<string> keys()
    {
        // 空字符串肯定是所有键的前缀，即以root为根节点，遍历找到所有键
        return keysWithPrefix("");
    }
};

// ============ 测试代码 ============

void printVector(const string &title, const vector<string> &vec)
{
    cout << title << ": [";
    for (int i = 0; i < vec.size(); i++)
    {
        cout << "\"" << vec[i] << "\"";
        if (i < vec.size() - 1)
            cout << ", ";
    }
    cout << "]\n";
}

int main()
{
    TrieMap<int> trie;

    cout << "========== 测试1: 基本插入和查询 ==========\n";
    trie.put("app", 1);
    trie.put("apple", 2);
    trie.put("application", 3);
    trie.put("apply", 4);
    trie.put("banana", 5);
    trie.put("band", 6);

    cout << "插入了6个键值对\n";
    cout << "Size: " << trie.getSize() << "\n";
    cout << "containsKey(\"app\"): " << (trie.containsKey("app") ? "true" : "false") << "\n";
    cout << "containsKey(\"appl\"): " << (trie.containsKey("appl") ? "true" : "false") << "\n";
    cout << "get(\"apple\"): " << trie.get("apple").value_or(-1) << "\n\n";

    cout << "========== 测试2: 前缀查询 ==========\n";
    cout << "hasKeyWithPrefix(\"app\"): " << (trie.hasKeyWithPrefix("app") ? "true" : "false") << "\n";
    cout << "hasKeyWithPrefix(\"ban\"): " << (trie.hasKeyWithPrefix("ban") ? "true" : "false") << "\n";
    cout << "hasKeyWithPrefix(\"cat\"): " << (trie.hasKeyWithPrefix("cat") ? "true" : "false") << "\n\n";

    cout << "========== 测试3: 最短/最长前缀 ==========\n";
    cout << "shortestPrefixOf(\"application\"): \"" << trie.shortestPrefixOf("application") << "\"\n";
    cout << "longestPrefixOf(\"application\"): \"" << trie.longestPrefixOf("application") << "\"\n";
    cout << "shortestPrefixOf(\"banana123\"): \"" << trie.shortestPrefixOf("banana123") << "\"\n";
    cout << "longestPrefixOf(\"banana123\"): \"" << trie.longestPrefixOf("banana123") << "\"\n\n";

    cout << "========== 测试4: 获取指定前缀的所有键 ==========\n";
    printVector("keysWithPrefix(\"app\")", trie.keysWithPrefix("app"));
    printVector("keysWithPrefix(\"ban\")", trie.keysWithPrefix("ban"));
    printVector("所有键", trie.keys());
    cout << "\n";

    cout << "========== 测试5: 通配符模式匹配 ==========\n";
    printVector("keysWithPattern(\"app..\")", trie.keysWithPattern("app.."));
    printVector("keysWithPattern(\"ban...\")", trie.keysWithPattern("ban..."));
    cout << "hasKeysWithPattern(\".pp\"): " << (trie.hasKeysWithPattern(".pp") ? "true" : "false") << "\n";
    cout << "hasKeysWithPattern(\"...\"): " << (trie.hasKeysWithPattern("...") ? "true" : "false") << "\n\n";

    cout << "========== 测试6: 删除操作 ==========\n";
    cout << "删除前 size: " << trie.getSize() << "\n";

    trie.remove("application");
    cout << "删除 \"application\" 后:\n";
    cout << "  containsKey(\"application\"): " << (trie.containsKey("application") ? "true" : "false") << "\n";
    cout << "  containsKey(\"apple\"): " << (trie.containsKey("apple") ? "true" : "false") << "\n";
    cout << "  size: " << trie.getSize() << "\n";
    printVector("  keysWithPrefix(\"app\")", trie.keysWithPrefix("app"));

    trie.remove("app");
    cout << "删除 \"app\" 后:\n";
    cout << "  containsKey(\"app\"): " << (trie.containsKey("app") ? "true" : "false") << "\n";
    cout << "  containsKey(\"apple\"): " << (trie.containsKey("apple") ? "true" : "false") << "\n";
    cout << "  size: " << trie.getSize() << "\n";
    printVector("  keysWithPrefix(\"app\")", trie.keysWithPrefix("app"));

    cout << "\n========== 测试7: 更新值 ==========\n";
    cout << "apple 原值: " << trie.get("apple").value_or(-1) << "\n";
    trie.put("apple", 100);
    cout << "更新后 apple 值: " << trie.get("apple").value_or(-1) << "\n";
    cout << "size (应该不变): " << trie.getSize() << "\n\n";

    cout << "========== 测试8: 清空操作 ==========\n";
    trie.clear();
    cout << "清空后 size: " << trie.getSize() << "\n";
    cout << "empty(): " << (trie.empty() ? "true" : "false") << "\n";
    printVector("keys()", trie.keys());

    return 0;
}