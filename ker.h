// #include <iostream>

template <size_t n>
struct factorial : std::integral_constant<size_t, n * factorial<n-1>::value >{};

template<>
struct factorial<1> : std::integral_constant<size_t, 1>{};

template<>
struct factorial<0> : std::integral_constant<size_t, 1>{};

template <size_t n, size_t k>
struct Comb : std::integral_constant<size_t, factorial<n>::value / factorial<k>::value / factorial<n-k>::value >{};

template<int N>
double pow_t(double x)
{
    if constexpr (N<0)
    {
        return 1.0 / pow_t<-N>(x);
    }
    else if constexpr (N==0)
    {
        return 1.0;
    }
    else if constexpr (N%2==0)
    {
        double t = pow_t<N/2>(x);
        return t * t;
    }
    else
    {
        double t = pow_t<N/2>(x);
        return x * t * t;
    }
}