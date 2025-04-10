#include <string>
#include <vector>
#include <set>
#pragma once
using namespace std;

class Trie {
    struct node {
        char character;
        vector<node*> children = {};
        set<char> children_chars;
        int rank = -1;
        bool end_word = false;

        // Constructor
        node();
        node(char character);
        node(char character, int rank, bool end_word);
    };

    node* root;

public:
    // Constructor
    Trie();

    // Destructor
    // ~Trie();

    // Functions
    bool insert(int rank, string word);
    // pair<bool, int> search();

    // Getters
    node* get_root(); // Used for testing
};
