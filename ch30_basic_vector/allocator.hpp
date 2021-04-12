#pragma once
#include "../all.hpp"

namespace example
{
    // 独自のアロケーター
    template <class T>
    struct custom_allocator
    {
        // ...
    };

    template <class T>
    using custom_vector = std::vector<T, custom_allocator<T>>;


    /**
     * @brief std::allocator<T>の概要
     * T型を構築できる生のメモリを確保するために以下のようになっている。
     */
    template <class T>
    class allocator
    {
        // ネストされた型名の宣言
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using propagate_on_container_move_assignment = std::true_type;
        using is_always_equal = std::true_type;

        // コンストラクタ
        constexpr allocator() noexcept;
        constexpr allocator(const allocator&) noexcept;
        template <class U> constexpr allocator(const allocator<U>&) noexcept;
        ~allocator();
        // コピー代入演算子
        allocator& operator=(const allocator&) = default;

        // ここが重要
        [[nodiscard]] T* allocate(size_t n);
        void deallocate(T* p, size_t n);
    };

    

}