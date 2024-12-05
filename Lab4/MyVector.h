#include <iostream>
using namespace std;

class MyVector {
    public:
        MyVector (void);
        MyVector (int s);
        
        double operator[](int index) const;
        double& operator[](int index);
        
        double safe_get (int i) const;
        void safe_set (int i, double value);
        
        //ESERCIZIO 2
        
        MyVector (const MyVector& v);
        const double& at (int i) const; //lettura
        double& at (int i); //scrittura
        void push_back (double value);
        double pop_back (void);
        void reserve (int dim);
        
        ~MyVector(void);
        
    private:
        int size {10};
        int real_size {0};
        double* elem = nullptr;
        void resize (int new_size);
};