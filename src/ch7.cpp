#include <iostream>
#include <type_traits>
#include <cassert>
#ifndef __cpp_concepts
assert(false)
#endif

template<typename T>
concept SemiRegular =   std::is_default_constructible<T>::value &&
                        std::is_copy_constructible<T>::value &&
                        std::is_copy_assignable<T>::value &&
                        std::is_move_constructible<T>::value &&
                        std::is_move_assignable<T>::value &&
                        std::is_destructible<T>::value &&
                        std::is_swappable<T>::value;

template<typename T>
concept Integer = std::numeric_limits<T>::is_integer;

template<typename T>
concept Regular = SemiRegular<T> && Integer<T>;

template<typename T>
concept MonoidOperation = true;

template<typename T>
concept SemigroupOperation = true;

template<typename T>
concept GroupOperation = true;

template<typename Op, typename T>
concept Domain = requires (T t) { op(t, t) -> t; };

template <Regular A, Integer N, SemigroupOperation Op>
A power_accumulate_semigroup(A r, A a, N n, Op op) requires Domain<Op, A> {
    assert(n >= 0);
    if (n == 0) return r;
    while (true) {
        if (odd(n)) {
            r = op(r, a);   
            if (n == 1) return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

template <Regular A, Integer N, SemigroupOperation Op>
// Requires Domain<Op, A>
A power_semigroup(A a, N n, Op op) {
    // precondition(n > 0)
    while (!odd(n)) {
        a = op(a, a);
        n = half(n);
    }
    if (n == 1) return a;
    return power_accomulate_semigroup(a, op(a, a), half(n-1), op);
}

template <Regular A, Integer N, MonoidOperation Op>
// requires(Domain<Op, A>)
A power_monoid(A a, N n, Op op) {
    //  precondition(n >= 0)
    if (n == 0) return identity_element(op);
    return power_semigroup(a, n, op);
}


template <Regular A, Integer N, GroupOperation Op>
// requires(Domain<Op, A>)
A power_group(A a, N n, Op op) {
    if (n < 0) {
        n = - n;
        a = inverse_operation(op)(a);
    }
    return power_monoid(a, n, op);
}

// Exercise 7.2. Implement computing Fibonacci numbers using power
int main(int argc, char** argv) {
    return 0;
}