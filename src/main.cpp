#include <string>
#include <fstream>
#include <sstream>
#include "Trie.h"
#include "Test.h"
#include "GUI.h"
#include "Hash_Table_LL_Chaining.h"

using namespace std;

int main() {
    // reading from the file and inserting into the data structure
    // create data structure objects
    Trie trie;
    Hash_Table_LL_Chaining hash(1000);
    // open file
    string filename = "../Data/10millionPasswords.csv";
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "File reading error" << endl;
    }
    // read every line of file
    string line;
    getline(file, line); // First line
    while (getline(file, line)) { // Starts on second line of file
        stringstream string_stream(line);
        string rank_s;
        int rank;
        string word;
        getline(string_stream, rank_s, ',');
        getline(string_stream, word, ',');
        rank = stoi(rank_s);
        // insert
        trie.insert(rank, word);
        hash.insert(rank, word);
    }

    Screen screen;
    screen.openWindow(800.0f, 600.0f);
}
