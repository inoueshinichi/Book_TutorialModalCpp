/**
 * @file main_pointer_naive.cpp
 * @author your name (you@domain.com)
 * @brief ポインターの内部実装
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../all.hpp"

#define ToStr(T) #T

template <class T>
void print_size()
{
    std::printf("sizeof(%s): %lu\n", ToStr(T), sizeof(T));
}

// std::memcpyの実装
void* memcpy(void* dst, const void* src, size_t n) {
    // srcの先頭バイトからnバイトを
    // dstの先頭バイトからのバイト列にコピーし
    // dstを返す.

    // dstをstd::byte*型に変換
    auto d = static_cast<std::byte*>(dst);
    // srcをconst std::byte*型に変換
    auto s = static_cast<const std::byte*>(src);

    // srcからnバイトコピーするのでnバイト先のアドレスを得る
    auto last = s + n;

    // nバイトコピーする
    while (s != last) {
        *d = *s;
        ++s;
        ++d;
    }

    // dstを返す
    return dst;
}

// std::bit_castの実装
template <class To, class From>
To bit_cast(const From& from) {
    // 値fromのバイト列をTo型の値として解釈して返す.
    To to;
    // std::memcpy(&to, &from, sizeof(To));
    memcpy(&to, &from, sizeof(To));
    return to;
}

// 生のアドレスを出力する関数
template <class T>
void print_raw_address(T ptr) {
    std::cout << bit_cast<std::uintptr_t>(ptr) << std::endl;
}

struct S {
    int x = 123;
};

struct Object {
    int x {123};
    int y {456};
    int z {789};
};

int main(int, char**)
{
    // ポインターのサイズ
    {
        print_size<int*>();
        print_size<double*>();
        print_size<int**>();
    }

    // ポインターの値
    {
        // std::uintptr_t: すべてのポインター値を格納できるサイズの符号なし整数
        std::cout << "sizeof(std::uintptr_t): " << sizeof(std::uintptr_t) << std::endl;

        // std::bit_cast<to>(from): ある値fromのバイト列を同じバイト数のある型toの値として強引に解釈する. from C++20
        int data {};
        std::cout << bit_cast<std::uintptr_t>(&data) << std::endl;
    }

    // void*
    {
        // ある型Tへのポインター型はvoid*型に変換できる.
        int data{};
        void* ptr = &data;

        // void*型の値eから元の型Tへのポインターに変換するにはstatic_cast<T*>(e)が必要.
        int* int_ptr = static_cast<int*>(ptr);
        // もしstatic_cast<T*>(e)のeがT*として妥当なアドレスの値であれば、変換後も正しく動く.

        // const T*型は, const void*型に変換できる.
        // その逆も可能.
        // ポインター間の変換でconstの有無を変更することはできない.
        int data2 {};
        const int* c_int_ptr = &data2;
        const void* c_void_ptr = c_int_ptr;
        const int* original = static_cast<const int*>(c_void_ptr);
    }

    // std::memcpyはvoid*を使うことで、どんなポインターの値でも取れるようにしている.
    // C++にはテンプレートがあるので、以下のように宣言してもよいが、C言語ライブラリなのでvoid*をつかっている.
    // template <class Dst, class Src>
    // Dst* memcpy(Dst* dst, const Src* src, std::size_t n);

    // std::byte型
    {
        // // エラー
        // std::byte a = 123;
        // std::byte a(123);
        // a = 123;

        std::byte a{123};
        std::byte b;
        b = std::byte{180};
        

        // static_cast<std::byte>(x)やstd::byte(x)はコンパイルはできるが、使ってはならない.
        // 使ってはならない. 範囲外の値を無理やり変換するので、未定義動作になる
        // std::byte a = static_cast<std::byte>(256);
        // std::byte b = std::byte(-1);
    }

    // 配列のメモリー上での表現
    {
        int array[3] = {0,1,2};
        print_raw_address(&array[0]);
        print_raw_address(&array[1]);
        print_raw_address(&array[2]);
    }

    // ポインターと整数の演算
    {
        std::cout << "ポインターと整数の演算" << std::endl;
        int a[4] = {0,1,2,3};

        // 0個目の要素へのポインター
        int* a0 =&a[0];
        print_raw_address(a0);

        // アドレスがsizeof(int) * 3が加算される
        // a3は3個目の要素へのポインター
        int* a3 = a0 + 3;
        print_raw_address(a3);

        // アドレスがsizeof(int) * 2が減算される
        // a1は1個目の要素へのポインター
        int* a1 = a3 - 2;
        print_raw_address(a1);
    }

    // データメンバーへのポインターの内部実装
    // データメンバーへのポインターは、具体的なクラスのオブジェクトへのポインターやリファレンス
    // があって初めて意味がある.
    // データメンバーへのポインターとは、クラスのオブジェクトを表現するバイト列の先頭から何バイト目に配置されているかというオフセット値になっている.
    {
        int data = 123;
        int* ptr = &data;
        // ptr単体で参照できる
        int read1 = *ptr;

        S object;
        int S::* mem_ptr = &S::x;
        print_raw_address(mem_ptr); // 常にゼロを返す(nullptr)
        int read2 = object.*mem_ptr;
        // print_raw_address(object.mem_ptr);

        // メンバーポインタに入れる前のデータメンバーのアドレスを確認
        print_raw_address(&Object::x); 
        print_raw_address(&Object::y);
        print_raw_address(&Object::z);

        // クラスのオブジェクトの先頭アドレス
        Object obj;
        std::byte* start = bit_cast<std::byte*>(&obj);
        // オフセット 0
        int* x = bit_cast<int*>(start + bit_cast<std::uintptr_t>(&Object::x)); // ポインタ(アドレス)を符号なし整数std::uintptr_tに変換してから演算
        std::cout << *x << std::endl;
        int* y = bit_cast<int*>(start + bit_cast<std::uintptr_t>(&Object::y));
        std::cout << *y << std::endl;
        int* z = bit_cast<int*>(start + bit_cast<std::uintptr_t>(&Object::z));
        std::cout << *z << std::endl;
    }

    return 0;
}
