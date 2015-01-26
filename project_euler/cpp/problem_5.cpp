/*
 * Project Euler problem 5 smallest number divisible by 1..20
 */

#include <chrono>
#include <iostream>
#include <numeric>
#include <array>

// Loop over multiples of 20 only divide by numbers which aren't factors of 20
unsigned long problem_5_fast() {
    unsigned long ans = 20;

    // Any number which is a factor of a larger number can be ignored. 12 can 
    // be ignored because if the number is diviable by both 18 and 16 then 
    // it will also be divisible by 12, this idea leads us to a very fast 
    // solution.  We could factor all the numbers between 1 and 20 and then 
    // just multiply unique factors to find the number. 
    while (!(ans % 19 == 0 && ans % 18 == 0 && ans % 17 == 0 && ans % 16 == 0 &&
             ans % 15 == 0 && ans % 14 == 0 && ans % 13 == 0 &&
             ans % 11 == 0)) {
        ans += 20;
    }
    return ans;
}

unsigned long problem_5() {
    std::array<unsigned long, 20> nums;
    std::iota(nums.begin(), nums.end(), 1);

    unsigned long ans = 1;
    auto is_divisable =
        [&ans](unsigned long divisor) { return 0 == ans % divisor; };

    while (!std::all_of(nums.begin(), nums.end(), is_divisable)) {
        ++ans;
    }
    return ans;
}

int main(int argc, char *argv[]) {
    using namespace std::chrono;

    auto t1 = steady_clock::now();
    auto ans = problem_5();
    auto t2 = steady_clock::now();
    auto ans_fast = problem_5_fast();
    auto t3 = steady_clock::now();

    auto time_span = duration_cast<duration<double>>(t2 - t1);
    auto time_span_fast = duration_cast<duration<double>>(t3 - t2);

    std::cout << "Problem 5 answer = " << ans << " in " << time_span.count()
              << " seconds.\n";
    std::cout << "Problem 5 fast answer = " << ans_fast << " in "
              << time_span_fast.count() << " seconds.\n";
    return 0;
}
