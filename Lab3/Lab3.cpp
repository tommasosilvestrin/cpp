#include <iostream>
#include <vector>
using namespace std;

/* ESERCIZIO 1

void f () {
    int v [10];
    int* pv = &v[3];
    for (int i = -3; i < 7; i++) {
        pv[i] = 19;
        cout << pv[i] << "\n";
    }
}

void f_illegal () {
    int v [10];
    int* pv = &v[3];
    for (int i = 0; i < 10; i++) {
        pv[i] = 19;
        cout << pv[i] << "\n";
    }
}

int main () {
    f();
    f_illegal();
    return 0;
}

*/

/* ESERCIZIO 2

void print_array_length (double v [], int dim) {
    cout << "The size of the array is " << sizeof(v)*dim << "\n";
}

int main () {
    constexpr int dim = 7;
    double v [dim];
    cout << "The size of the array is " << sizeof(v) << "\n";
    
    double* pv = v;
    print_array_length (pv, dim);
    return 0;
}

*/

/* ESERCIZIO 3

void print_reference (int& x, double& y) {
    cout << "Passaggio per reference: int a = " << x << "; double b = " << y << "\n";
}
void print_pointer (int* x, double* y) {
    cout << "Passaggio per reference: int a = " << *x << "; double b = " << *y << "\n";
}

int main () {
    int a = 8;
    int* pa = &a;
    double b = 3.1456789;
    double* pb = &b;
    print_reference (a, b);
    print_pointer (pa, pb);
    return 0;
}

*/