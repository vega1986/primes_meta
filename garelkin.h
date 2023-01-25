#include <iostream>
#include "ker.h"

template<size_t n, size_t i, class any>
void metaLoopRaw(any& a)
{   
    if constexpr (i==n)
    {
    }
    else
    {
        a.template apply<i>();
        metaLoopRaw<n,i+1>(a);
    }
    return;
}

template<size_t n, class any>
void metaLoop(any& a)
{
    metaLoopRaw<n,0>(a);
    return;
}

// any must have apply template function

template<class Functor>
struct abstractSummator {
    private:
        Functor& func;
        double result;
    public:
        
        abstractSummator(Functor& _func):func(_func), result(0.0){}
        
        template<size_t i>
        void apply()
        {
            result += func.template value<i>();
        }
        double get_result()const
        {
            return result;
        }
};


template <size_t n, class Functor>
double anySumm(Functor& f)
{
    abstractSummator<Functor> mySummator(f);
    metaLoop<n>(mySummator);
    return mySummator.get_result();
}

template <size_t a, size_t b, size_t g>
struct monomial_3d : std::integral_constant<size_t, factorial<a+b+g+3>::value / factorial<a>::value / factorial<b>::value / factorial<g>::value>
{};

template <size_t a, size_t b>
struct monomial_2d : std::integral_constant<size_t, factorial<a+b+2>::value / factorial<a>::value / factorial<b>::value>
{};


// constexpr double monomial_3d(size_t a, size_t b, size_t g)
// {
//     return 
// }

template <size_t n>
struct binomTerm
{
    private:
        const double a, b;
    public:
        binomTerm(double _a, double _b): a(_a), b(_b){}
        template <size_t k>
        double value() const 
        {
            return Comb<n,k>::value * pow_t<k>(a) * pow_t<n-k>(b) / monomial_2d<k, n-k>::value;
        }
};

template <size_t n>
double binom(double a, double b)
{
    binomTerm<n> bt(a, b);
    return anySumm<n+1>(bt);
}

// // Galerkin
// template <size_t a, size_t b, size_t g>
// struct baseFuncBase {
//     static const size_t alpha = a;
//     static const size_t beta  = b;
//     static const size_t gamma = g;
// };
// 
// struct bf_t {
//     using type0 = baseFuncBase<0,0,0>;
//     using type1 = baseFuncBase<1,0,0>;
//     using type2 = baseFuncBase<0,1,0>;
//     using type3 = baseFuncBase<0,0,1>;
//     using type4 = baseFuncBase<2,0,0>;
//     using type5 = baseFuncBase<0,2,0>;
//     using type6 = baseFuncBase<0,0,2>;
//     using type7 = baseFuncBase<1,1,0>;
//     using type8 = baseFuncBase<1,0,1>;
//     using type9 = baseFuncBase<0,1,1>;
// };
// 
// template <size_t i>
// struct get_bf_type{};
// 
// template <>
// struct get_bf_type<0>
// {
//     using type = bf_t::type0;
// };
// 
// template <>
// struct get_bf_type<1>
// {
//     using type = bf_t::type1;
// };
// 
// template <>
// struct get_bf_type<2>
// {
//     using type = bf_t::type2;
// };
// 
// template <>
// struct get_bf_type<3>
// {
//     using type = bf_t::type3;
// };
// 
// template <>
// struct get_bf_type<4>
// {
//     using type = bf_t::type4;
// };
// 
// template <>
// struct get_bf_type<5>
// {
//     using type = bf_t::type5;
// };
// 
// template <>
// struct get_bf_type<6>
// {
//     using type = bf_t::type6;
// };
// 
// template <>
// struct get_bf_type<7>
// {
//     using type = bf_t::type7;
// };
// 
// template <>
// struct get_bf_type<8>
// {
//     using type = bf_t::type8;
// };
// 
// template <>
// struct get_bf_type<9>
// {
//     using type = bf_t::type9;
// };
// 
// 
// 
// // End Galerkin
