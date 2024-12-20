#include "unique_ptr.h"

template<typename T>
unique_ptr<T>::unique_ptr (T* ptr)
{
    _ptr = ptr;
}

template<typename T>
T unique_ptr<T>::operator* ()
{
    return *_ptr;
}

template<typename T>
unique_ptr<T>::~unique_ptr ()
{
    delete _ptr;
    _ptr = nullptr;
}

template<typename T>
T* unique_ptr<T>::release ()
{
    T* ptr = _ptr
    _ptr = nullptr;
    return ptr;
}

template<typename T>

T* unique_ptr<T>::operator-> ()
{
    return _ptr;
}