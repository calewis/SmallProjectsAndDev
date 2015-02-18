#include <memory>
#include <iostream>

int func(std::shared_ptr<int> const &pi){
    std::cout << "Called const & overload" << std::endl;
    return *pi;
}

int func(std::shared_ptr<int> &pi){
    std::cout << "Called & overload" << std::endl;
    return *pi;
}
    
int func(std::shared_ptr<int> &&pi){
    std::cout << "Called && overload" << std::endl;
    return *pi;
}

int func(std::shared_ptr<int> const &&pi){
    std::cout << "Called const const && overload" << std::endl;
    return *pi;
}

using namespace std;
shared_ptr<int> make_shared_int(int i){
    return make_shared<int>(i);
}

const shared_ptr<int> make_shared_int_const(int i){
    return make_shared<int>(i);
}

int main(){
    shared_ptr<int> pi = make_shared<int>(1);
    std::cout << "Testing with lvalue shared_ptr." << std::endl;
    func(pi);

    const shared_ptr<int> pj = make_shared<int>(3);
    std::cout << "\nTesting with const lvalue shared_ptr." << std::endl;
    func(pj);

    shared_ptr<int> const &rpj = pj;
    std::cout << "\nTesting with const lvalue ref shared_ptr." << std::endl;
    func(rpj);

    std::cout << "\nTesting with const rvalue shared_ptr." << std::endl;
    func(make_shared_int(2));

    shared_ptr<int> && rvpz = make_shared_int(3);
    std::cout << "\nTesting with const rvalue shared_ptr." << std::endl;
    func(rvpz);

    shared_ptr<int> const&& q = make_shared<int>(5);
    std::cout << "\nTesting with const rvalue ref shared_ptr." << std::endl;
    func(q);

    std::cout << "\nTesting with const rvalue shared_ptr." << std::endl;
    func(make_shared_int_const(2));


    return 0;
}
