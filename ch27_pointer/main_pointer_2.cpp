#include "../all.hpp"

namespace pointer_type {

    template <class T> using type = T;
    template <class T> using add_pointer_t = T*;
}

int main(int, char**)
{
    // 配列の型
    // 配列の型は、要素の型をT, 要素数をNとすると, T[N]となる.
    {
        // 要素型int, 要素数5の配列型
        using int5 = int[5];
        // 要素型double, 要素数10の配列型
        using double10 = double[10];

        // 配列型のポインタ
        using pointer_to_array_type = int(*)[5];

        int a[5];
        pointer_to_array_type ptr = &a;

        // エイリアス宣言を使わない場合の配列型のポインタ
        int (*arr_p)[5] = &a;

        // 配列名は配列の先頭要素へのポインターに暗黙的に変換される
        int* ap = a; // &a[0]と同じ
    }


    // ポインタ型の作り方
    {
        using function_type = int (int);
        using pointer_to_function_type = function_type*;

        // aはint
        pointer_type::type<int> a = 123;
        // bはdouble
        pointer_type::type<double> b = 1.23;
        // cはstd::vector<int>
        pointer_type::type<std::vector<int>> c = {1,2,3,4,5};
        
        // int
        using namespace pointer_type;

        // int
        type<type<int>> d = 0;
        // int
        type<type<type<int>>> e = 0;
        // std::vector<int>
        std::vector<type<int>> f = {1,2,3,4,5};
        // std::vector<int>
        type<std::vector<type<int>>> g = {1,2,3,4,5};

        // type<T>は型として使える. type<int>*はポインターとして機能する
        // int*
        type<int>* h = nullptr;
        // int (*)(int)
        type<int(int)>* i = nullptr;
        // int (*)[5]
        type<int [5]>* j = nullptr;
        // これで *を置く場所を悩まなくて済む

        // int *
        add_pointer_t<int> k = nullptr;
        // int**
        add_pointer_t<int*> l = nullptr;
        // int(*)(int)
        add_pointer_t<int(int)> m = nullptr;
        // int(*)[5]
        add_pointer_t<int [5]> n = nullptr;

        // int**
        add_pointer_t<add_pointer_t<int>> o = nullptr;

        // std::add_pointer_tはリファレンスを渡してもいエラーにならない
        std::add_pointer_t<int&> p = nullptr;

        // int
        std::remove_pointer_t<int *> q = 0;
    }

    // クラスへのポインター
    {
        
    }
}

