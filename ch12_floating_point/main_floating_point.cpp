#include "../all.hpp"

int main(int, char**) {

    // 情報落ち
    float a = 10000.0; // 1万
    float b = 0.0001; // 1万分の1
    float c = a + b;
    std::cout << a << "\n"s << b << "\n"s << c << std::endl;

    // float
    auto d = 123.456f; // float
    auto e = 123.456;  // double
    auto f = 123.456l; // long double

    // 値はすべて123.456
    auto g = 1.23456e2;
    auto h = 123456e-3;
    auto i = 123.456e0;
    auto j = 123.456E0;

    // 16進数の仮数と指数
    double k = 0xabc.0p0; // 5496
    double l = 0xde.fP5;  // 7134

    // 浮動小数点数の国際標準規格 ISO/IEC/IEEE 60559:2011
    // これは、米国電気電子学会の規格IEEE 754-2008と同じ
    // この中身は, Intelが立案した規格IEEE 754-1985.
    // 通称、IEEE-754

    // +0.0/-0.0の2種類がある
    std::cout << 0.0 << "\n"s << -0.0 << std::endl;

    // 値を比較すると同じものとみなされる
    double m = +0.0;
    double n = -0.0;
    bool o = m == n;
    std::cout << std::boolalpha << "+0.0 == -0.0: " << o << std::endl;

    // 浮動小数点は＋∞と-∞を表現できる
    std::cout << "+∞ of float: " << std::numeric_limits<float>::infinity() << std::endl;
    std::cout << "-∞ of float: " << -std::numeric_limits<float>::infinity() << std::endl;

    // 計算結果が未定義の場合(Nan)
    double NaN = std::numeric_limits<double>::quiet_NaN();
    std::cout << NaN << std::endl;

    // Nanとの比較結果
    std::cout << std::boolalpha << "Nan == 0.0: " << (NaN == 0.0) << std::endl;
    std::cout << std::boolalpha << "Nan != 0.0: " << (NaN != 0.0) << std::endl;
    std::cout << std::boolalpha << "Nan == Nan: " << (NaN == NaN) << std::endl;
    std::cout << std::boolalpha << "Nan < 0.0: " << (NaN < 0.0) << std::endl;

    // 有効桁数
    // 浮動小数点数が表現できるのは、仮数部が何桁を正確に表現できるかに依存している
    std::cout << "有効桁数 float: "s << std::numeric_limits<float>::digits10 << std::endl;
    std::cout << "有効桁数 double: "s << std::numeric_limits<double>::digits10 << std::endl;
    std::cout << "有効桁数 long double: "s << std::numeric_limits<long double>::digits10 << std::endl;

    // 浮動小数点数を10進数表記にして、その10進数表記を再び浮動小数点数に戻したときに、制度が落ちることなく再現できる桁数
    std::cout << "f -> i -> f float: "s << std::numeric_limits<float>::max_digits10 << std::endl;
    std::cout << "f -> i -> f double: "s << std::numeric_limits<double>::max_digits10 << std::endl;
    std::cout << "f -> i -> f long double: "s << std::numeric_limits<long double>::max_digits10 << std::endl;

    // epsilon : 浮動小数点数の1と比較して比較可能な最小の値の差
    std::cout << "epsilon float: "s << std::numeric_limits<float>::epsilon() << std::endl;
    std::cout << "epsilon double: "s << std::numeric_limits<double>::epsilon() << std::endl;
    std::cout << "epsilon long double: "s << std::numeric_limits<long double>::epsilon() << std::endl;
}