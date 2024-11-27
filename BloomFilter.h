#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <random>

class BloomFilter {
private:
    int m;   // Size of the Bloom filter
    int k;   // Number of hash functions
    std::vector<bool> table;   // The hash table (bit array)
    std::vector<int> ai_values; // ai values for hash functions
    std::vector<int> bi_values; // bi values for hash functions
    std::vector<int> si_values; // si values for hash functions

    int random_in_range(int min, int max);

    int hash_function1(int x, int ai, int bi);

    int hash_function2(int x, int si, std::mt19937& gen);

public:
    BloomFilter(int n, int c, int k_hashes);

    void Add(int x);

    bool Contains(int x);
};

#endif
