#include <iostream>
#include "BloomFilter.h"

int main() {
    int n = 1000;
    int c = 10;
    int k = 5;

    // Create a BloomFilter instance
    BloomFilter bloomFilter(n, c, k);

    //Add some elements
    bloomFilter.Add(42);
    bloomFilter.Add(1024);
    bloomFilter.Add(100);

    // Test: Check if the following elements are in the Bloom filter
    std::cout << "Contains 42: " << (bloomFilter.Contains(42) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 1024: " << (bloomFilter.Contains(1024) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 100: " << (bloomFilter.Contains(100) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 999: " << (bloomFilter.Contains(999) ? "Yes" : "No") << std::endl;

    return 0;
}
