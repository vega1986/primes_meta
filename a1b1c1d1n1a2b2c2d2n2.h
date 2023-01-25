#include <iostream>
#include "ker.h"


namespace binom {

    namespace two_quartet {
        
        struct term {
        private:
            double a, b, c, d;
        public:
            inline double geta(){return a;}
            inline double getb(){return b;}
            inline double getc(){return c;}
            inline double getd(){return d;}
            
            term(double _a, double _b, double _c, double _d):a(_a), b(_b), c(_c), d(_d){}
        };
        
        
        class Summator {
        private:
            term left;
            term righ;
            double result {0.0};
        public:
            Summator(term _left, term _righ): left(_left), righ(_righ){}
            
            double get_result(){return result;}
            
            template <size_t nr,size_t nl,size_t ir,size_t jr,size_t kr,size_t il,size_t jl,size_t kl>
            void apply()
            {
                
                size_t constexpr koeff = 
                          
                          Comb<nr      , ir>::value * 
                          Comb<nr-ir   , jr>::value * 
                          Comb<nr-ir-jr, kr>::value * 
                          
                          Comb<nl      , il>::value * 
                          Comb<nl-il   , jl>::value * 
                          Comb<nl-il-jl, kl>::value;
                          
                result += 
                       koeff * 
                       
                       pow_t<ir         >(righ.geta()) * 
                       pow_t<jr         >(righ.getb()) * 
                       pow_t<kr         >(righ.getc()) * 
                       pow_t<nr-ir-jr-kr>(righ.getd()) * 
                       
                       pow_t<il         >(left.geta()) * 
                       pow_t<jl         >(left.getb()) * 
                       pow_t<kl         >(left.getc()) * 
                       pow_t<nl-il-jl-kl>(left.getd());
                
            }
        };
        
        
        

        template <class any, size_t nr, size_t nl, size_t ir, size_t jr, size_t kr, size_t il, size_t jl, size_t kl=0>
        inline void meta_loop_kl(any& a)
        {
            if constexpr (kl==nl-il-jl+1)
            {
                
            }
            else
            {
                a.template apply<nr,nl,ir,jr,kr,il,jl,kl>();
                meta_loop_kl<any,nr,nl,ir,jr,kr,il,jl,kl+1>(a);
            }
            
        }
        
        
        template <class any, size_t nr, size_t nl, size_t ir, size_t jr, size_t kr, size_t il, size_t jl=0>
        inline void meta_loop_jl(any& a)
        {
            if constexpr (jl==nl-il+1)
            {
                
            }
            else
            {
                meta_loop_kl<any,nr,nl,ir,jr,kr,il,jl>(a);
                meta_loop_jl<any,nr,nl,ir,jr,kr,il,jl+1>(a);
            }
        }
        
        
        
        template <class any, size_t nr, size_t nl, size_t ir, size_t jr, size_t kr, size_t il=0>
        inline void meta_loop_il(any& a)
        {
            if constexpr (il==nl+1)
            {
                
            }
            else
            {
                meta_loop_jl<any,nr,nl,ir,jr,kr,il>(a);
                meta_loop_il<any,nr,nl,ir,jr,kr,il+1>(a);
            }
        }
        
        template <class any, size_t nr, size_t nl, size_t ir, size_t jr, size_t kr=0>
        inline void meta_loop_kr(any& a)
        {
            if constexpr (kr==nr-ir-jr+1)
            {
                
            }
            else
            {
                meta_loop_il<any,nr,nl,ir,jr,kr>(a);
                meta_loop_kr<any,nr,nl,ir,jr,kr+1>(a);
            }
            
        }
        
        
        template<class any, size_t nr, size_t nl, size_t ir, size_t jr=0>
        inline void meta_loop_jr(any& a)
        {
            if constexpr (jr==nr-ir+1)
            {
                
            }
            else
            {
                meta_loop_kr<any,nr,nl,ir,jr>(a);
                meta_loop_jr<any,nr,nl,ir,jr+1>(a);
            }
            
            
        }
        
        template<class any, size_t nr, size_t nl, size_t ir=0>
        inline void meta_loop_ir(any& a)
        {
            if constexpr (ir==nr+1)
            {
                
            }
            else
            {
                meta_loop_jr<any,nr,nl,ir>(a);
                meta_loop_ir<any,nr,nl,ir+1>(a); 
            }
            
        }
        
        template <size_t nl, size_t nr>
        double get_summ(double al, double bl, double cl, double dl,
                        double ar, double br, double cr, double dr)
        {
            Summator summ(term(al,bl,cl,dl),term(ar,br,cr,dr));
            meta_loop_ir<Summator,nr,nl>(summ);
            return summ.get_result();
        }
        
        
    }

}
