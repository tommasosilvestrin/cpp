#include "MyVector.h"
#include <iostream>
#include <stdexcept>
using namespace std;

MyVector::MyVector (void) :
    elem { new double[10] }
{
    for (int i = 0; i < size; i++) elem[i] = 0;
}

MyVector::MyVector (int s) :
    real_size {s}
{
    size = ((s/10)+1)*10;
    elem = new double [size];
    for (int i = 0; i < size; i++) elem[i] = 0;
}

double MyVector::operator[](int index) const
{
    return elem[index]; //valore
}

double& MyVector::operator[](int index)
{
    return elem[index]; //reference
}

double MyVector::safe_get(int i) const
{
    if (i >= 0 && i < size) {
        return elem[i];
    }
    throw invalid_argument("index out of bound");
}

void MyVector::safe_set(int i, double value)
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

MyVector::MyVector (const MyVector& v) : //costruttore di copia
    size{v.size}, real_size{v.real_size}, elem { new double [v.size] }
{
    copy (v.elem, v.elem+size, elem);
}

void MyVector::resize (int new_size)
{
    double* elem_temp = new double [new_size];
    copy (elem, elem+size, elem_temp);
    delete[] elem;
    elem = elem_temp;
    for (int i = size; i < new_size; i++) {
        elem[i] = 0;
    }
    size = new_size;
}

const double& MyVector::at (int i) const 
{
    if (i >= real_size || i < 0) throw out_of_range ("out of range");
    else return elem[i];
} // lettura

double& MyVector::at (int i)
{
    if (i >= real_size || i < 0) throw out_of_range ("out of range");
    else return elem[i];
} // scrittura

void MyVector::push_back (double value)
{
    if (real_size == size) resize (size*2);
    elem[real_size] = value;
    real_size++;
}

double MyVector::pop_back (void)
{
    if (real_size != 0) return elem[--real_size];
    throw out_of_range ("out of range");
}

void MyVector::reserve (int dim)
{
    if (dim > size) resize(dim);
}

MyVector::~MyVector (void) {
    delete[] elem;
}