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
        void deallocate()
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

        // ヘルパー関数 (6)
        void destroy_all()
        {
            destroy_until(rend());
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

        // イテレータのペアを入力とするコンストラクタ
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            : vector(alloc)
        {
            // ストレージ確保
            reserve(std::distance(first, last));
            for (auto i = first; i != last; ++i)
            {
                push_back(*i); // *iでインスタンスを構築
            }
        }

        // std::initializer_list<T>を引数にとるコンストラクタ
        vector(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type())
            : vector(init.begin(), init.end(), alloc)
        {}

        // デストラクタ
        ~vector()
        {
            // 1. 要素を末尾から先頭に向かう順番で破棄
            clear();
            // 2. 生のメモリを解放する
            deallocate();
        }

        // コピー
        vector(const vector& other)
            // アロケータのコピー
            : alloc(traits::select_on_container_copy_construction(other.alloc))
        {
            // コピー処理
            // 1. コピー元の要素数を保持できるだけのストレージを確保
            reserve(other.size());
        
            // 2. コピー元の要素をコピー構築
            // dstはコピー先
            // [src, last)はコピー元
            for (auto dst = first, src = other.begin(), last = other.end();
                 src != last; ++dst, ++src)
            {
                construct(dst, *src);
            }
            last = first + other.size();
        }

        // アロケータのコピーは必要ない
        // 自分自身への対応が必要
        // コピー先とコピー元の要素数がおなじであるとは限らない.
        // コピー先とコピー元の要素数が同じであれば、単にコピー代入すればよい.
        vector& operator=(const vector& rhs)
        {
            // 1.自分自身への代入ならば何もしない
            // 2.要素数が同じならば要素ごとにコピー代入
            // 3.それ以外の場合で、予約数が十分ならば有効な要素にはコピー代入、残りはコピー構築
            // 4.それ以外の場合で、予約数が不十分ならば、現在の要素は全て破棄して新たなストレージを確保してコピー

            // 1.自分自身への代入ならば何もしない
            if (this == &rhs)
                return *this;
            
            // 2.要素数が同じならば要素ごとにコピー代入
            if (size() == rhs.size())
            {
                // 要素毎のコピー
                std::copy(rhs.begin(), rhs.end(), begin());
            }
            else
            {
                // 3.それ以外の場合で、予約数が十分ならば有効な要素にはコピー代入、残りはコピー構築
                if (capacity() >= rhs.size())
                {
                    // 以下のコードに対する疑問
                    // コピー先がコピー元より多くの要素を構築していたら
                    // コピー元外の要素はどのような扱いになるのか?
                    // コピー構築の際に元の要素ははされるのか？はては、コピー構築がエラーになるのか?
                    // destroy_until()が必要だと思う

                    // 有効外の要素を破棄
                    destroy_until(reverse_iterator(begin() + rhs.size()));
                    std::cout << "destroy_until" << std::endl;

                    // 有効な要素はコピー
                    std::copy(rhs.begin(), rhs.begin() + rhs.size(), begin());


                    // 残りはコピー構築
                    for (auto src_iter = rhs.begin() + rhs.size(), src_end = rhs.end();
                        src_iter != src_end; ++src_iter, ++last)
                    {
                        construct(last, *src_iter);
                    }
                }
                // 4.それ以外の場合で、予約数が不十分ならば、現在の要素は全て破棄して新たなストレージを確保してコピー
                else
                {
                    // 要素を全て破棄
                    destroy_all();
                    // 予約
                    reserve(rhs.size());
                    // コピー構築
                    for (auto src_iter = rhs.begin(), src_end = rhs.end();
                        src_iter != src_end; ++src_iter, ++last)
                    {
                        construct(last, *src_iter);
                    }
                }
            }

            return *this;
        }


        // reserveの実装
        // 生の動的メモリを確保して、データメンバを適切に設定する
        // 考慮すべき点がおおい
        void reserve(size_type sz)
        {
            // すでに指定された要素数以上に予約されているなら何もしない
            if (sz <= capacity())
                return;
            
            // 動的メモリを確保する
            auto ptr = allocate(sz);

            // 古いストレージの情報を保存
            auto old_first = first;
            auto old_last = last;
            auto old_capacity = capacity();

            // 新しいストレージに差し替え
            first = ptr;
            last = first;
            reserved_last = first + sz;

            // // 例外安全のため
            // // 関数を抜けるときに古いストレージを破棄する
            // std::scope_exit e([&] {
            //     traits::deallocate(alloc, old_first, old_capacity);
            // });

            // 古いストレージから新しいストレージに要素をコピー構築
            // 実際にはムーブ構築　
            for (auto old_iter = old_first; old_iter != old_last; ++old_iter, ++last)
            {
                // このコピーの理解にはムーブセマンティクスが必要
                construct(last, std::move(*old_iter));
            }

            // 新しいストレージにコピーし終えたので
            // 古いストレージの値は破棄
            for (auto riter = reverse_iterator(old_last), rend = reverse_iterator(old_first); 
                 riter != rend; ++riter)
            {
                destroy(&*riter);
            }
            // scope_exitによって自動的にストレージが破棄される.

            traits::deallocate(alloc, old_first, old_capacity);
        }


        void resize(size_type sz)
        {
            // 現在の要素数より少ない
            if (sz < size())
            {
                auto diff = size() - sz;
                destroy_until(rbegin() + diff);
            }
            // 現在の要素数より大きい
            else
            {
                reserve(sz);
                for (; last != reserved_last; ++last)
                {
                    construct(last); // デフォルト構築してる
                }
            }
        }


        void resize(size_type sz, const_reference value)
        {
            // 現在の要素数より少ない
            if (sz < size())
            {
                auto diff = size() - sz;
                destroy_until(rbegin() + diff);
            }
            // 現在の要素数より大きい
            else
            {
                reserve(sz);
                for (; last != reserved_last; ++last)
                {
                    construct(last, last); // 要素をvalueで初期化
                }
            }
        }

        // 要素アクセス
        void push_back(const T& x)
        {
            // よくある実装： 動的メモリ確保が必要になった場合、現在のストレージの2倍を確保する

            // 予約メモリが足りなければ拡張
            if (size() + 1 > capacity())
            {
                // 現在のストレージサイズ
                auto c = size();
                // 0の場合は1
                if (c == 0)
                    c = 1;
                else
                    // それ以外の場合は2倍する
                    c *= 2;

                reserve(c);
            }

            construct(last, x);
            ++last;
        }


        // shrink_to_fitは切り詰めるが、新しいストレージを確保する作業はある
        void shrink_to_fit()
        {
            // 何もする必要がない
            if (size() == capacity())
                return ;

            // 新しいストレージの確保
            auto ptr = allocate(size());
            // コピー
            auto current_size = size();
            for (auto raw_ptr = ptr, iter = begin(), iter_end = end();
                 iter != iter_end; ++iter, ++raw_ptr)
            {
                construct(raw_ptr, *iter); // *iterでインスタンスを構築
            }
            // 破棄
            clear();
            deallocate();
            // 新しいストレージを使う
            first = ptr;
            last = ptr + current_size;
            reserved_last = last;
        }
        

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