#include <iostream>

// j - last known prime value
template<unsigned j, unsigned v>
struct prime_after;

template<unsigned i>
struct prime_value : std::integral_constant<unsigned, prime_after<i-1, prime_value<i-1>::value>::value>{};

template<>
struct prime_value<0> : std::integral_constant<unsigned, 2>{};

template<>
struct prime_value<1> : std::integral_constant<unsigned, 3>{};

// j - last known prime value index
// i - iterator from 0 to j
template<unsigned v, unsigned j, unsigned i=j>
struct is_prime : std::conditional<
                                    v % prime_value<i>::value == 0,
                                    std::false_type,
                                    is_prime<v, j, i-1> >::type{};

template<unsigned v, unsigned j>
struct is_prime<v,j,0> : std::conditional<v % prime_value<0>::value == 0,
                                    std::false_type,
                                    std::true_type>::type{};

// j - last known prime value
template<unsigned j, unsigned v>
struct prime_after : std::conditional<is_prime<v, j>::value, std::integral_constant<unsigned,v>, prime_after<j,v+2> >::type{};



template<unsigned... I> struct ivector {};
template<class ivec, unsigned i> struct push_back;

template<unsigned... I, unsigned J>
struct push_back<ivector<I...>, J>
{
    using type = ivector<I..., J>;
};

template<unsigned n>
struct primes
{
    using type = typename push_back<
                            typename primes<n-1>::type,
                            prime_value<n-1>::value
                          >
                 ::type;
};

template<>
struct primes<0>
{
    using type = ivector<>;
};
