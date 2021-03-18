#pragma once
#include "../all.hpp"

template <class T, std::size_t N>
struct array {
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

    value_type storage[N];

    // 非const
    reference operator[](size_type i) {
        return storage[i];
    }

    // const
    const_reference operator[](std::size_t i) const {
        return storage[i];
    }

    size_type size() const {
        return N;
    }

    // front
    reference front() {
        return storage[0];
    }
    const_reference front() const {
        return storage[0];
    }

    // back
    reference back() {
        return storage[N-1];
    }
    const_reference back() const {
        return storage[N-1];
    }

    // fill
    void fill(const T& u) {
        std::fill(std::begin(storage), std::end(storage), u);
        // std::fill(this->begin(), this->end(), u);
    }
};

template <class Array>
void print(Array& c) {
    for (std::size_t i = 0; i != c.size(); ++i) {
        std::cout << c[i];
    }
    std::cout << std::endl;
}