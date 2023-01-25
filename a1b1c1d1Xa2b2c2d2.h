#include <iostream>
#include "ker.h"

namespace binom {
    namespace two_quartet {
        
        
        

        struct summijk;
        struct term;
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
        template<size_t nr,
                 size_t ir,
                 size_t jr,
                 size_t kr,
                 size_t nl,
                 size_t il,
                 size_t jl,
                 size_t kl>
        inline void meta_inloop_inner(term& righ, summijk& s)
        {
            if constexpr (kl==nl-il-jl+1)
            {
            
            }
            else
            {
                s.template apply<nr,ir,jr,kr,nl,il,jl,kl>(righ);
                meta_inloop_inner<nr,ir,jr,kr,nl,il,jl,kl+1>(righ, s);
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
        template<size_t nr,
                 size_t ir,
                 size_t jr,
                 size_t kr,
                 size_t nl,
                 size_t il,
                 size_t jl>
        inline void meta_inloop_center(term& righ, summijk& s)
        {
            if constexpr (jl==nl-il+1)
            {
            
            }
            else
            {
                meta_inloop_inner<nr,ir,jr,kr,nl,il,jl,0>(righ, s);
                meta_inloop_center<nr,ir,jr,kr,nl,il,jl+1>(righ, s);
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
        template <size_t nr,
                  size_t ir,
                  size_t jr,
                  size_t kr,
                  size_t nl,
                  size_t il>
        inline void meta_inloop_outer(term& righ, summijk& s)
        {
            if constexpr (il==nl+1)
            {
                
            }
            else
            {
                meta_inloop_center<nr,ir,jr,kr,nl,il,0>(righ, s);
                meta_inloop_outer<nr,ir,jr,kr,nl,il+1>(righ, s);
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
        template<size_t nl,
                 size_t nr,
                 size_t ir,
                 size_t jr,
                 size_t kr>
        inline void meta_outloop_inner(summijkOuter& s)
        {
            if constexpr (kr==nr-ir-jr+1)
            {
            
            }
            else
            {
                s.template apply<nr,ir,jr,kr,nl>();
                meta_outloop_inner<nl,nr,ir,jr,kr+1>(s);
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
        template<size_t nl,
                 size_t nr,
                 size_t ir,
                 size_t jr>
        inline void meta_outloop_center(summijkOuter& s)
        {
            if constexpr (jr==nr-ir+1)
            {
            
            }
            else
            {
                meta_outloop_inner<nl,nr,ir,jr,0>(s);
                meta_outloop_center<nl,nr,ir,jr+1>(s);
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
        template <size_t nl,
                  size_t nr,
                  size_t ir>
        inline void meta_outloop_outer(summijkOuter& s)
        {
            if constexpr (ir==nr+1)
            {
                
            }
            else
            {
                meta_outloop_center<nl,nr,ir,0>(s);
                meta_outloop_outer<nl,nr,ir+1>(s);
            }
            return;
        }
        
        
                
        struct summijk {
            private:
                term& left;
                double result;
            public:
                
                summijk(term& _left):left(_left), result(0.0){}
                template<size_t nr,
                         size_t ir,
                         size_t jr,
                         size_t kr,
                         size_t nl,
                         size_t il,
                         size_t jl,
                         size_t kl>
                inline void apply(term& righ)
                {
                    result += righ.template value<nr,ir,jr,kr,nl,il,jl,kl>(left);
                }
                
                
                
                inline double get_result()const
                {
                    return result;
                }
        };        
        
        
        
        struct term
        {
            private:
                const double a, b, c, d;
            public:
                term(double _a, double _b, double _c, double _d): a(_a), b(_b), c(_c), d(_d){}
                
                inline double geta()const{return a;}
                inline double getb()const{return b;}
                inline double getc()const{return c;}
                inline double getd()const{return d;}
                                
            
                template <size_t n, size_t i, size_t j, size_t k,
                          size_t no, size_t io, size_t jo, size_t ko>
                inline double value(term& outer) const
                {
                    const double prev = Comb<no      , io>::value * 
                                        Comb<no-io   , jo>::value * 
                                        Comb<no-io-jo, ko>::value * 
                                        pow_t<io>(outer.geta()) * 
                                        pow_t<jo>(outer.getb()) * 
                                        pow_t<ko>(outer.getc()) * 
                                        pow_t<no-io-jo-ko>(outer.getd());
                                    
                    const double curr = Comb<n    , i>::value *
                                        Comb<n-i  , j>::value *
                                        Comb<n-i-j, k>::value * 
                                        pow_t<i>(a) * 
                                        pow_t<j>(b) * 
                                        pow_t<k>(c) * 
                                        pow_t<n-i-j-k>(d);
                    return prev * curr;
                }
            
                template <size_t n, size_t i, size_t j, size_t k, size_t nl>
                inline double value(term& left) const 
                {
                    summijk myAccumulator(left);
                    meta_inloop_outer<n, i, j, k, nl, 0>(*this, myAccumulator);
                    return myAccumulator.get_result();
                }
        };        

        struct summijkOuter {
            private:
                term& left;
                term& righ;
                double result;
            public:
                summijkOuter(term& _left, term& _righ):left(_left), righ(_righ), result(0.0){}
                template<size_t nr, size_t ir, size_t jr, size_t kr, size_t nl>
                inline void apply()
                {
                    result += righ.template value<nr, ir, jr, kr, nl>(left);
                }
                inline double get_result()const
                {
                    return result;
                }
        };

        template <size_t nle, size_t nri>
        inline double getSumm(term& tle, term& tri)
        {
            summijkOuter ss(tle, tri);
            meta_outloop_outer<nle, nri, 0>(ss);
            return ss.get_result();
        }
        
        template <size_t nle, size_t nri>
        double binom_a1b1c1d1_a2b2c2d2(
                      double ale, double ble, double cle, double dle,
                      double ari, double bri, double cri, double dri)
        {
                term tle(ale, ble, cle, dle);
                term tri(ari, bri, cri, dri);
                return getSumm<nle, nri>(tle, tri);
        }
        
    }
    
    
    
}
