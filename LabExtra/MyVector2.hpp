#ifndef MyVector2_hpp
#define MyVector2_hpp

#include "MyVector2.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>

MyVector2::MyVector2 (void) :
    elem { new T[10] }
{
    for (int i = 0; i < size; i++) elem[i] = 0;
}

MyVector2::MyVector2 (int s) :
    real_size {s}
{
    size = ((s/10)+1)*10;
    elem = new T [size];
    for (int i = 0; i < size; i++) elem[i] = 0;
}

T MyVector2::operator[](int index) const
{
    return elem[index]; //valore
}

T& MyVector2::operator[](int index)
{
    return elem[index]; //reference
}

T MyVector2::safe_get(int i) const
{
    if (i >= 0 && i < size) {
        return elem[i];
    }
    throw invalid_argument("index out of bound");
}

void MyVector2::safe_set(int i, T value)
{
    if (i >= 0 && i < size) {
        elem[i] = value;
    }
    else {
        throw invalid_argument("index out of bound");
    }
    if (i >= real_size) {
        real_size += (i + 1 - real_size);
    }
}

//ESERCIZIO 2

MyVector2::MyVector2 (const MyVector& v) : //costruttore di copia
    size{v.size}, real_size{v.real_size}, elem { new T [v.size] }
{
    copy (v.elem, v.elem+size, elem);
}

void MyVector2::resize (int new_size)
{
    T* elem_temp = new T [new_size];
    copy (elem, elem+size, elem_temp);
    delete[] elem;
    elem = elem_temp;
    for (int i = size; i < new_size; i++) {
        elem[i] = 0;
    }
    size = new_size;
}

const T& MyVector2:at (int i) const 
{
    if (i >= real_size || i < 0) throw out_of_range ("out of range");
    else return elem[i];
} // lettura

T& MyVector2::at (int i)
{
    if (i >= real_size || i < 0) throw out_of_range ("out of range");
    else return elem[i];
} // scrittura

void MyVector2::push_back (T value)
{
    if (real_size == size) resize (size*2);
    elem[real_size] = value;
    real_size++;
}

T MyVector2::pop_back (void)
{
    if (real_size != 0) return elem[--real_size];
    throw out_of_range ("out of range");
}

void MyVector2::reserve (int dim)
{
    if (dim > size) resize(dim);
}

MyVector2::~MyVector2 (void) {
    delete[] elem;
}

#endif