#include <bits/stdc++.h>

using namespace std;

// ============ TrieMap 实现（来自原代码）============
template <typename V>
class TrieMap
{
private:
    struct TrieNode
    {
        optional<V> val;
        unordered_map<char, unique_ptr<TrieNode>> children;

        TrieNode() : val(nullopt) {}
        bool isEnd()
        {
            return val.has_value();
        }
    };

    unique_ptr<TrieNode> root;
    int size;

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

        for (auto &[c, child] : root->children)
        {
            collectKeys(child.get(), prefix + c, results);
        }
    }

    void collectKeysWithPattern(TrieNode *node, const string &pattern, int index, string prefix, vector<string> &results)
    {
        if (!node)
        {
            return;
        }

        if (index == pattern.size())
        {
            if (node->isEnd())
            {
                results.push_back(prefix);
            }
            return;
        }

        char c = pattern[index];
        if (c == '.')
        {
            for (auto &[ch, child] : node->children)
            {
                collectKeysWithPattern(child.get(), pattern, index + 1, prefix + ch, results);
            }
        }
        else
        {
            if (node->children.find(c) != node->children.end())
            {
                collectKeysWithPattern(node->children[c].get(), pattern, index + 1, prefix + c, results);
            }
        }
    }

    bool hasMatchingKey(TrieNode *node, const string &pattern, int index)
    {
        if (!node)
        {
            return false;
        }

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
                return hasMatchingKey(node->children[c].get(), pattern, index + 1);
            }
            else
            {
                return false;
            }
        }
    }

    bool removeHelper(TrieNode *node, const string &key, int index)
    {
        if (index == key.length())
        {
            if (!node->isEnd())
            {
                return false;
            }
            node->val = nullopt;
            size--;
            return node->children.empty();
        }

        char c = key[index];
        if (node->children.find(c) == node->children.end())
        {
            return false;
        }

        bool shouldDeleteChild = removeHelper(node->children[c].get(), key, index + 1);

        if (shouldDeleteChild)
        {
            node->children.erase(c);
            return !node->isEnd() && node->children.empty();
        }

        return false;
    }

public:
    TrieMap() : root(make_unique<TrieNode>()), size(0) {}

    void put(const string &key, V val)
    {
        if (key.empty())
            return;

        TrieNode *curr = root.get();
        for (char c : key)
        {
            if (curr->children.find(c) == curr->children.end())
            {
                curr->children[c] = make_unique<TrieNode>();
            }
            curr = curr->children[c].get();
        }

        if (!curr->isEnd())
        {
            size++;
        }

        curr->val = val;
    }

    void remove(const string &key)
    {
        if (key.empty())
        {
            return;
        }
        removeHelper(root.get(), key, 0);
    }

    optional<V> get(const string &key)
    {
        TrieNode *node = getNode(key);
        if (node == nullptr || !node->isEnd())
        {
            return nullopt;
        }
        return node->val;
    }

    bool containsKey(const string &key)
    {
        return get(key) != nullopt;
    }

    bool hasKeyWithPrefix(const string &prefix)
    {
        return getNode(prefix) != nullptr;
    }

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

            curr = curr->children[c].get();

            if (curr->isEnd())
            {
                return query.substr(0, i + 1);
            }
        }
        return "";
    }

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

    vector<string> keysWithPrefix(const string &prefix)
    {
        vector<string> results;
        TrieNode *curr = getNode(prefix);
        if (curr == nullptr)
        {
            return results;
        }

        if (curr->isEnd())
        {
            results.push_back(prefix);
        }

        for (auto &[c, child] : curr->children)
        {
            collectKeys(child.get(), prefix + c, results);
        }

        return results;
    }

    vector<string> keysWithPattern(const string &pattern)
    {
        TrieNode *curr = root.get();
        vector<string> results;

        collectKeysWithPattern(curr, pattern, 0, "", results);

        return results;
    }

    bool hasKeysWithPattern(const string &pattern)
    {
        return hasMatchingKey(root.get(), pattern, 0);
    }

    int getSize() const
    {
        return size;
    }

    bool empty() const
    {
        return size == 0;
    }

    void clear()
    {
        root = make_unique<TrieNode>();
        size = 0;
    }

    vector<string> keys()
    {
        return keysWithPrefix("");
    }
};

// ============ TrieSet 实现 ============

/**
 * @brief 基于 TrieMap 实现的字符串集合
 *
 * TrieSet 是一个高效的字符串集合数据结构，底层使用 TrieMap<bool> 实现。
 * 其中 TrieMap 的键表示集合中的元素，值（bool 类型）仅作为占位符使用。
 * 支持插入、删除、查询、前缀匹配和通配符搜索等操作。
 */
class TrieSet
{
private:
    // 底层使用 TrieMap，值类型为 bool（仅作占位符，实际值无意义）
    TrieMap<bool> map;

public:
    /**
     * @brief 构造函数，创建一个空的 TrieSet
     */
    TrieSet() {}

    /**
     * @brief 向集合中添加一个字符串
     *
     * @param key 要添加的字符串
     *
     * 如果字符串已存在，则不进行任何操作。
     * 底层实现：将字符串作为键插入 TrieMap，值设为 true（占位符）
     */
    void add(const string &key)
    {
        // 值用 true 作为占位符，实际上任何值都可以
        map.put(key, true);
    }

    /**
     * @brief 从集合中删除一个字符串
     *
     * @param key 要删除的字符串
     *
     * 如果字符串不存在，则不进行任何操作。
     */
    void remove(const string &key)
    {
        map.remove(key);
    }

    /**
     * @brief 判断字符串是否在集合中
     *
     * @param key 要查找的字符串
     * @return bool 如果存在返回 true，否则返回 false
     */
    bool contains(const string &key)
    {
        return map.containsKey(key);
    }

    /**
     * @brief 判断是否存在具有指定前缀的字符串
     *
     * @param prefix 指定的前缀
     * @return bool 如果至少存在一个具有该前缀的字符串返回 true，否则返回 false
     */
    bool hasElementWithPrefix(const string &prefix)
    {
        return map.hasKeyWithPrefix(prefix);
    }

    /**
     * @brief 在集合中查找最短的、是查询字符串前缀的元素
     *
     * @param query 查询字符串
     * @return string 返回集合中是 query 前缀的最短字符串，如果没有返回空字符串
     *
     * 例如：集合中有 "app", "apple", "application"
     *      shortestPrefixOf("application") 返回 "app"
     */
    string shortestPrefixOf(const string &query)
    {
        return map.shortestPrefixOf(query);
    }

    /**
     * @brief 在集合中查找最长的、是查询字符串前缀的元素
     *
     * @param query 查询字符串
     * @return string 返回集合中是 query 前缀的最长字符串，如果没有返回空字符串
     *
     * 例如：集合中有 "app", "apple", "application"
     *      longestPrefixOf("application") 返回 "application"
     */
    string longestPrefixOf(const string &query)
    {
        return map.longestPrefixOf(query);
    }

    /**
     * @brief 获取所有具有指定前缀的字符串
     *
     * @param prefix 指定的前缀
     * @return vector<string> 包含所有匹配字符串的向量
     *
     * 如果前缀本身也是集合中的元素，会包含在结果中。
     */
    vector<string> elementsWithPrefix(const string &prefix)
    {
        return map.keysWithPrefix(prefix);
    }

    /**
     * @brief 使用通配符模式搜索所有匹配的字符串
     *
     * @param pattern 匹配模式，其中 '.' 可以匹配任意单个字符
     * @return vector<string> 包含所有匹配字符串的向量
     *
     * 例如：pattern = "a.." 可以匹配 "app", "abc", "add" 等三字符且以 'a' 开头的字符串
     */
    vector<string> elementsWithPattern(const string &pattern)
    {
        return map.keysWithPattern(pattern);
    }

    /**
     * @brief 判断是否存在匹配通配符模式的字符串
     *
     * @param pattern 匹配模式，其中 '.' 可以匹配任意单个字符
     * @return bool 如果存在至少一个匹配的字符串返回 true，否则返回 false
     */
    bool hasElementsWithPattern(const string &pattern)
    {
        return map.hasKeysWithPattern(pattern);
    }

    /**
     * @brief 获取集合中的元素数量
     *
     * @return int 集合中的元素数量
     */
    int getSize() const
    {
        return map.getSize();
    }

    /**
     * @brief 判断集合是否为空
     *
     * @return bool 如果集合为空返回 true，否则返回 false
     */
    bool empty() const
    {
        return map.empty();
    }

    /**
     * @brief 清空集合中的所有元素
     */
    void clear()
    {
        map.clear();
    }

    /**
     * @brief 获取集合中的所有元素
     *
     * @return vector<string> 包含所有元素的向量
     */
    vector<string> elements()
    {
        return map.keys();
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
    TrieSet set;

    cout << "========== 测试1: 基本添加和查询 ==========\n";
    set.add("app");
    set.add("apple");
    set.add("application");
    set.add("apply");
    set.add("banana");
    set.add("band");

    cout << "添加了6个字符串\n";
    cout << "Size: " << set.getSize() << "\n";
    cout << "contains(\"app\"): " << (set.contains("app") ? "true" : "false") << "\n";
    cout << "contains(\"appl\"): " << (set.contains("appl") ? "true" : "false") << "\n";
    cout << "contains(\"apple\"): " << (set.contains("apple") ? "true" : "false") << "\n\n";

    cout << "========== 测试2: 前缀查询 ==========\n";
    cout << "hasElementWithPrefix(\"app\"): " << (set.hasElementWithPrefix("app") ? "true" : "false") << "\n";
    cout << "hasElementWithPrefix(\"ban\"): " << (set.hasElementWithPrefix("ban") ? "true" : "false") << "\n";
    cout << "hasElementWithPrefix(\"cat\"): " << (set.hasElementWithPrefix("cat") ? "true" : "false") << "\n\n";

    cout << "========== 测试3: 最短/最长前缀 ==========\n";
    cout << "shortestPrefixOf(\"application\"): \"" << set.shortestPrefixOf("application") << "\"\n";
    cout << "longestPrefixOf(\"application\"): \"" << set.longestPrefixOf("application") << "\"\n";
    cout << "shortestPrefixOf(\"banana123\"): \"" << set.shortestPrefixOf("banana123") << "\"\n";
    cout << "longestPrefixOf(\"banana123\"): \"" << set.longestPrefixOf("banana123") << "\"\n\n";

    cout << "========== 测试4: 获取指定前缀的所有元素 ==========\n";
    printVector("elementsWithPrefix(\"app\")", set.elementsWithPrefix("app"));
    printVector("elementsWithPrefix(\"ban\")", set.elementsWithPrefix("ban"));
    printVector("所有元素", set.elements());
    cout << "\n";

    cout << "========== 测试5: 通配符模式匹配 ==========\n";
    printVector("elementsWithPattern(\"app..\")", set.elementsWithPattern("app.."));
    printVector("elementsWithPattern(\"ban...\")", set.elementsWithPattern("ban..."));
    cout << "hasElementsWithPattern(\".pp\"): " << (set.hasElementsWithPattern(".pp") ? "true" : "false") << "\n";
    cout << "hasElementsWithPattern(\"...\"): " << (set.hasElementsWithPattern("...") ? "true" : "false") << "\n\n";

    cout << "========== 测试6: 删除操作 ==========\n";
    cout << "删除前 size: " << set.getSize() << "\n";

    set.remove("application");
    cout << "删除 \"application\" 后:\n";
    cout << "  contains(\"application\"): " << (set.contains("application") ? "true" : "false") << "\n";
    cout << "  contains(\"apple\"): " << (set.contains("apple") ? "true" : "false") << "\n";
    cout << "  size: " << set.getSize() << "\n";
    printVector("  elementsWithPrefix(\"app\")", set.elementsWithPrefix("app"));

    set.remove("app");
    cout << "删除 \"app\" 后:\n";
    cout << "  contains(\"app\"): " << (set.contains("app") ? "true" : "false") << "\n";
    cout << "  contains(\"apple\"): " << (set.contains("apple") ? "true" : "false") << "\n";
    cout << "  size: " << set.getSize() << "\n";
    printVector("  elementsWithPrefix(\"app\")", set.elementsWithPrefix("app"));

    cout << "\n========== 测试7: 重复添加 ==========\n";
    cout << "apple 添加前 size: " << set.getSize() << "\n";
    set.add("apple");
    cout << "重复添加 apple 后 size (应该不变): " << set.getSize() << "\n\n";

    cout << "========== 测试8: 清空操作 ==========\n";
    set.clear();
    cout << "清空后 size: " << set.getSize() << "\n";
    cout << "empty(): " << (set.empty() ? "true" : "false") << "\n";
    printVector("elements()", set.elements());

    return 0;
}