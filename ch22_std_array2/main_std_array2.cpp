#include "../all.hpp"

// #include "std_array2.hpp"


struct array_int_3 { 
    int storage[3];

    array_int_3(const array_int_3& other) {
        std::copy(std::begin(other.storage), std::end(other.storage), std::begin(storage));
    }
};
struct array_int_10 { 
    int storage[10]; 

    int& operator[](std::size_t i) {
        return storage[i];
    }
};


int main(int, char**)
{
    // 配列のサイズ
    {
        auto print = [](auto s) { std::cout << s << "\n"s; };

        int a[5];
        print(sizeof(a));
        print(sizeof(int) * 5);

        double b[5];
        print(sizeof(b));
        print(sizeof(double) * 5);
    }

    // sizeofは型やオブジェクトのバイト数を取得するのに対し、vectorやarrayの
    // メンバ関数size()は要素数を取得する.
    {
        auto print = [](auto s) { std::cout << s << "\n"s; };

        std::array<int, 5> a;

        // aのバイト数
        print(sizeof(a));
        // 要素数:5
        print(a.size());
    }

    // 配列はコピーできない、std::arrayはコピーできる
    {
        int a[5] = {1,2,3,4,5};
        // エラー、コピーできない
        // int b[5] = a;

        std::array<int, 5> c = {1,2,3,4,5};
        // OK, コピーできる
        std::array<int, 5> d = c;
    }

    // 配列はコピーできないが、クラスのデータメンバとしてえ宣言した配列は、
    // クラスコピーの際に、その対応する順番の要素がそれぞれコピーされる.
    {
        // array_int_3 a = {1,2,3};
        // array_int_10 b = a;
        // b.storage[0] == a.storage[0]
        // b.storage[1] == a.storage[1]
        // b.storage[2] == a.storage[2]
    }
}