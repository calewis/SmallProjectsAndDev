/*
 * This code finds the median of two sorted arrays
 */
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <chrono>

double vec_median(std::vector<int> const &v) {
    const auto size = v.size();
    if (size == 1) {
        return v[0];
    } else if (size == 2) {
        return double(v[0] + v[1]) / 2.0;
    } else if (size % 2 == 0) {
        const auto upper = size / 2;
        const auto lower = upper - 1;
        return double(v[upper] + v[lower]) / 2.0;
    } else {
        return v[size / 2];
    }
}

// Slow solution that passes test, but isn't optimal.
double median_dumb(int A[], int m, int B[], int n) {
    std::vector<int> combo(m + n);
    std::merge(A, A + m, B, B + n, combo.begin());
    return vec_median(combo);
}

int num_lower(int A[], int m, int value) {
    int count = m;
    int step = count/2;

    auto index = 0;
    auto temp_index = 0;
    while(count > 0){
        temp_index = index;
        step = count/2;
        temp_index += step;
        if(A[temp_index] < value){
            index = ++temp_index;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    return index;
}

int num_higher(int A[], int m, int value) {
    int count = m;
    int step = count/2;

    auto index = 0;
    auto temp_index = 0;
    while(count > 0){
        temp_index = index;
        step = count/2;
        temp_index += step;
        if(!(A[temp_index] > value)){
            index = ++temp_index;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    return m - index;
}

// Finish this later use num_lower and num_upper to solve
double median_smart(int A[], int m, int B[], int n) { 
    auto combined_size = m + n;
    auto auto bounds = m + n;
    if(combined_size % 2 == 0){
        bounds = combined_size/2 - 2;
    } else {
        bounds = combined_size/2;
    }
        
    if(m > n){
        auto middle = m/2;
    return 0.0; 
}

int main() {
    using namespace std::chrono;

#if 1
    for (auto i = 1; i < 100001; i *= 10) {
        std::cout << "Problem size = " << i << "\n";
        std::vector<int> vec(i);
        std::vector<int> vec2(i);
        std::iota(vec.begin(), vec.end(), 1);
        std::iota(vec2.begin(), vec2.end(), 10);

        steady_clock::time_point t1 = steady_clock::now();
        auto med_d = median_dumb(&vec[0], i, &vec2[0], i);
        steady_clock::time_point t2 = steady_clock::now();
        auto med_s = median_smart(&vec[0], i, &vec2[0], i);
        steady_clock::time_point t3 = steady_clock::now();

        auto time_dumb = duration_cast<duration<double>>(t2 - t1);
        auto time_smart = duration_cast<duration<double>>(t3 - t2);

        std::cout << "\tDumb med = " << med_d << " " << time_dumb.count()
                  << " seconds\n";
        std::cout << "\tsmart med = " << med_s << " " << time_smart.count()
                  << " seconds\n";
    }
#endif

    return 0;
}
