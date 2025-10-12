#include <bits/stdc++.h>

using namespace std;

class Trie
{
private:
    struct TrieNode
    {
        unordered_map<char, unique_ptr<TrieNode>> children;
        optional<int> val;

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

public:
    Trie()
    {
        root = make_unique<TrieNode>();
    }

    void insert(string word)
    {
        if (word.empty())
            return;
        TrieNode *curr = root.get();
        for (char c : word)
        {
            if (curr->children.find(c) == curr->children.end())
            {
                curr->children[c] = make_unique<TrieNode>();
            }
            curr = curr->children[c].get();
        }

        curr->val = 1;
    }

    optional<int> get(const string &key)
    {
        TrieNode *node = getNode(key);

        if (!node)
        {
            return nullopt;
        }

        return node->val;
    }

    bool search(string word)
    {
        return get(word) != nullopt;
    }

    bool startsWith(string prefix)
    {
        return getNode(prefix) != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */