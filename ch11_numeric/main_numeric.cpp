#include <iostream>
#include <cstdio>
#include <algorithm> // std::clamp

#include "../all.hpp"

int main(int, char**)
{
    std::cout << "Hello, neumeric!\n";

    // 8進数リテラル (10進数で83)
    int octal = 0123;
    std::printf("0%o: %d\n", octal, octal);

    // 16進数リテラル(10進数で291)
    int hexadecimal = 0x123;
    std::printf("0x%x: %d\n", hexadecimal, hexadecimal);

    // 数値区切り
    int a = 100'000'000;
    std::printf("%d\n", a);
    int b = 0xff'20'4d;
    std::printf("%x: %d\n", b);

    // 1バイトで表現された整数
    auto zero = 0b00000000;
    auto max = 0b11111111;
    std::printf("0b00000000: %d\n", zero);
    std::printf("0b11111111: %d\n", max);

    // 整数
    auto c = 123u; // unsigned int
    auto d = 123l; // long
    auto e = 123ul; // unsigned long
    auto f = 123ll; // long long
    auto g = 123ull; // unsigned long long
    auto h = 'A'; // char型, singed char型 と char型は異なる

    // 整数のサイズ
#define GET_SIZE(TYPE)                                   \
    std::printf("sizeof(%s): %ud\n", #TYPE, sizeof(TYPE))

    using schar = signed char;
    using uchar = unsigned char;
    using ushort = unsigned short;
    using uint = unsigned int;
    using ulong = unsigned long;
    using longlong = long long;
    using ulonglong = unsigned long long;
    using longdouble = long double;

    GET_SIZE(char);
    GET_SIZE(schar);
    GET_SIZE(uchar);
    GET_SIZE(short);
    GET_SIZE(ushort);
    GET_SIZE(int);
    GET_SIZE(uint);
    GET_SIZE(long);
    GET_SIZE(ulong);
    GET_SIZE(longlong);
    GET_SIZE(ulonglong);
    GET_SIZE(size_t);
    GET_SIZE(float);
    GET_SIZE(double);
    GET_SIZE(longdouble);

#define NUMERIC_RANGE(TYPE)                                                                    \
    std::cout << "max of " << #TYPE << ": " << std::numeric_limits<TYPE>::min() << std::endl;  \
    std::cout << "min of " << #TYPE << ": " << std::numeric_limits<TYPE>::max() << std::endl
    
    // 整数型で表現できる値の範囲
    NUMERIC_RANGE(char);
    NUMERIC_RANGE(schar);
    NUMERIC_RANGE(uchar);
    NUMERIC_RANGE(short);
    NUMERIC_RANGE(ushort);
    NUMERIC_RANGE(int);
    NUMERIC_RANGE(uint);
    NUMERIC_RANGE(long);
    NUMERIC_RANGE(ulong);
    NUMERIC_RANGE(longlong);
    NUMERIC_RANGE(ulonglong);
    NUMERIC_RANGE(size_t);
    NUMERIC_RANGE(float);
    NUMERIC_RANGE(double);
    NUMERIC_RANGE(longdouble);

    // 符号なし整数型の最小値 - 1 = 最大値
    // 符号なし整数型の最大値 + 1 = 最小値
#define MUMERIC_BEYOND_MAX_MIN(TYPE)                                                                 \
    NUMERIC_RANGE(TYPE);                                                                             \
    TYPE min_minus_one_##TYPE = std::numeric_limits<TYPE>::min() - 1u;                               \
    TYPE max_plus_one_##TYPE = std::numeric_limits<TYPE>::max() + 1u;                                \
    std::cout << "min - 1 of " << #TYPE << ": " << min_minus_one_##TYPE << std::endl;                \
    std::cout << "max + 1 of " << #TYPE << ": " << max_plus_one_##TYPE << std::endl
    MUMERIC_BEYOND_MAX_MIN(char);
    MUMERIC_BEYOND_MAX_MIN(schar);
    MUMERIC_BEYOND_MAX_MIN(uchar);
    MUMERIC_BEYOND_MAX_MIN(short);
    MUMERIC_BEYOND_MAX_MIN(ushort);
    MUMERIC_BEYOND_MAX_MIN(int);
    MUMERIC_BEYOND_MAX_MIN(uint);
    MUMERIC_BEYOND_MAX_MIN(long);
    MUMERIC_BEYOND_MAX_MIN(ulong);
    MUMERIC_BEYOND_MAX_MIN(longlong);
    MUMERIC_BEYOND_MAX_MIN(ulonglong);
    MUMERIC_BEYOND_MAX_MIN(size_t);
    MUMERIC_BEYOND_MAX_MIN(float);
    MUMERIC_BEYOND_MAX_MIN(double);
    MUMERIC_BEYOND_MAX_MIN(longdouble);
}
