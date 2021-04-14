#pragma once
#include "../all.hpp"

namespace example
{
    template <class T, class Allocator = std::allocator<T>>
    class vector
    {
    private:
        // データメンバー
    public:

        // value_typeなどネストされた型名
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const pointer;
        using reference = value_type&;
        using const_reference = const value_type&;

        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t; // イテレータの距離

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // 先頭の要素へのポインタ
        pointer first;
        // 最後の要素の1つ前方のポインタ
        pointer last;
        // 確保したストレージの終端
        pointer reseved_last;
        // アロケータの値
        allocator_type alloc;

        // コンストラクタ
        vector(std::size_t n = 0, Allocator a = Allocator());
        // デストラクタ
        ~vector();
        // コピー
        vector(const vector& x);
        vector& operator=(const vector& x);

        // 要素アクセス
        void push_back(const T& x);
        T& operator [](std::size_t i) noexcept;

        // イテレータアクセス
        iterator begin() noexcept
        { return first; }
        iterator end() noexcept
        { return last; }

        const_iterator begin() const noexcept
        { return first; }
        const_iterator end() const noexcept
        { return last; }

        const_iterator cbegin() const noexcept
        { return first; }
        const_iterator cend() const noexcept
        { return last; }

        reverse_iterator rbegin() noexcept
        { return reverse_iterator{last}; }
        reverse_iterator rend() noexcept
        { return reverse_iterator{first}; }

        size_type size() const noexcept
        { return end() - begin(); }

        bool empty() const noexcept
        { return size() == 0; }

        size_type capacity() const noexcept
        { return reseved_last - first; }

        reference operator[](size_type i)
        { return first[i]; }
        const_reference operator[](size_type i) const
        { return first[i]; }

        reference at(size_type i)
        {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            
            return first[i];
        }
        const_reference at(size_type i) const
        {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            
            return first[i];
        }

        reference front()
        { return first; }
        const_reference front() const
        { return first; }
        reference back()
        { return last - 1; }
        const_reference back()
        { return last - 1; }

        pointer data() noexcept
        { return first; }
        const_pointer data() const noexcept
        { return first; }

        
    };


    void f1(std::vector<int>& v)
    {
        std::vector<int>::size_type s = v.size();
    }

    void f2(std::vector<int>& v)
    {
        auto i = v.begin();
        auto j = i + 3;

        // iとjの距離
        std::vector<int>::difference_type d = j - i;
    }


}

