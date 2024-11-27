#include "BloomFilter.h"

// Constructor to initialize the Bloom filter with size m and k hash functions
BloomFilter::BloomFilter(int n, int c, int k_hashes) : k(k_hashes) {
    m = c * n;  // Size of the table is proportional to n
    table = std::vector<bool>(m, false); // Initialize the table with false

    // Initialize ai, bi, and si values to be used for hashing
    for (int i = 0; i < k; ++i) {
        ai_values.push_back(random_in_range(1, m - 1)); // Random ai for hash function 1
        bi_values.push_back(random_in_range(0, m - 1)); // Random bi for hash function 1
        si_values.push_back(random_in_range(1, m - 1)); // Random si for hash function 2
    }
}

// Function to generate a random number in a given range
int BloomFilter::random_in_range(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// First hash function (linear congruential method)
int BloomFilter::hash_function1(int x, int ai, int bi) {
    return ((ai * x + bi) % m);
}

// Second hash function (random number generator approach)
int BloomFilter::hash_function2(int x, int si, std::mt19937& gen) {
    std::uniform_int_distribution<> dis(0, m - 1);  // Ensure it's within [0, m-1]
    return dis(gen);
}

// Add element to the Bloom filter
void BloomFilter::Add(int x) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate k hash functions and mark the corresponding positions
    for (int i = 0; i < k; ++i) {
        // Use pre-generated ai, bi, and si values
        int ai = ai_values[i];
        int bi = bi_values[i];
        int si = si_values[i];

        // Apply the first hash function
        int index1 = hash_function1(x, ai, bi);
        table[index1] = true;

        // Apply the second hash function
        int index2 = hash_function2(x, si, gen);
        table[index2] = true;
    }
}

// Check if element is possibly in the Bloom filter
bool BloomFilter::Contains(int x) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Apply k hash functions
    for (int i = 0; i < k; ++i) {
        // Use pre-generated ai, bi, and si values
        int ai = ai_values[i];
        int bi = bi_values[i];
        int si = si_values[i];

        // Check the first hash function
        int index1 = hash_function1(x, ai, bi);
        if (!table[index1]) {
            return false; // If any bit is false, the element is definitely not in the set
        }

        // Check the second hash function
        int index2 = hash_function2(x, si, gen);
        if (!table[index2]) {
            return false; // If any bit is false, the element is definitely not in the set
        }
    }

    // If all checks passed, the element is possibly in the set
    return true;
}

