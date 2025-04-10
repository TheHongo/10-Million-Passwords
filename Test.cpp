#include "Test.h"

// Trie testing
bool trie_test_1() {
    // inserting 1 word into the trie

    Trie trie;
    trie.insert(1, "map");

    auto curr_node = trie.get_root();
    if (curr_node->character != '\0' || // check root
        curr_node->children.size() != 1 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0];
    if (curr_node->character != 'm' || // check m
        curr_node->children.size() != 1 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0]; // check a
    if (curr_node->character != 'a' ||
        curr_node->children.size() != 1 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0]; // check p
    if (curr_node->character != 'p' ||
        curr_node->children.size() != 0 ||
        curr_node->rank != 1 ||
        curr_node->end_word != true) {
        return false;
    }

    return true;
}

bool trie_test_2() {
    // inserting 2 words into trie

    Trie trie;
    trie.insert(1, "map");
    trie.insert(2, "mat");

    auto curr_node = trie.get_root();
    if (curr_node->character != '\0' || // check root
        curr_node->children.size() != 1 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0];
    if (curr_node->character != 'm' || // check m
        curr_node->children.size() != 1 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0];
    if (curr_node->character != 'a' || // check a
        curr_node->children.size() != 2 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0];
    if (curr_node->character != 'p' || // check p
        curr_node->children.size() != 0 ||
        curr_node->rank != 1 ||
        curr_node->end_word != true) {
        return false;
    }
    curr_node = trie.get_root();
    curr_node = curr_node->children[0]->children[0]->children[1];
    if (curr_node->character != 't' || // check t
        curr_node->children.size() != 0 ||
        curr_node->rank != 2 ||
        curr_node->end_word != true) {
        return false;
    }

    return true;
}

bool trie_test_3() {
    // inserting 3 words. 1 overlaps

    Trie trie;
    trie.insert(1, "map");
    trie.insert(2, "ma");
    trie.insert(3, "mat");

    auto curr_node = trie.get_root();
    if (curr_node->character != '\0' || // check root
        curr_node->children.size() != 1 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0];
    if (curr_node->character != 'm' || // check m
        curr_node->children.size() != 1 ||
        curr_node->rank != -1 ||
        curr_node->end_word != false) {
        return false;
    }
    curr_node = curr_node->children[0];
    if (curr_node->character != 'a' || // check a
        curr_node->children.size() != 2 ||
        curr_node->rank != 2 ||
        curr_node->end_word != true) {
        return false;
    }
    curr_node = curr_node->children[0];
    if (curr_node->character != 'p' || // check p
        curr_node->children.size() != 0 ||
        curr_node->rank != 1 ||
        curr_node->end_word != true) {
        return false;
    }
    curr_node = trie.get_root();
    curr_node = curr_node->children[0]->children[0]->children[1];
    if (curr_node->character != 't' || // check t
        curr_node->children.size() != 0 ||
        curr_node->rank != 3 ||
        curr_node->end_word != true) {
        return false;
    }

    return true;
}

void Test::trie_test() {
    if (!trie_test_1()) {cout << "trie test 1 failed" << endl;} // Inserting
    if (!trie_test_2()) {cout << "trie test 2 failed" << endl;} // Inserting
    if (!trie_test_3()) {cout << "trie test 3 failed" << endl;} // Inserting
}
// End trie testing
