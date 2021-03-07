#include "../all.hpp"


int main(int, char**)
{
    // lvalueリファレンス
    {
        int a = 1;
        int b = 2;

        b = a;
        // b == 1

        b = 3;
        // a == 1
        // b == 3

        auto assign_3 = [](int x) -> void {
            x = 3;
        };

        assign_3(a);
        std::cout << "a: " << a << std::endl;

        // lvalueリファレンス
        int& ref = a; // lvalueリファレンスは必ず初期化しなければならない

        ref = 3;
        std::cout << "a: " << a << std::endl;

        // int& ref2; // エラー

        // lvalueリファレンスは関数でも使える。
        auto f = [](int& x) -> void {
            x = 5;
        };

        f(a);
        std::cout << "a: " << a << std::endl;
    }

    // スワップ
    auto swap = [](auto& a, auto& b) {
        auto temp = a;
        a = b;
        b = temp;
    };

    // const
    {
        // 値を変更したくない変数は、constをつけることで変更を禁止できる
        int x = 0;
        x = 1; // OK, 変更できる

        const int y = 0;
        // y = 0; // エラー, 変更できない

        // 意味は同じ
        const int z = 0;
        int const w = 0;
    }

    // constは、lvalueリファレンスと組み合わせることができる
    {
        int x = 0;

        int & ref = x;
        // OK
        ++ref;

        const int& const_ref = x;
        // エラー
        // ++const_ref;
    }

    // constは本当に文法が変わっていて混乱する
    {
        int a = 0;

        // OK, 意味は同じ
        const int& b = a;
        int const& c = a;

        // エラー
        // int& const d = a;
    }

    // constがついてない型のオブジェクトをconstなlvalueリファレンスで参照できる
    {
        int x = 0;

        // OK
        int& ref = x;
        // OK, constはつけてもよい
        const int& cref = x;
    }

    // constのついている型のオブジェクトをconstの付いていないlvalueリファレンスで参照することはできない
    {
        const int x = 0;

        // エラー、constがない
        // int& ref = x;

        // OK, constが付いている
        const int& cref = x;
    }

    // 以下のコードは非効率的。関数の仮引数に値を渡すとき、実引数がコピーされるから
    {
        auto f = [](std::vector<int> v) -> void {
            std::cout << v.at(1234) << std::endl;
        };

        // 10000個の要素を持つvector
        std::vector<int> v(10000);

        f(v);
    }

    // リファレンスを使うと不要なコピーをしなくて済む
    // しかし、リファレンスを受け取ると、うっかり変数を変更してしまった場合、
    // その変更が関数の呼び出し元に反映されてしまう。
    {
        auto f = [](std::vector<int>& v) -> void {
            std::cout << v.at(1234) << std::endl;
        };

        // 10000個の要素を持つvector
        std::vector<int> v(10000);

        f(v);

        // 値は、変更されているかもしれない
    }

    // constなlvalueリファレンスは、不要なコピーを避けて値を書き換えないことを保証する
    {
        auto f = [](const std::vector<int>& v) -> void {
            std::cout << v.at(1234) << std::endl;
        };

        // 10000個の要素を持つvector
        std::vector<int> v(10000);

        f(v);

        // 値は、変更されない
    }
    
}


