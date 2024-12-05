#include "Rational.h"
#include <algorithm>
#include <iostream>
using namespace std;

Rational::Rational(void) {};

Rational::Rational(int n) :
    numerator{n}
{}

Rational::Rational(int n, int d) :
    numerator{n},
    denominator{d}
{}

Rational& Rational::operator=(const Rational& r) {
    numerator = r.num();
    denominator = r.den();
    return *this;
}

Rational& Rational::operator=(int n) {
    numerator = n;
    denominator = 1;
    return *this;
}

int Rational::num(void) const {
    return numerator;
}

int Rational::den(void) const {
    return denominator;
}

Rational operator+(const Rational& r, const Rational& p) {
    int tnum = (r.num()*p.den()) + (r.den()*p.num());
    int tden = r.den()*p.den();
    // tnum /= __gcd(tnum, tden);
    // tden /= __gcd(tnum, tden);
    return Rational(tnum, tden);
}

Rational operator+(const Rational& r, int n) {
    int tnum = n*r.den() + r.num();
    int tden = r.den();
    // tnum /= __gcd(tnum, tden);
    // tden /= __gcd(tnum, tden);
    return Rational(tnum, tden);
}

Rational operator-(const Rational& r, const Rational& p) {
    int tnum = (r.num()*p.den()) - (r.den()*p.num());
    int tden = r.den()*p.den();
    // tnum /= __gcd(tnum, tden);
    // tden /= __gcd(tnum, tden);
    return Rational(tnum, tden);
}

Rational operator-(const Rational& r, int n) {
    int tnum = r.num() - n*r.den();
    int tden = r.den();
    // tnum /= __gcd(tnum, tden);
    // tden /= __gcd(tnum, tden);
    return Rational(tnum, tden);
}

Rational operator*(const Rational& r, const Rational& p) {
    int tnum = r.num()*p.num();
    int tden = r.den()*p.den();
    return Rational(tnum, tden);
}

Rational operator*(const Rational& r, int n) {
    int tnum = r.num()*n;
    int tden = r.den();
    return Rational(tnum, tden);
}

Rational operator/(const Rational& r, const Rational& p) {
    int tnum = r.num()*p.den();
    int tden = r.den()*p.num();
    return Rational(tnum, tden);
}

Rational operator/(const Rational& r, int n) {
    int tnum = r.num();
    int tden = r.den()*n;
    return Rational(tnum, tden);
}

bool operator==(const Rational& r, const Rational& p) {
    double dr = (double)(r.num()/r.den());
    double dp = (double)(p.num()/p.den());
    return dr==dp;
}

bool operator==(const Rational& r, int n) {
    return (r.num()%r.den()==0) && (r.num()/r.den()==n);
}

bool operator>(const Rational& r, const Rational& p) {
    return (r.num()*p.den())>(p.num()*r.den());
}

bool operator>(const Rational& r, int n) {
    return r.num()>(n*r.den());
}

bool operator<(const Rational& r, const Rational& p) {
    return (r.num()*p.den())<(p.num()*r.den());
}

bool operator<(const Rational& r, int n) {
    return r.num()<(n*r.den());
}

ostream& operator<<(ostream& out, const Rational& r) {
    return out << r.num() << "/" << r.den();
}

double to_double(const Rational& r) {
    return ((double)r.num()/r.den());
}