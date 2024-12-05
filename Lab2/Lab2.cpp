#include <iostream>
#include "Rational.h"
using namespace std;

int main () {
    
    Rational r1(1,2);
    Rational r2(2,3);
    Rational r3(3,4);
    Rational r4(4,5);
    
    cout << r1 << "\n";
    cout << r2 << "\n";
    cout << r3 << "\n";
    cout << r4 << "\n";
    
    cout << r1 << " plus " << r2 << " = " << r1+r2 << "\n";
    cout << r3 << " minus " << r4 << " = " << r3-r4 << "\n";
    cout << r1 << " multiplied by " << r2 << " = " << r1*r2 << "\n";
    cout << r3 << " divided by " << r4 << " = " << r3/r4 << "\n";
    
    Rational ra(5,6);
    Rational rb(5,6);
    Rational rc(6,7);
    
    cout << ra << " is equal to " << rb << " : " << (ra==rb) << "\n";
    cout << ra << " is higher than " << rc << " : " << (ra>rc) << "\n";
    cout << ra << " is lower than " << rc << " : " << (ra<rc) << "\n";
    cout << ra << " can also be written as " << to_double(ra) << "\n";
    
    return 0;
}