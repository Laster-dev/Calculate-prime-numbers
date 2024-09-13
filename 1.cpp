#include <iostream>
#include <vector>
#include <chrono>
#include <bitset>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const int MAX = 1000000;
    std::bitset<MAX + 1> is_prime;
    is_prime.set();
    is_prime.reset(0);
    is_prime.reset(1);
    for (int p = 2; p * p <= MAX; p++) {
        if (is_prime[p]) {
            for (int multiple = p * p; multiple <= MAX; multiple += p) {
                is_prime.reset(multiple);
            }
        }
    }
    std::vector<int> primes;
    primes.reserve(MAX / 10);
    for (int i = 2; i <= MAX; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    auto start_time = std::chrono::high_resolution_clock::now();
    size_t buffer_size = primes.size() * 10;
    char* buffer = new char[buffer_size];
    size_t pos = 0;
    for (size_t i = 0; i < primes.size(); i++) {
        int current_prime = primes[i];
        if (current_prime + 2 > MAX) break;
        if (is_prime[current_prime + 2]) {
            pos += sprintf(buffer + pos, "%d %d\n", current_prime, current_prime + 2);
        }
    }
    fwrite(buffer, sizeof(char), pos, stdout);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    printf("程序执行时间: %ld 微秒\n", duration);
    delete[] buffer;
    return 0;
}
