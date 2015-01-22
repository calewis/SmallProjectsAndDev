/*
 * Project Euler problem template
 */

#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>

unsigned long problem_3(unsigned long input) {
    std::vector<unsigned long> primes;
    primes.reserve(10); // Assume small number of primes

    const auto limit = std::sqrt(input) + 1;
    for (auto i = 2ul; i < limit; ++i) {
        if (input % i == 0) {
            // Divide i by all smaller primes of input to test for primeyness
            bool prime = true;
            for (auto const &p : primes) {
                if (i % p == 0) {
                    prime = false;
                    break;
                }
            }

            if (prime) {  // if i was prime lets add it to our list of primes
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
