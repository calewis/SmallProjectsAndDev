#include <vector>
#include <iostream>

#include "n_for_each.h"

int main() {
    std::vector<int> elem = {1, 2, 3, 4, 5};

    auto sum = [](int out, int in) { return out + in; };
    auto product = [](int out, int in) {
        if (out == 0) {
            return 1 * in;
        } else {
            return out * in;
        }
    };

    auto pair = n_for_each(elem, elem, sum, product);
    std::cout << "Sum = " << std::get<0>(pair) << " product = " << std::get<1>(pair) << std::endl;

    return 0;
}
