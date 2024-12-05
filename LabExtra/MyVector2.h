#ifndef MyVector2_h
#define MyVector2_h

#include <iostream>
using namespace std;

template <typename T>

class MyVector2 {
    public:
        MyVector2 (void);
        MyVector2 (int s);
        
        T operator[](int index) const;
        T& operator[](int index);
        
        T safe_get (int i) const;
        void safe_set (int i, T value);
        
        //ESERCIZIO 2
        
        MyVector2 (const MyVector2& v);
        const double& at (int i) const; //lettura
        double& at (int i); //scrittura
        void push_back (double value);
        double pop_back (void);
        void reserve (int dim);
        
        ~MyVector2(void);
        
    private:
        int size {10};
        int real_size {0};
        double* elem = nullptr;
        void resize (int new_size);
};

#include "MyVector2.hpp"
#endif