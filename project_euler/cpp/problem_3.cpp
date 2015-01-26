/*
 * Project Euler problem template
 */

#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

unsigned long problem_3(unsigned long input) {
    std::vector<unsigned long> primes;
    primes.reserve(10);  // Assume small number of primes

    const auto limit = std::sqrt(input) + 1;
    for (auto i = 2ul; i < limit; ++i) {

        if (input % i == 0) {

            // Divide i by all smaller primes of input to test for primeyness
            if (std::none_of(
                    primes.begin(), primes.end(),
                    [=](unsigned long const &p) { return 0 == i % p; })) {
                primes.push_back(i);
            }

        }

    }

    // Largest prime we found will be the larget prime divisor
    return primes.back();
}

int main(int argc, char *argv[]) {
    using namespace std::chrono;

    auto t1 = steady_clock::now();
    auto ans = problem_3(600851475143);
    auto t2 = steady_clock::now();

    auto time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "Problem 3 answer = " << ans << " in " << time_span.count()
              << " seconds.\n";
    return 0;
}
