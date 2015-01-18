/*
 * This code demonstrates a case where a hash table can outperform a nested loop
 * lookup
 */
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <chrono>

std::vector<int> twoSumHash(std::vector<int> const &numbers, int target) {
    std::unordered_multimap<int, int> map_;

    const auto size = numbers.size();
    map_.reserve(size);
    for (auto i = 0ul; i < size; ++i) {
        map_.emplace(numbers[i], int(i));
    }

    for (auto first = 0ul; first < size; ++first) {
        const auto sec_range = map_.equal_range(target - numbers[first]);
        for (auto it = sec_range.first; it != sec_range.second; ++it) {
            if (it->second > int(first)) {
                return std::vector<int>{int(first + 1),
                                        int(it->second + 1)};
            }
        }
    }

    return std::vector<int>{0, 0};  // Only hit when error.
}

std::vector<int> twoSumLoop(std::vector<int> const &numbers, int target) {
    const auto size = numbers.size();
    for (auto first = 0ul; first < size; ++first) {
        const auto diff = target - numbers[first];
        for (auto sec = first + 1; sec < size; ++sec) {
            if (numbers[sec] == diff) {
                return std::vector<int>{int(first + 1), int(sec + 1)};
            }
        }
    }

    return std::vector<int>{0, 0};  // Only hit when error.
}

int main() {
    using namespace std::chrono;

    // Test case 
    std::vector<int> test = {0,1,0};
    auto sol = twoSumHash(test, 0);
    if(sol[0] == 1 && sol[1] == 3){
        std::cout << "Test passed\n";
    } else {
        std::cout << "Test failed\n";
    }

    for (auto i = 10; i < 100001; i *= 10) {
        std::vector<int> vec(i);
        std::iota(vec.begin(), vec.end(), 1);

        const auto target = vec.back() + vec[i - 2];

        steady_clock::time_point t1 = steady_clock::now();
        auto sol_hash = twoSumHash(vec, target);

        steady_clock::time_point t2 = steady_clock::now();

        auto sol_loop = twoSumLoop(vec, target);
        steady_clock::time_point t3 = steady_clock::now();

        auto time_hash = duration_cast<duration<double>>(t2 - t1);
        auto time_loop = duration_cast<duration<double>>(t3 - t2);

        std::cout << "Vector size = " << vec.size() << "\n";
        std::cout << "\tHash Index 1 = " << sol_loop[0]
                  << " Index 2 = " << sol_loop[1] << " in " << time_hash.count()
                  << " seconds\n";
        std::cout << "\tLoop Index 1 = " << sol_hash[0]
                  << " Index 2 = " << sol_hash[1] << " in " << time_loop.count()
                  << " seconds\n";
    }
    return 0;
}
