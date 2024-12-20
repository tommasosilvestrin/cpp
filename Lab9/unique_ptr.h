#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template<typename T>
class unique_ptr
{
    T* _ptr = nullptr;

    public:
        unique_ptr() = default;
        unique_ptr(T* ptr);

        ~unique_ptr();

        T operator*();
        T* operator->();

        T* release();

        unique_ptr(const unique_ptr<T>& ptr) = delete;
        unique_ptr& operator=(const unique_ptr<T>& ptr) = delete;
}

#include "unique_ptr.hpp"

#endif