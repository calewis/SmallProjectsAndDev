/*
 * Project Euler problem template
 */

#include <chrono>
#include <iostream>

int problem_N(int input) { return input; }

int main(int argc, char *argv[]) {
    using namespace std::chrono;

    auto t1 = steady_clock::now();
    auto ans = problem_N(1);
    auto t2 = steady_clock::now();

    auto time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "Problem N answer = " << ans << " in " << time_span.count()
              << " seconds.\n";
    return 0;
}
