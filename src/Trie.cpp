#include "Trie.h"

#include <queue>

// Constructors
Trie::node::node() {
    char null_char = '\0';
    character = null_char;
}

Trie::node::node(char character) {
    this->character = character;
}

Trie::node::node(char character, int rank, bool end_word) {
    this->character = character;
    this->rank = rank;
}

Trie::Trie() {
    root = new node();
}

// Destructor
Trie::~Trie() {
    // add elements to queue and delete them
    queue<node*> nodes;
    nodes.push(root); // add root to the queue

    while (nodes.empty() == false) {
        node* curr_node = nodes.front();
        for (size_t i = 0; i < curr_node->children.size(); i++) { // loop over every node in vector adding to queue
            nodes.push(curr_node->children[i]);
        }
        nodes.pop();
        delete curr_node;
    }
}


// Functions
bool Trie::insert(int rank, string word) {
    node* curr_node = root;

    for (size_t i = 0; i < word.size(); i++) { // loop over every char in word
        char curr_char = word[i];

        // last char of word
        if (i == word.size()-1) {
            if (curr_node->children_chars.find(curr_char) == curr_node->children_chars.end()) { // last char of word does not exist in children set
                // add current char to children
                curr_node->children.emplace_back(new node(curr_char, rank, true));
                curr_node->children_chars.insert(curr_char);
                return true;
            }
            else { // last char of word already exists in children set
                for (size_t j = 0; j < curr_node->children.size(); j++) {
                    if (curr_node->children[j]->character == curr_char) {
                        curr_node = curr_node->children[j];
                        break;
                    }
                }
                if (curr_node->rank > -1) { // word is already in trie
                    return false;
                }
                else { // word is not already in trie
                    curr_node->rank = rank;
                    return true;
                }
            }
        }

        // not last char of word
        if (curr_node->children_chars.find(curr_char) == curr_node->children_chars.end()) { // current char of word is not in children set
            // add current char to children
            curr_node->children.emplace_back(new node(curr_char));
            curr_node->children_chars.insert(curr_char);
            curr_node = curr_node->children.back();
        }
        else { // current char of word is in the children set
            for (size_t j = 0; j < curr_node->children.size(); j++) {
                if (curr_node->children[j]->character == curr_char) {
                    curr_node = curr_node->children[j];
                    break;
                }
            }
        }
    }
}

int Trie::search(string word) {
    node* curr_node = root;

    for (size_t i = 0; i < word.size(); i++) { // Loop over every letter in the word
        char curr_char = word[i];

        // last char of word
        if (i == word.size()-1) {
            if (curr_node->children_chars.find(curr_char) == curr_node->children_chars.end()) {
                return -1; // word not found
            }
            else {
                for (size_t j = 0; j < curr_node->children.size(); j++) {
                    if (curr_node->children[j]->character == curr_char) { // Find location of char in children vector
                        curr_node = curr_node->children[j];
                        return curr_node->rank;
                    }
                }
            }
        }

        // Not last char of word
        if (curr_node->children_chars.find(curr_char) == curr_node->children_chars.end()) {
            return -1; // word not found
        }
        else {
            for (size_t j = 0; j < curr_node->children.size(); j++) {
                if (curr_node->children[j]->character == curr_char) { // Find location of char in children vector
                    curr_node = curr_node->children[j];
                    break;
                }
            }
        }
    }
}

// Getters
Trie::node* Trie::get_root() {
    return root;
}
