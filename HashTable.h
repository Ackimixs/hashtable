#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <string>

template<typename T, typename U, size_t N = 10>
class HashTable {
private:
    static const int TABLE_SIZE = N; // Taille de la table
    std::vector<std::list<std::pair<T, U>>> table;

    static int hashFunction(const T& key) {
        int hash = 0;
        for (char c : key)
            hash += c;
        return hash % TABLE_SIZE;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    void insert(const T& key, U value) {
        int index = hashFunction(key);
        // Vérifier si la clé existe déjà pour mettre à jour
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back({key, value});
    }

    bool search(const T& key, U& valueOut) {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                valueOut = pair.second;
                return true;
            }
        }
        return false;
    }

    bool remove(const T& key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    void print() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "[" << i << "] ";
            for (const auto& pair : table[i]) {
                std::cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i].clear();
        }
    }
};
