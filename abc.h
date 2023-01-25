#include <iostream>
#include "ker.h"

namespace binom {
    namespace triplet {
        template <size_t n>
        struct term
        {
            private:
                const double a, b, c;
            public:
            term(double _a, double _b, double _c): a(_a), b(_b), c(_c){}
            template <size_t i, size_t j>
            inline double value() const 
            {
//                 std::cout << Comb<n,i>::value * Comb<n-i,j>::value <<
//                              "a^" << i <<
//                              "b^" << j <<
//                              "c^" << n-i-j << std::endl;
                return Comb<n,i>::value * Comb<n-i,j>::value * pow_t<i>(a) * pow_t<j>(b) * pow_t<n-i-j>(c);
            }
        };
        
        template<class valuable>
        struct summij {
            private:
                valuable& v;
                double result;
            public:
                
                summij(valuable& val):v(val), result(0.0){}
                
                template<size_t i, size_t j>
                inline void apply()
                {
                    result += v.template value<i, j>();
                }
                inline double get_result()const
                {
                    return result;
                }
        };
        
        template<size_t n, size_t i, size_t j, class appliable>
        inline void meta_loop_inner(appliable& a)
        {
            if constexpr (j==n-i+1)
            {
            
            }
            else
            {
                a.template apply<i,j>();
                meta_loop_inner<n,i,j+1>(a);
            }
            return;
        }
        
        template <size_t n, size_t i, class appliable>
        inline void meta_loop_outer(appliable& a)
        {
            if constexpr (i==n+1)
            {
                
            }
            else
            {
                meta_loop_inner<n,i,0>(a);
                meta_loop_outer<n,i+1>(a);
            }
            return;
        }        
        
        template<size_t n, class Term>
        inline double getSumm(Term& t)
        {
            summij<Term> s(t);
            meta_loop_outer<n,0>(s);
            return s.get_result();
        }        
        
        template<size_t n>
        inline double binom_abc(double _a, double _b, double _c)
        {
            term<n> t(_a, _b, _c);
            double res = getSumm<n>(t);
            return res;
        }
        
        
    }
    
    
    
}
