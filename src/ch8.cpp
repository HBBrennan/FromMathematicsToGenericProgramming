#include <type_traits>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator> 

#ifndef __cpp_concepts
assert(false)
#endif

using std::ostream;
using std::vector;
using std::endl;
using std::cout;


template<typename T>
concept Integral = std::is_integral<T>::value;

template <class T>
concept SignedIntegral = Integral<T> && std::is_signed<T>::value;

template <SignedIntegral T>
class Polynomial {
public:
    Polynomial() : coeffs{0} {}
    Polynomial(std::initializer_list<T> l) : coeffs{std::rbegin(l), std::rend(l)} { }

    size_t degree() const { return coeffs.size() - 1; }

    friend ostream& operator<<(ostream& os, const Polynomial& p) {
        p.shrink();
        for (size_t i = p.coeffs.size(); i > 0; i--) {
            cout << ' ';
            if (i != p.coeffs.size() && p.coeffs[i - 1] > 0)
                os << "+";
            os << p.coeffs[i - 1];
            if (i > 0)
                os << "x**" << i - 1;
        }
        return os;
    }

    Polynomial operator-(const Polynomial& other) const
    {
        Polynomial ret = *this;
        if (other.degree() > ret.degree())
            ret.resize(other.coeffs.size());
        
        for (size_t i = 0; i < std::min(ret.coeffs.size(), other.coeffs.size()); i++) {
            ret.coeffs[i] -= other.coeffs[i];
        }

        ret.shrink();
        return ret;
    }

    bool operator=(const Polynomial& other) const { return degree() == other.degree() && coeffs == other.coeffs; }
    void shrink() {
        
     }

private:
    vector<T> coeffs;

    void resize(size_t newDegree) {
        assert(newDegree > 0);
        if (newDegree > degree())
            coeffs.resize(newDegree + 1);
    }
};

// template <InputIterator I, Semiring R>
// R polynomial_value(I first, I last, R x) {
//     if (first == last) return R(0);
//     R sum(*first);
//     while (++first != last) {
//         sum *= x;
//         sum += *first;
//     }
//     return sum;
// }


template<typename T>
Polynomial<T> gcd(Polynomial<T> a, Polynomial<T> b) {
    while (b != polynomial<T>(0)) {
        a = remainder(a, b);
        std::swap(a, b);
    }
    return a;
}

int main() {
    Polynomial<int64_t> problem1a({16, -54, -88, 278, 105});
    Polynomial<int64_t> problem1b({16, -64, -44, 232, 70});

    cout << "Polynomial1 = " << problem1a << endl;
    cout << "Polynomial2 = " << problem1b << endl;

    cout << "Polynomial1 - Polynomial2 = " << problem1b - problem1b;

    return 0;
}