#include <iostream>
using namespace std;

class Rational {
    public:
        Rational (void);
        Rational (int n);
        Rational (int n, int d);
        
        Rational& operator=(const Rational& r);
        Rational& operator=(int n);
        
        int num(void) const;
        int den(void) const;
        
    private:
        int numerator {0};
        int denominator {1};
};

Rational operator+(const Rational& r, const Rational& p);
Rational operator+(const Rational& r, int n);

Rational operator-(const Rational& r, const Rational& p);
Rational operator-(const Rational& r, int n);

Rational operator*(const Rational& r, const Rational& p);
Rational operator*(const Rational& r, int n);

Rational operator/(const Rational& r, const Rational& p);
Rational operator/(const Rational& r, int n);

bool operator==(const Rational& r, const Rational& p);
bool operator==(const Rational& r, int n);

bool operator>(const Rational& r, const Rational& p);
bool operator>(const Rational& r, int n);

bool operator<(const Rational& r, const Rational& p);
bool operator<(const Rational& r, int n);

ostream& operator<<(ostream& out, const Rational& r);

double to_double(const Rational& r);