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

// template<int N>
// typename std::enable_if<(N==0), double>::type pow_t(double x)
// {
//     return 1.0;
// }
// 
// template<int N>
// typename std::enable_if<((N>0) && (N%2==1)), double>::type pow_t(double x)
// {
//     constexpr int hN {N / 2};
//     double t = pow_t<N / 2>(static_cast<double>(x));
//     return x * t * t;
// }
// 
// 
// template<int N>
// typename std::enable_if<((N>0) && (N%2==0)), double>::type pow_t(double x)
// {
//     constexpr int hN {N / 2};
//     double t = pow_t<N / 2>(static_cast<double>(x));
//     return t * t;
// }
// 
// 
// template<int N>
// typename std::enable_if<(N<0), double>::type pow_t(double x)
// {
//     constexpr int mN {-N};
//     return 1.0 / pow_t<-N>(static_cast<double>(x));
// }
// 
// 
