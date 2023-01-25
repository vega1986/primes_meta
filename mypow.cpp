#include <iostream>
#include <cmath>
    // #include "aplusbn.h"
    // #include "abc.h"
    // #include "abcd.h"
    // #include "abcdXabcd.h"
    // #include "a1b1c1d1n1Xa2b2c2d2n2.h"
//#include "a1b1c1d1n1a2b2c2d2n2.h"
#include "primes.h"

int main()
{
    using namespace std;
//     using namespace binom::triplet;
//     using namespace binom::quartet;


//     using namespace binom::two_quartet;
    //using namespace binom::two_quartet;

    cout << "5-th prime number is " << prime_value<5>::value << endl;
    cout << "113-th prime number is " << prime_value<113>::value << endl;


//     primes<33>::type pr;
//     static_assert(pr == 0);


//     cout << pow_t<-13>(3.0) << endl;
//     cout << prime_value<5>::value << endl;
//
//     cout << "factorial" << endl;
//     cout << "7! = " << factorial<7>::value << endl;
//     cout << "C(4,0) = " << Comb<4,0>::value << endl;
//
//     cout << "binom<5>(1.23, 2.34) = " << binom<5>(1.23, 2.34) << endl;

//     meta_loop_outer<3,0>();
//     cout << binom_apbn<12>(1,1) << endl;

//     cout << binom_abcd<5>(0.55394, 0.49857, 0.34578, 0.64329) << endl;


//     cout << binom_a1b1c1d1_a2b2c2d2<3,5>(0.55394, 0.49857, 0.34578, 0.64329,
//                                          1.03254, 0.65987, 2.35665, 1.22343) << endl;

//         cout << binom_a1b1c1d1_a2b2c2d2<3,5>(0.55394, 0.49857, 0.34578, 0.64329,
//                                              1.03254, 0.65987, 2.35665, 1.22343);

    //cout << get_summ<5,6>(0.55394, 0.49857, 0.34578, 0.64329,
    //                      1.03254, 0.65987, 2.35665, 1.22343) << endl;


    // cout << pow(0.55394+0.49857+0.34578+0.64329,5) * pow(1.03254+0.65987+2.35665+1.22343,6) << endl;

    return 0;
}
