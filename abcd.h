#include <iostream>
#include "ker.h"

namespace binom {
    namespace quartet {
        template <size_t n>
        struct term
        {
            private:
                const double a, b, c, d;
            public:
                static const size_t power {n};
            term(double _a, double _b, double _c, double _d): a(_a), b(_b), c(_c), d(_d){}
            template <size_t i, size_t j, size_t k>
            inline double value() const 
            {
//                 std::cout << Comb<n,i>::value * Comb<n-i,j>::value * Comb<n-i-j,k>::value << ' ';
//                      if (i> 1) std::cout << " * a^" << i;
//                 else if (i==1) std::cout << " * a";
// 
//                      if (j> 1) std::cout << " * b^" << j;
//                 else if (j==1) std::cout << " * b";
// 
//                      if (k> 1) std::cout << " * c^" << k;
//                 else if (k==1) std::cout << " * c";
//                 
//                 auto m {n-i-j-k};
//                 
//                      if (m> 1) std::cout << " * d^" << m;
//                 else if (m==1) std::cout << " * d";
// 
//                 std::cout << std::endl;
                return Comb<n,i>::value * Comb<n-i,j>::value * Comb<n-i-j,k>::value * pow_t<i>(a) * pow_t<j>(b) * pow_t<k>(c) * pow_t<n-i-j-k>(d);
            }
        };
        
        template<class valuable>
        struct summijk {
            private:
                valuable& v;
                double result;
            public:
                
                summijk(valuable& val):v(val), result(0.0){}
                
                template<size_t i, size_t j, size_t k>
                inline void apply()
                {
                    result += v.template value<i, j, k>();
                }
                inline double get_result()const
                {
                    return result;
                }
        };
        
        template<size_t n, size_t i, size_t j, size_t k, class appliable>
        inline void meta_loop_inner(appliable& a)
        {
            if constexpr (k==n-i-j+1)
            {
            
            }
            else
            {
                a.template apply<i,j,k>();
                meta_loop_inner<n,i,j,k+1>(a);
            }
            return;
        }
        
        template<size_t n, size_t i, size_t j, class appliable>
        inline void meta_loop_center(appliable& a)
        {
            if constexpr (j==n-i+1)
            {
            
            }
            else
            {
                meta_loop_inner<n,i,j,0>(a);
                meta_loop_center<n,i,j+1>(a);
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
                meta_loop_center<n,i,0>(a);
                meta_loop_outer<n,i+1>(a);
            }
            return;
        }        
        
        template<size_t n, class Term>
        inline double getSumm(Term& t)
        {
            summijk<Term> s(t);
            meta_loop_outer<n,0>(s);
            return s.get_result();
        }        
        
        template<size_t n>
        inline double binom_abcd(double _a, double _b, double _c, double _d)
        {
            term<n> t(_a, _b, _c, _d);
            double res = getSumm<n>(t);
            return res;
        }
        
        
    }
    
    
    
}
