/*
 * Project Euler problem 2
 */

#include <chrono>
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

int problem_2_fast(int max_val) {
    auto a = 0;
    auto b = 1;
    auto sum = 0;
    while (b < max_val) {
        const auto old_b = b;
        b = b + a;
        a = old_b;
        sum += (b % 2 == 0) ? b : 0;
    }

    return sum;
}

int main(int argc, char *argv[]) {
    auto max_val = 0;
    if (argc == 2) {
        max_val = std::stoi(argv[1]);
    } else {
        std::cout << "Program behavior => ./prog input_value\n";
        return 0;
    }

    using namespace std::chrono;

    auto t1 = steady_clock::now();
    auto ans = problem_2(max_val);
    auto t2 = steady_clock::now();
    auto ans_fast = problem_2_fast(max_val);
    auto t3 = steady_clock::now();

    auto time_span = duration_cast<duration<double>>(t2 - t1);
    auto time_span1 = duration_cast<duration<double>>(t3 - t2);

    std::cout << "Problem 2 answer \t= " << ans << " in " << time_span.count()
              << " seconds.\n";
    std::cout << "Problem 2 answer fast \t= " << ans_fast << " in "
              << time_span1.count() << " seconds.\n";
    return 0;
}
