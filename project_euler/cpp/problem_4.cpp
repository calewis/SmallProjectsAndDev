/*
 * Project Euler problem 4
 */

#include <chrono>
#include <iostream>
#include <string>

int problem_4() { 
    auto max = 0ul;

    for(auto i = 100ul; i < 1000ul; ++i){
        for(auto j = 100ul; j < 1000ul; ++j){
            std::string num = std::to_string(i * j);
            if(std::equal(num.begin(), num.end(), num.rbegin())){
                const auto pal = std::stoul(num);
                max = std::max(pal, max);
            }
        }
    }

    return max; 
}

int main(int argc, char *argv[]) {
    using namespace std::chrono;

    auto t1 = steady_clock::now();
    auto ans = problem_4();
    auto t2 = steady_clock::now();

    auto time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "Problem 4 answer = " << ans << " in " << time_span.count()
              << " seconds.\n";
    return 0;
}
