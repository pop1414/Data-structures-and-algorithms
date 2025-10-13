#include <bits/stdc++.h>

using namespace std;

class Trie
{
private:
    struct TrieNode
    {
        optional<int> val;
        unordered_map<char, unique_ptr<TrieNode>> children;

        TrieNode() : val(nullopt) {}

        bool isEnd()
        {
            return val.has_value();
        }
    };

    unique_ptr<TrieNode> root;

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

    void collectKeys(TrieNode *node, int &sum)
    {
        if (!node)
            return;

        if (node->isEnd())
        {
            sum += node->val.value();
        }

        for (auto &[c, child] : node->children)
        {
            collectKeys(child.get(), sum);
        }
    }

public:
    Trie() : root(make_unique<TrieNode>()) {}

    void put(const string &key, int val)
    {
        TrieNode *curr = root.get();

        for (char c : key)
        {
            if (curr->children.find(c) == curr->children.end())
            {
                curr->children[c] = make_unique<TrieNode>();
            }
            curr = curr->children[c].get();
        }

        curr->val = val;
    }

    int keysWithPrefix(const string &prefix)
    {
        TrieNode *curr = getNode(prefix);
        int sum = 0;
        collectKeys(curr, sum);

        return sum;
    }
};

class MapSum
{
public:
    Trie tree;

    MapSum()
    {
    }

    void insert(string key, int val)
    {
        tree.put(key, val);
    }

    int sum(string prefix)
    {
        return tree.keysWithPrefix(prefix);
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */