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

    bool hasMatchingKey(TrieNode *node, const string &pattern, int index)
    {
        if (!node)
        {
            return false;
        }

        if (index == pattern.length())
        {
            return node->isEnd();
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

public:
    Trie() : root(make_unique<TrieNode>()) {}

    void put(const string &key)
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

        curr->val = 1;
    }

    bool hasKeysWithPattern(const string &pattern)
    {
        return hasMatchingKey(root.get(), pattern, 0);
    }
};

class WordDictionary
{
public:
    Trie tree;

    WordDictionary()
    {
    }

    void addWord(string word)
    {
        tree.put(word);
    }

    bool search(string word)
    {
        return tree.hasKeysWithPattern(word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */