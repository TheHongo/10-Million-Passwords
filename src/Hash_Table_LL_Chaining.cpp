#include <iostream>
#include "Hash_Table_LL_Chaining.h"

using namespace std;

Hash_Table_LL_Chaining::Hash_Table_LL_Chaining(int capacity) {
    num_elements = 0;
    this->capacity = capacity;
    hash_table = new std::list<std::pair<std::string, int>>[capacity];
}

Hash_Table_LL_Chaining::~Hash_Table_LL_Chaining() {
    delete[] hash_table;
}
//yeah

int Hash_Table_LL_Chaining::hash(string &pass_key) const{
    int hash_val = 0;
    for (unsigned int i = 0; i < pass_key.size(); i++){
        hash_val += (pass_key[i] * (i + 1)) % capacity; // might be bad for clustering
    }
    return hash_val % capacity;
}

double Hash_Table_LL_Chaining::load_factor() const{
    return static_cast<double>(num_elements)/capacity;
}

void Hash_Table_LL_Chaining::rehash() {
    int old_capacity = capacity; // for indexing
    int new_capacity = capacity * 2; // for new table hash
    auto* new_table = new std::list<std::pair<std::string, int>>[new_capacity];
    for (int i = 0; i < old_capacity; i++){
        for (auto pass_rank: hash_table[i]){
            new_table[hash(pass_rank.first)].emplace_back(pass_rank.first, pass_rank.second);
        }
    }
    delete[] hash_table;
    hash_table = new_table;
}

void Hash_Table_LL_Chaining::insert(int rank, std::string pass) {
    hash_table[hash(pass)].emplace_back(pass, rank);
    if (load_factor() > 0.7){
        rehash();
    }
}

int Hash_Table_LL_Chaining::search(std::string pass) const{
    for (auto pass_rank: hash_table[hash(pass)]){
        if (pass == pass_rank.first){
            return pass_rank.second;
        }
    }
    return -1;
}
