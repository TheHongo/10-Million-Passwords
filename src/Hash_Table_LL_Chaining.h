#pragma once
#include <list> // for LL
#include <utility> // for pairs
#include <string>

using namespace std;

class Hash_Table_LL_Chaining {
    private:

    int num_elements;
    int capacity;
    std::list<std::pair<std::string, int>>* hash_table; // pass, rank

    int hash(std::string& pass_key) const;
    double load_factor() const;
    void rehash();

    public:

    ~Hash_Table_LL_Chaining();
    explicit Hash_Table_LL_Chaining(int capacity = 10); // int ONLY
    void insert(int rank, std::string pass);
    int search(std::string pass) const;

};

// This class and method are optional.
