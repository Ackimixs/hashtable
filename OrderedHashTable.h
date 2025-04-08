#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>

template<typename T, typename U, size_t N = 10>
class OrderedHashTable {
public:
    using KeyType = T;
    using ValueType = U;

private:
    static const int TABLE_SIZE = N;
    std::vector<std::list<std::pair<T, U>>> table;
    std::list<T> insertionOrder;
    //std::unordered_map<T, typename std::list<T>::iterator> orderMap;

    int hashFunction(const T& key) {
        int hash = 0;
        for (char c : key) hash += c;
        return hash % TABLE_SIZE;
    }

public:

    OrderedHashTable() {
        table.resize(TABLE_SIZE);
    }

    void insert(const T& key, U value) {
        int index = hashFunction(key);

        // Mettre à jour si déjà existant
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        // Sinon, insérer et enregistrer l’ordre
        table[index].emplace_back(key, value);
        insertionOrder.push_back(key);
        //orderMap[key] = --insertionOrder.end();
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
                // Supprimer de l’ordre d’insertion
                /*insertionOrder.erase(orderMap[key]);
                orderMap.erase(key);*/
                for (auto orderIt = insertionOrder.begin(); orderIt != insertionOrder.end(); ++orderIt) {
                    if (*orderIt == key) {
                        insertionOrder.erase(orderIt);
                        break;
                    }
                }
                return true;
            }
        }
        return false;
    }

    void printInOrder() {
        std::cout << "Contenu (ordre d'insertion) :" << std::endl;
        for (const T& key : insertionOrder) {
            int index = hashFunction(key);
            for (const auto& pair : table[index]) {
                if (pair.first == key) {
                    std::cout << key << " => " << pair.second << std::endl;
                }
            }
        }
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
        table.clear();
        insertionOrder.clear();
        //orderMap.clear();
        table.resize(TABLE_SIZE);
    }
};
