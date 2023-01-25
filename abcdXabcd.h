#include <iostream>
#include "ker.h"

namespace binom {
    namespace two_quartet {
        
        
        template <class valuable>
        struct summijk;
        
        template <size_t n>
        struct term;
        
        template<class valuable, class term>
        struct summijkOuter;
        
// ********************************************* //
// ********************************************* //
// ********************************************* //
// ***********                     ************* //
// ***********  meta_inloop_inner  ************* //
// ***********                     ************* //
// ********************************************* //
// ********************************************* //
// ********************************************* //
        template<size_t n,
                 size_t i,
                 size_t j,
                 size_t k,
                 size_t io,
                 size_t jo,
                 size_t ko,
                 class valuable,
                 class appliable>
        inline void meta_inloop_inner(valuable& v, appliable& a)
        {
            if constexpr (k==n-i-j+1)
            {
            
            }
            else
            {
                a.template apply<i,j,k,io,jo,ko>(v);
                meta_inloop_inner<n,i,j,k+1,io,jo,ko>(v, a);
            }
            return;
        }
// ********************************************* //
// ********************************************* //
// ********************************************* //
// ***********                      ************ //
// ***********  meta_inloop_center  ************ //
// ***********                      ************ //
// ********************************************* //
// ********************************************* //
// ********************************************* //
        template<size_t n,
                 size_t i,
                 size_t j,
                 size_t io,
                 size_t jo,
                 size_t ko,
                 class valuable,
                 class appliable>
        inline void meta_inloop_center(valuable& v, appliable& a)
        {
            if constexpr (j==n-i+1)
            {
            
            }
            else
            {
                meta_inloop_inner<n, i, j, 0, io, jo, ko>(v, a);
                meta_inloop_center<n, i, j+1, io, jo, ko>(v, a);
            }
            return;
        }
// ********************************************* //
// ********************************************* //
// ********************************************* //
// ***********                     ************* //
// ***********  meta_inloop_outer  ************* //
// ***********                     ************* //
// ********************************************* //
// ********************************************* //
// ********************************************* //
        template <size_t n,
                  size_t i,
                  size_t io,
                  size_t jo,
                  size_t ko,
                  class valuable,
                  class appliable>
        inline void meta_inloop_outer(valuable& v, appliable& a)
        {
            if constexpr (i==n+1)
            {
                
            }
            else
            {
                meta_inloop_center<n,i,0, io, jo, ko>(v, a);
                meta_inloop_outer<n,i+1, io, jo, ko>(v, a);
            }
            return;
        }

// ******************************************** //
// ******************************************** //
// ******************************************** //
// ***********                      *********** //
// ***********  meta_outloop_inner  *********** //
// ***********                      *********** //
// ******************************************** //
// ******************************************** //
// ******************************************** //
        template<size_t n,
                 size_t i,
                 size_t j,
                 size_t k,
                 class appliable>
        inline void meta_outloop_inner(appliable& a)
        {
            if constexpr (k==n-i-j+1)
            {
            
            }
            else
            {
                a.template apply<i,j,k>();
                meta_outloop_inner<n,i,j,k+1>(a);
            }
            return;
        }        
// ******************************************** //
// ******************************************** //
// ******************************************** //
// ***********                       ********** //
// ***********  meta_outloop_center  ********** //
// ***********                       ********** //
// ******************************************** //
// ******************************************** //
// ******************************************** //
        template<size_t n,
                 size_t i,
                 size_t j,
                 class appliable>
        inline void meta_outloop_center(appliable& a)
        {
            if constexpr (j==n-i+1)
            {
            
            }
            else
            {
                meta_outloop_inner<n, i, j, 0>(a);
                meta_outloop_center<n, i, j+1>(a);
            }
            return;
        }        
// ******************************************** //
// ******************************************** //
// ******************************************** //
// ***********                      *********** //
// ***********  meta_outloop_outer  *********** //
// ***********                      *********** //
// ******************************************** //
// ******************************************** //
// ******************************************** //
        template <size_t n,
                  size_t i,
                  class appliable>
        inline void meta_outloop_outer(appliable& a)
        {
            if constexpr (i==n+1)
            {
                
            }
            else
            {
                meta_outloop_center<n,i,0>(a);
                meta_outloop_outer<n,i+1>(a);
            }
            return;
        }
        
        
        
        
        
        template<class valuable>
        struct summijk {
            private:
                valuable& v;
                double result;
            public:
                
                summijk(valuable& val):v(val), result(0.0){}
                
                
                
                
                template<size_t i,
                         size_t j,
                         size_t k,
                         size_t io,
                         size_t jo,
                         size_t ko,
                         class termtype>
                inline void apply(termtype& t)
                {
                    result += v.template value<i, j, k, io, jo, ko>(t);
                }
                
                
                
                inline double get_result()const
                {
                    return result;
                }
        };
        
        
        template <size_t n>
        struct term
        {
            private:
                const double a, b, c, d;
            public:
                static constexpr size_t power {n};
                term(double _a, double _b, double _c, double _d): a(_a), b(_b), c(_c), d(_d){}
                
                inline double geta()const{return a;}
                inline double getb()const{return b;}
                inline double getc()const{return c;}
                inline double getd()const{return d;}
                                
            
            template <size_t i,
                      size_t j,
                      size_t k,
                      size_t io,
                      size_t jo,
                      size_t ko,
                      class termtype>
            inline double value(termtype& t) const
            {
                const double prev = Comb<termtype::power      , io>::value * 
                                    Comb<termtype::power-io   , jo>::value * 
                                    Comb<termtype::power-io-jo, ko>::value * 
                                    pow_t<io>(t.geta()) * 
                                    pow_t<jo>(t.getb()) * 
                                    pow_t<ko>(t.getc()) * 
                                    pow_t<termtype::power-io-jo-ko>(t.getd());
                                    
                const double curr = Comb<n    , i>::value *
                                    Comb<n-i  , j>::value *
                                    Comb<n-i-j, k>::value * 
                                    pow_t<i>(a) * 
                                    pow_t<j>(b) * 
                                    pow_t<k>(c) * 
                                    pow_t<n-i-j-k>(d);
                return prev * curr;
            }
            
            
            template <size_t i,
                      size_t j,
                      size_t k,
                      class termtype>
            inline double value(termtype& t) const 
            {
                summijk<termtype> myAccumulator(t);
                meta_inloop_outer<termtype::power, 0, i, j, k>(*this, myAccumulator);
                return myAccumulator.get_result();

//                 const double prev = Comb<term::power      , io>::value * 
//                                     Comb<term::power-io   , jo>::value * 
//                                     Comb<term::power-io-jo, ko>::value * 
//                                     pow_t<io>(term.geta()) * 
//                                     pow_t<jo>(term.getb()) * 
//                                     pow_t<ko>(term.getc()) * 
//                                     pow_t<term::power-io-jo-ko>(term.getd());
//                                     
//                 const double curr = Comb<n    , i>::value *
//                                     Comb<n-i  , j>::value *
//                                     Comb<n-i-j, k>::value * 
//                                     pow_t<i>(a) * 
//                                     pow_t<j>(b) * 
//                                     pow_t<k>(c) * 
//                                     pow_t<n-i-j-k>(d);
                
                
//                 return prev * curr;
            }
            
            
        };
        
        
        template<class valuable, class term>
        struct summijkOuter {
            private:
                valuable& v;
                term& t;
                double result;
            public:
                
                
                
                
                summijkOuter(valuable& val, term& tm):v(val), t(tm), result(0.0){}

                
                
                template<size_t i,
                         size_t j,
                         size_t k>
                inline void apply()
                {
                    result += v.template value<i, j, k>(t);
                }
                
                
                
                inline double get_result()const
                {
                    return result;
                }
        };        

        template<class TermLeftType, class TermRightType>
        inline double getSumm(TermLeftType& tle, TermRightType& tri)
        {
            summijkOuter<TermRightType, TermLeftType> ss(tri, tle);
            meta_outloop_outer<TermRightType::power, 0>(ss);
            return ss.get_result();
        }
        
        template <size_t nle, size_t nri>
        inline double binom_a1b1c1d1_a2b2c2d2(
                                double ale, double ble, double cle, double dle,
                                double ari, double bri, double cri, double dri)
        {
                term<nle> tle(ale, ble, cle, dle);
                term<nri> tri(ari, bri, cri, dri);
                return getSumm(tle, tri);
        }        
    }
}
