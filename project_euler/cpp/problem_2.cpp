/*
 * Project Euler Problem 2
 */
#include <iostream>
#include <vector>
#include <numeric>

int problem_2(int max_val) {
    std::vector<int> fibs = {1, 1};

    while (fibs.back() < max_val) {
        auto last_elem = *(fibs.end() - 1);
        auto sec_last_elem = *(fibs.end() - 2);
        fibs.push_back(last_elem + sec_last_elem);
    }

    return std::accumulate(fibs.begin(), fibs.end(), 0, [](int x, int fib) {
        if (fib % 2 == 0) {
            x += fib;
        };
        return x;
    });
}

int main() {
    std::cout << "Answer problem 2 = " << problem_2(4000000) << std::endl;
    return 0;
}
