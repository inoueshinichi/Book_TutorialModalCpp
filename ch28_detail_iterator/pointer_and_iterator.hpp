#pragma once
#include "../all.hpp"

namespace example {

    // ポインター型のイテレータ
    template <class Array>
    struct array_iterator 
    {
        using pointer = typename Array::pointer;
        using referece = typename Array::reference;
        pointer p;

        array_iterator(pointer p)
            : p(p) {}
        
        referece operator*() {
            return *p;
        }

        array_iterator& operator++() {
            ++p;
            return *this;
        }

        referece operator[](std::size_t n) {
            return p[n];
        }
    };

    // ポインター型のArrayクラス
    template <class T, std::size_t N>
    struct array
    {
        T storage[N];

        // ポインター
        using iterator = T*;
        using reference = T&;
        using pointer = iterator;

        iterator begin() {
            return &storage[0];
        }

        iterator end() {
            return begin() + N; // ここポインタの足し算.
        }
    };
}