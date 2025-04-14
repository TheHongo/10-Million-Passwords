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
    ~Trie();

    // Functions
    bool insert(int rank, string word);
    int search(string word);

    // Getters
    node* get_root(); // Used for testing
};
