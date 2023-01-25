#include "ker.h"
// (a+b)^N

template <size_t n>
struct a_bTerm
{
    private:
        const double a, b;
    public:
        a_bTerm(double _a, double _b): a(_a), b(_b){}
        template <size_t i/*, size_t j*/>
        inline double value() const 
        {
            std::cout << "i=" << i << ": ";
            std::cout << Comb<n,i>::value << " a^" << i << " b^" << n-i << std::endl;
            return Comb<n,i>::value * pow_t<i>(a) * pow_t<n-i>(b);
            //std::cout << "i=" << i << " j=" << j << std::endl;
//             return Comb<n,i>::value * Comb<n-i,j>::value * pow_t<i>(a) * pow_t<j>(b);
        }
};



template<class valuable>
struct summi {
    private:
        valuable& a;
        double result;
    public:
        
        summi(valuable& _a):a(_a), result(0.0){}
        
        template<size_t i/*, size_t j*/>
        inline void apply()
        {
            result += a.template value<i/*,j*/>();
        }
        inline double get_result()const
        {
            return result;
        }
};



#if 0

template<size_t n, size_t i, size_t j, class appliable>
inline void meta_loop_inner(appliable& a)
{
    if constexpr (j==n-i+1)
    {
    
    }
    else
    {
        //std::cout << "i=" << i << " j=" << j << std::endl;
        a.template apply<i/*,j*/>();
        meta_loop_inner<n,i,j+1>(a);
    }
    
}
#endif


template <size_t n, size_t i, class appliable>
inline void meta_loop_outer(appliable& a)
{
    if constexpr (i==n+1)
    {
        
    }
    else
    {
        //meta_loop_inner<n,i,0>(a);
        a.template apply<i>();
        meta_loop_outer<n,i+1>(a);
    }
}


template<size_t n, class Term>
inline double getSumm(Term& t)
{
    summi<Term> s(t);
    meta_loop_outer<n,0>(s);
    return s.get_result();
//     summij<a_bTerm> s(a_bTerm)
}

template<size_t n>
inline double binom_apbn(double _a, double _b)
{
    a_bTerm<n> term(_a, _b);
    double res = getSumm<n>(term);
    return res;
}
