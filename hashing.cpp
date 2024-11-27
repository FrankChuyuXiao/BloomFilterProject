#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

const int p = 10061; // A prime number greater than or equal to N = 10000
const int m = 1000;  // Size of the Bloom filter table (m << N)

// Generate a random number between a range
int random_in_range(int min, int max) {
    static std::random_device rd;  
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(min, max); 
    return dis(gen);
}

//First hash function
int hash_function1(int x, int ai, int bi) {
    // h_i(x) = ((a_i * x + b_i) % p) % m
    return ((ai * x + bi) % p) % m;
}

// Second hash function
int hash_function2(int x, int si, std::mt19937& gen) {
    // Using mersenne twister to generate a random number seeded with s_i + x
    std::uniform_int_distribution<> dis(0, m-1);
    return dis(gen); // Generate random number in range [0, m-1]
}

int main() {
    int x;
    std::cout << "Enter an integer (x) to hash: ";
    std::cin >> x;

    int ai = random_in_range(1, p-1);
    int bi = random_in_range(0, p-1);
    int si = random_in_range(1, p-1);

    std::random_device rd;
    std::mt19937 gen(rd());

    int result1 = hash_function1(x, ai, bi);
    int result2 = hash_function2(x, si, gen);

    std::cout << "Hash Function 1 result: " << result1 << std::endl;
    std::cout << "Hash Function 2 result: " << result2 << std::endl;


    return 0;
}
