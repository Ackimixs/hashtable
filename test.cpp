#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <vector>
#include "HashTable.h"
#include "OrderedHashTable.h"

constexpr int nbExecutions = 5;
constexpr int keyLength = 8;
constexpr int stepSize = 2;
constexpr int maxElements = 200000;

std::string randomString(std::mt19937& rng) {
    static const std::string chars = "abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<> dist(0, chars.size() - 1);
    std::string result;
    for (int i = 0; i < keyLength; ++i) {
        result += chars[dist(rng)];
    }
    return result;
}

int main() {
    std::ofstream fileInsert("results_insert.csv");
    std::ofstream fileRemove("results_remove.csv");
    std::ofstream fileSearch("results_search.csv");

    // Titres avec description plus explicite
    fileInsert << "NbElements,HashTable_Insert_ns,OrderedHashTable_Insert_ns,HashTable_Insert_s,OrderedHashTable_Insert_s,HashTable_Single_Insert_ns,OrderedHashTable_Single_Insert_ns,HashTable_Single_Insert_s,OrderedHashTable_Single_Insert_s\n";
    fileRemove << "NbElements,HashTable_Remove_ns,OrderedHashTable_Remove_ns,HashTable_Remove_s,OrderedHashTable_Remove_s,HashTable_Single_Remove_ns,OrderedHashTable_Single_Remove_ns,HashTable_Single_Remove_s,OrderedHashTable_Single_Remove_s\n";
    fileSearch << "NbElements,HashTable_Search_ns,OrderedHashTable_Search_ns,HashTable_Search_s,OrderedHashTable_Search_s,HashTable_Single_Search_ns,OrderedHashTable_Single_Search_ns,HashTable_Single_Search_s,OrderedHashTable_Single_Search_s\n";

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> valueDist(0, 1000000);

    for (int nbElements = 10; nbElements <= maxElements; nbElements *= stepSize) {
        long long totalInsertHT = 0, totalRemoveHT = 0, totalSearchHT = 0;
        long long totalInsertOHT = 0, totalRemoveOHT = 0, totalSearchOHT = 0;
        long long totalSingleInsertHT = 0, totalSingleRemoveHT = 0, totalSingleSearchHT = 0;
        long long totalSingleInsertOHT = 0, totalSingleRemoveOHT = 0, totalSingleSearchOHT = 0;

        for (int i = 0; i < nbExecutions; ++i) {
            HashTable<std::string, int, 4271> ht;
            OrderedHashTable<std::string, int, 4271> oht;

            std::vector<std::string> keysHT;
            std::vector<std::string> keysOHT;

            // HashTable insertion
            auto startInsertHT = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < nbElements; ++j) {
                std::string key = randomString(rng);
                int value = valueDist(rng);
                ht.insert(key, value);
                keysHT.push_back(key);
            }
            auto endInsertHT = std::chrono::high_resolution_clock::now();
            totalInsertHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertHT - startInsertHT).count();

            // OrderedHashTable insertion
            auto startInsertOHT = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < nbElements; ++j) {
                std::string key = randomString(rng);
                int value = valueDist(rng);
                oht.insert(key, value);
                keysOHT.push_back(key);
            }
            auto endInsertOHT = std::chrono::high_resolution_clock::now();
            totalInsertOHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endInsertOHT - startInsertOHT).count();

            // HashTable search
            auto startSearchHT = std::chrono::high_resolution_clock::now();
            for (const auto& key : keysHT) {
                int value;
                ht.search(key, value);
            }
            auto endSearchHT = std::chrono::high_resolution_clock::now();
            totalSearchHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchHT - startSearchHT).count();

            // OrderedHashTable search
            auto startSearchOHT = std::chrono::high_resolution_clock::now();
            for (const auto& key : keysOHT) {
                int value;
                oht.search(key, value);
            }
            auto endSearchOHT = std::chrono::high_resolution_clock::now();
            totalSearchOHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSearchOHT - startSearchOHT).count();

            // HashTable remove
            auto startRemoveHT = std::chrono::high_resolution_clock::now();
            for (const auto& key : keysHT) {
                ht.remove(key);
            }
            auto endRemoveHT = std::chrono::high_resolution_clock::now();
            totalRemoveHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endRemoveHT - startRemoveHT).count();

            // OrderedHashTable remove
            auto startRemoveOHT = std::chrono::high_resolution_clock::now();
            for (const auto& key : keysOHT) {
                oht.remove(key);
            }
            auto endRemoveOHT = std::chrono::high_resolution_clock::now();
            totalRemoveOHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endRemoveOHT - startRemoveOHT).count();

            // Single HashTable insertion at the end
            std::string singleKeyHT = randomString(rng);
            int singleValueHT = valueDist(rng);
            auto startSingleInsertHT = std::chrono::high_resolution_clock::now();
            ht.insert(singleKeyHT, singleValueHT);
            auto endSingleInsertHT = std::chrono::high_resolution_clock::now();
            totalSingleInsertHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSingleInsertHT - startSingleInsertHT).count();

            // Single OrderedHashTable insertion at the end
            std::string singleKeyOHT = randomString(rng);
            int singleValueOHT = valueDist(rng);
            auto startSingleInsertOHT = std::chrono::high_resolution_clock::now();
            oht.insert(singleKeyOHT, singleValueOHT);
            auto endSingleInsertOHT = std::chrono::high_resolution_clock::now();
            totalSingleInsertOHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSingleInsertOHT - startSingleInsertOHT).count();

            // Single HashTable search
            auto startSingleSearchHT = std::chrono::high_resolution_clock::now();
            int value;
            ht.search(singleKeyHT, value);
            auto endSingleSearchHT = std::chrono::high_resolution_clock::now();
            totalSingleSearchHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSingleSearchHT - startSingleSearchHT).count();

            // Single OrderedHashTable search
            auto startSingleSearchOHT = std::chrono::high_resolution_clock::now();
            oht.search(singleKeyOHT, value);
            auto endSingleSearchOHT = std::chrono::high_resolution_clock::now();
            totalSingleSearchOHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSingleSearchOHT - startSingleSearchOHT).count();

            // Single HashTable remove
            auto startSingleRemoveHT = std::chrono::high_resolution_clock::now();
            ht.remove(singleKeyHT);
            auto endSingleRemoveHT = std::chrono::high_resolution_clock::now();
            totalSingleRemoveHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSingleRemoveHT - startSingleRemoveHT).count();

            // Single OrderedHashTable remove
            auto startSingleRemoveOHT = std::chrono::high_resolution_clock::now();
            oht.remove(singleKeyOHT);
            auto endSingleRemoveOHT = std::chrono::high_resolution_clock::now();
            totalSingleRemoveOHT += std::chrono::duration_cast<std::chrono::nanoseconds>(endSingleRemoveOHT - startSingleRemoveOHT).count();
        }

        // Calcul des moyennes et ajout des résultats dans les fichiers CSV
        fileInsert << nbElements << ","
                   << totalInsertHT / nbExecutions << ","
                   << totalInsertOHT / nbExecutions << ","
                   << (totalInsertHT / nbExecutions) / 1e9 << ","
                   << (totalInsertOHT / nbExecutions) / 1e9 << ","
                   << totalSingleInsertHT / nbExecutions << ","
                   << totalSingleInsertOHT / nbExecutions << ","
                   << (totalSingleInsertHT / nbExecutions) / 1e9 << ","
                   << (totalSingleInsertOHT / nbExecutions) / 1e9 << "\n";

        fileRemove << nbElements << ","
                   << totalRemoveHT / nbExecutions << ","
                   << totalRemoveOHT / nbExecutions << ","
                   << (totalRemoveHT / nbExecutions) / 1e9 << ","
                   << (totalRemoveOHT / nbExecutions) / 1e9 << ","
                   << totalSingleRemoveHT / nbExecutions << ","
                   << totalSingleRemoveOHT / nbExecutions << ","
                   << (totalSingleRemoveHT / nbExecutions) / 1e9 << ","
                   << (totalSingleRemoveOHT / nbExecutions) / 1e9 << "\n";

        fileSearch << nbElements << ","
                   << totalSearchHT / nbExecutions << ","
                   << totalSearchOHT / nbExecutions << ","
                   << (totalSearchHT / nbExecutions) / 1e9 << ","
                   << (totalSearchOHT / nbExecutions) / 1e9 << ","
                   << totalSingleSearchHT / nbExecutions << ","
                   << totalSingleSearchOHT / nbExecutions << ","
                   << (totalSingleSearchHT / nbExecutions) / 1e9 << ","
                   << (totalSingleSearchOHT / nbExecutions) / 1e9 << "\n";

        std::cout << "nbElements = " << nbElements << " termine." << std::endl;
    }

    fileInsert.close();
    fileRemove.close();
    fileSearch.close();

    std::cout << "Benchmarks termines. Resultats dans : results_insert.csv, results_remove.csv, results_search.csv\n";

    return 0;
}
