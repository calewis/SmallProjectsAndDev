/*
 * Project Euler Problem 1
 */
#include <iostream>

int problem1(int n){
    auto ans = 0;
    for(auto i = 0; i < n; ++i){
        if(i % 3 == 0 || i % 5 == 0){
            ans += i;
        }
    }
    return ans;
}


int main(int argc, char *argv[]) { 
    auto n = 0;
    if(argc == 2){
        n = std::stoi(argv[1]);
    } else {
        std::cout << "Input the int you want to sum.\n";
        return 0;
    }
    
    std::cout << "Answer for " << n << " = " << problem1(n) << "\n";
    return 0; 
}
