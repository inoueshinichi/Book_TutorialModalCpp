#include "../all.hpp"

// 名前区間を指定しなくてもよいinline名前空間
inline namespace A {
    int a {};
}

// 普通の名前空間
namespace B {
    int b {};
}


int main(int, char**) {

    a = 0; // A::a
    A::a = 0; // A::a

    // b = 0; // エラー
    B::b = 0; // B::b

}