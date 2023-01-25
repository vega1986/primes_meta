#include <iostream>
#include <cmath>
//#include "abcdXabcd.h"
#include "primes.h"
#include "a1b1c1d1n1a2b2c2d2n2.h"

int main()
{
    using namespace std;

    cout << "Example 1" << endl;
    cout << "calculation of prime values" << endl;
    cout << " 5-th prime number is " << prime_value< 5>::value << endl;
    cout << "13-th prime number is " << prime_value<13>::value << endl;
    cout << endl << " ********************************************** " << endl;

    using namespace binom::two_quartet;
    cout << "Example №2" << endl;
    cout << "expand of brackets at compilation time of expression" << endl;
    cout << "(Al + Bl + Cl + Dl)^n1 * (Ar + Br + Cr + Dr)^n2" << endl;
    cout << "below are the each term of expanded expression and the result of the sum" << endl;

    constexpr double al{ 0.55394 };
    constexpr double bl{ 0.49857 };
    constexpr double cl{ 0.34578 };
    constexpr double dl{ 0.64329 };

    constexpr double ar{ 1.03254 };
    constexpr double br{ 0.65987 };
    constexpr double cr{ 2.35665 };
    constexpr double dr{ 1.22343 };

    cout << "template result = " << get_summ<2, 3>(al, bl, cl, dl, /**/ ar, br, cr, dr) << endl;

    cout << "direct result = " << std::pow(al + bl + cl + dl, 2.0) * std::pow(ar + br + cr + dr, 3.0) << std::endl;

    return 0;
}
