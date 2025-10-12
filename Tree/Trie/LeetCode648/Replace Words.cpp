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

    string shortestPrefixOfKey(const string &query)
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
};

class Solution
{
public:
    string replaceWords(vector<string> &dictionary, string sentence)
    {
        Trie tree;
        for (const string &s : dictionary)
        {
            tree.put(s);
        }

        string newSetence;
        vector<string> words;

        istringstream iss(sentence);
        string w;

        while (iss >> w)
        {
            string aWord = tree.shortestPrefixOfKey(w);
            if (aWord != "")
            {
                words.push_back(aWord);
            }
            else
            {
                words.push_back(w);
            }
        }

        for (int i = 0; i < words.size(); i++)
        {
            if (i == 0)
            {
                newSetence += words[i];
            }
            else
            {
                newSetence += " " + words[i];
            }
        }

        return newSetence;
    }
};