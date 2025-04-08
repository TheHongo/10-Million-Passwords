#include <string>
#include <vector>
#pragma once
using namespace std;

class Trie {
    struct node {
        char character;
        vector<node> children = {};
        int rank = -1;
        bool end_word = false;

        // Constructor
        node(char character, int rank, bool end_word);
    };

    vector<node*> root = {};

public:
    // Destructor
    ~Trie();

    // Functions
    bool insert(int rank, string word);
    pair<bool, int> search();
};
