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
        pointer reserved_last;
        // アロケータの値
        allocator_type alloc;

    private:
        using traits = std::allocator_traits<allocator_type>;

        // ヘルパー関数 (1)
        pointer allocate(size_type n)
        { return traits::allocate(alloc, n); }

        // ヘルパー関数 (2)
        void delallocate()
        { traits::deallocate(alloc, first, capacity()); }
         
        // ヘルパー関数 (3)
        void construct(pointer ptr)
        { traits::construct(alloc, ptr); }
        void construct(pointer ptr, const_reference value) 
        { traits::construct(alloc, ptr, value); }
        // ムーブ用
        void construct(pointer ptr, value_type&& value)
        { traits::construct(alloc, ptr, std::move(value)); }

        // ヘルパー関数 (4)
        void destroy(pointer ptr)
        { traits::destroy(alloc, ptr); }

        // ヘルパー関数 (5)
        void destroy_until(reverse_iterator rend)
        { 
            for (auto riter = rbegin(); riter != rend; ++riter, --last)
            {
                destroy(&*riter); // riterはポインタ(T*).
            }
        }
    public:

        // コンストラクタ (1)
        vector(size_type size, const allocator_type& alloc = allocator_type())
            : vector(alloc)
        {
            resize(size);
        }

        // コンストラクタ (2)
        vector(size_type size, const_reference value, const allocator_type& alloc)
            : vector(alloc)
        {
            resize(size, value);
        }

        // Allocatorを取るコンストラクタ(デリゲートされるコンストラクタ)
        vector(const allocator_type& alloc) noexcept
            : alloc(alloc)
        {}

        // デフォルトコンストラクタ
        vector()
            : vector(allocator_type())
        {}

        // デストラクタ
        ~vector()
        {
            // 1. 要素を末尾から先頭に向かう順番では気
            clear();
            // 2. 生のメモリを解放する
            deallocate();
        }

        // コピー
        vector(const vector& x);
        vector& operator=(const vector& x);

        // 要素アクセス
        void push_back(const T& x);
        // T& operator [](std::size_t i) noexcept;

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
        { return reserved_last - first; }

        void clear() noexcept
        { destroy_until(rend()); }

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
        const_reference back() const 
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