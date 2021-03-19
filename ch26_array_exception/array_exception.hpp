#pragma once

#include <iostream>

//////////////////////
// array_iteratorクラス
//////////////////////
template <class Array>
struct array_iterator {

    Array& a;
    std::size_t i;

    array_iterator(Array& a, std::size_t i) 
        : a(a)
        , i(i) {}

    array_iterator(const array_iterator&) = default; // コピーコンストラクタ

    // 次の要素を指す
    array_iterator& operator++() {
        ++i;
        return *this;
    }

    array_iterator operator++(int) {
        array_iterator copy = *this; // array_iteratorにはコピーコンストラクタが必要
        ++*this; // operator++() 前置インクルメント
        return copy;
    }

    array_iterator& operator+=(std::size_t n) {
        i += n;
        return *this;
    }

    array_iterator& operator+(std::size_t n) const {
        // operator+はオペランドの値を変更しないので、constにできる.
        auto copy = *this;
        copy += n;
        return copy;
    }

    // 前の要素を指す
    array_iterator& operator--() {
        --i;
        return *this;
    }

    array_iterator operator--(int) {
        array_iterator copy = *this;
        --*this; // operator--() 前置デクリメント
        return copy;
    }

    array_iterator& operator-=(std::size_t n) {
        i -= n;
        return *this;
    }

    array_iterator operator-(std::size_t n) const {
        auto copy = *this;
        copy -= n;
        return copy;
    }

    // 現在、参照している要素へのリファレンスを返す
    typename Array::reference operator*() {
        return a[i];
    }

    typename Array::reference operator[](std::size_t n) const {
        return *(*this + n); // a[i+n]
    }

    // 比較演算子
    bool operator==(const array_iterator& rhs) {
        return (i == rhs.i);
    }

    bool operator!=(const array_iterator& rhs) {
        return !(*this == rhs);
    }

    bool operator<(const array_iterator& rhs) {
        return (i < rhs.i);
    }

    bool operator>=(const array_iterator& rhs) {
        return !(*this < rhs);
    }

    bool operator>(const array_iterator& rhs) {
        return (rhs < *this); // *this < rhsの逆
    }

    bool operator<=(const array_iterator& rhs) {
        return !(*this > rhs);
    }
};


//////////////////////
// const_iteratorクラス
//////////////////////
// const iteratorではダメな理由 -> const iteratorは値を変更できないから.
// イテレータクラス自身は書き換えできて、中身のコンテナは変更できないようにしたい. -> const_iteratorが必要!
template <class Array>
struct array_const_iterator {

    const Array& a;
    std::size_t i;

    array_const_iterator(const Array& a, std::size_t i)
        : a(a)
        , i(i) {}
    
    // iteratorからconst_iteratorに変換するコンストラクタ
    array_const_iterator(const typename array_iterator<Array>::iterator& iter)
        : a(iter.a)
        , i(iter.i) {}
    
    array_const_iterator(const array_const_iterator&) = default; // コピーコンストラクタ

    ///////////////////////////////////////////////////
    // インデクシング、アクセス、比較用関数はiterotorと殆ど同じ
    ///////////////////////////////////////////////////
    // 次の要素を指す
    array_const_iterator& operator++() {
        ++i;
        return *this;
    }

    array_const_iterator operator++(int) {
        array_iterator copy = *this; // array_iteratorにはコピーコンストラクタが必要
        ++*this; // operator++() 前置インクルメント
        return copy;
    }

    array_const_iterator& operator+=(std::size_t n) {
        i += n;
        return *this;
    }

    array_const_iterator& operator+(std::size_t n) const {
        // operator+はオペランドの値を変更しないので、constにできる.
        auto copy = *this;
        copy += n;
        return copy;
    }

    // 前の要素を指す
    array_const_iterator& operator--() {
        --i;
        return *this;
    }

    array_const_iterator operator--(int) {
        array_iterator copy = *this;
        --*this; // operator--() 前置デクリメント
        return copy;
    }

    array_const_iterator& operator-=(std::size_t n) {
        i -= n;
        return *this;
    }

    array_const_iterator operator-(std::size_t n) const {
        auto copy = *this;
        copy -= n;
        return copy;
    }

    // 現在、参照している要素へのリファレンスを返す
    typename Array::const_reference operator*() {
        return a[i];
    }

    typename Array::const_reference operator[](std::size_t n) const {
        return *(*this + n); // a[i+n]
    }

    // 比較演算子
    bool operator==(const array_const_iterator& rhs) {
        return (i == rhs.i);
    }

    bool operator!=(const array_const_iterator& rhs) {
        return !(*this == rhs);
    }

    bool operator<(const array_const_iterator& rhs) {
        return (i < rhs.i);
    }

    bool operator>=(const array_const_iterator& rhs) {
        return !(*this < rhs);
    }

    bool operator>(const array_const_iterator& rhs) {
        return (rhs < *this); // *this < rhsの逆
    }

    bool operator<=(const array_const_iterator& rhs) {
        return !(*this > rhs);
    }
};


//////////////////
// 自作のarrayクラス
//////////////////
template <class T, std::size_t N>
struct array {
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

    // using iterator = array_iterator_begin<array>; // ここのarrayはarray<T, N>と同じ意味.
    using iterator = array_iterator<array>;
    using const_iterator = array_const_iterator<array>;
    value_type storage[N];


    iterator begin() {
        return iterator(*this, 0); // 自分自身を参照として格納したイテレータを返す.
    }
    iterator end() {
        return iterator(*this, N);
    }

    // const arrayのときにconst_iteratorを返す
    const_iterator begin() const {
        return const_iterator(*this, 0);
    }
    const_iterator end() const {
        return const_iterator(*this, N);
    }

    // 常にconst_iteratorを返す
    const_iterator cbegin() const {
        return const_iterator(*this, 0);
    }
    const_iterator cend() const {
        return const_iterator(*this, N);
    }

    // 非const
    reference operator[](size_type i) {
        return storage[i];
    }

    // const
    const_reference operator[](std::size_t i) const {
        return storage[i];
    }

    // at
    reference at(std::size_t i) {
        if (i >= size()) {
            throw std::out_of_range("Error: Out of Range.");
        }

        return storage[i];
    }

    // const at
    const_reference at(std::size_t i) const {
        if (i >= size()) {
            throw std::out_of_range("Error: Out of Range.");
        }

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