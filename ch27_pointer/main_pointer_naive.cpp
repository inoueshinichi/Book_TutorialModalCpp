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

}

// std::bit_castの実装
template <class To, class From>
To bit_cast(const From& from) {
    // 値fromのバイト列をTo型の値として解釈して返す.
    To to;
    std::memcpy(&to, &from, sizeof(To));
    return to;
}


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
    // 
    return 0;
}
