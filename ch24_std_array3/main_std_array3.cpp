#include "../all.hpp"

#include "std_array3.hpp"

int main(int,char**)
{
    // ネストされた型名を使う
    {
        using array_type = std::array<int, 5>;
        array_type a = {1,2,3,4,5};
        array_type::value_type x = 0;
        array_type::reference ref = a[0];
    }

    // メンバ関数のconst修飾
    {
        std::array<int, 5> a = {1,2,3,4,5};
        print(a);
    }

    // 自作のarrayクラス
    {
        array<int, 5> a = {1,2,3,4,5};

        // print(a); // エラー
    }

    // constな自作arrayクラス
    {
        const std::array<int, 5> ca = {1,2,3,4,5};
        print(ca);
    }

    // 先頭と末尾の要素:front/back
    {
        std::array<int, 5> a = {1,2,3,4,5};

        int& f = a.front(); // 1
        int& b = a.back();  // 5
    }

    // 全要素に値を代入:fill
    {
        std::array<int, 5> a = {1,2,3,4,5};
        a.fill(0);
        // aは{0,0,0,0,0}
        print(a);
    }

}