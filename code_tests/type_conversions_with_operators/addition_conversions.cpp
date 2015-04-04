#include <iostream>
#include <typeinfo>
#include <utility>

class A {
  public:
    A() = default;

    template <typename T,
              typename has_range = decltype(std::declval<T>().range())>
    A(T const &) {}
};

class B {
  public:
    void range() const {}
};
class Bnorange {};

class C {};

C add(A const &, B const &) { return C{}; }

A add(A const &, A const &) { return A{}; }

int main() {
    A a;
    B b;
    auto ApB = add(a, b); // calls C add(A const &, B const &);
    auto ApA = add(a, a); // calls A add(A const &, A const &);
    auto BpA = add(b, a); // calls A add(A const &, A const &);
    auto BpB = add(b, b); // calls C add(A const &, B const &);

    /* Bnorange bnr; */ // Fails to compile since no range.
    /* auto BnrpA = add(bnr, a); */

    std::cout << "auto ApB = add(a,b) type " << typeid(ApB).name() << "\n";
    std::cout << "auto ApA = add(a,a) type " << typeid(ApA).name() << "\n";
    std::cout << "auto BpA = add(b,a) type " << typeid(BpA).name() << "\n";
    std::cout << "auto BpB = add(b,b) type " << typeid(BpB).name() << "\n";

    return 0;
}
