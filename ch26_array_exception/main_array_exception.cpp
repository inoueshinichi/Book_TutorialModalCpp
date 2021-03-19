#include "array_exception.hpp"

#include "../all.hpp"


struct Object {
    std::string name;

    // コンストラクタ
    Object(const std::string& name) : name(name) {
        std::cout << name << " is constructed. " << std::endl;
    }

    // ですとらくた　
    ~Object() {
        std::cout << name << " is destructed. " << std::endl;
    }
};

int main(int,char**)
{
    // 例外を投げる
    {
        // 妥当な要素はa[0]のみ
        std::array<int,1> a = {1};

        // エラー、範囲外
        // a[1000] = 0;

        // エラー通知
        // a.at(1000) = 0;
    }

    {
        // int型の値123を投げる
        // throw 123;

        // double型の値3.14を投げる
        // throw 3.14;

        std::array<int,5> value = {1,2,3,4,5};

        // std::array<int,5>型の変数valueを投げる
        // throw value;
    }

    // ゼロを入力すると例外を投げるプログラム
    // {
    //     // 0を入力するなよ。絶対するなよ。。
    //     std::cout << "Don't type 0. >";

    //     int input{};
    //     std::cin >> input;

    //     // 入力が0なら例外を投げる
    //     if (input == 0)
    //         throw 0;
        
    //     // 通常の処理
    //     std::cout << "Success!" << std::endl;
    // }

    // std::out_of_rangeクラス
    {
        std::out_of_range err("I am error.");

        // I am error.
        std::cout << err.what() << std::endl;
    }


    // try-catch文で例外を捕捉
    {
        try {
            throw 123;
        }
        // キャッチする
        catch(int e) {
            std::cout << e;
        }

        // 実行される
        std::cout << "resumed." << std::endl;
    }

    // catchの型と投げられた例外の型が一致しない場合、キャッチしない
    {
        // try {
        //     throw 3.14; // double型
        // }
        // catch (int e) {
        //     std::cout << e;
        // }
        // // キャッチされない時点でプログラムが終了する.

        // //実行されない
        // std::cout << "You won't read this." << std::endl;
    }


    // 例外は複数書くことができる
    {
        try {
            throw "error"s;
        }
        catch (int e) {}
        catch (double e) {}
        catch (std::string& e) {
            std::cout << e << std::endl;
        }
    }

    
    // tryブロックの中で投げられた例外は、たとえ複雑な関数呼び出しの奥底にある
    // 例外でも、あますことなくキャッチする
    {
        auto f = []() { throw 123; };
        auto g = [&]() { f(); };
        auto h = [&]() { g(); };

        try {
            h();
        } 
        catch (int e) {
            // キャッチされる
            std::cout << e << std::endl;
        }
    }

    // std::arrayのat例外std::out_of_rangeをキャッチする
    {
        std::array<int, 1> a = {1};

        try { a[1000]; } // 例外出力されないいんだけど。。。
        catch (std::out_of_range& e) {
            // エラー内容を示す文字列
            std::cout << e.what() << std::endl;
        }
    }

    // std::terminate
    {
        // std::terminate();
    }

    // 例外による巻き戻し：スタックアンワインディング(stack unwinding)
    {
        auto f = []() { 
            throw 123;

            // 実行されない
            std::cout << "Don't done f." << std::endl;
        };

        auto g = [&]() { 
            try { //try4
                f();
            }
            catch (double e) {
                std::cout << "g: " << e << std::endl;
            }

            // 実行されない
            std::cout << "Don't done g." << std::endl;
        };

        auto h = [&]() { 
            try { //try3
                g();
            }
            catch (std::string& e) {
                std::cout << "h: " << e << std::endl;
            }

            // 実行されない
            std::cout << "Don't done h." << std::endl;
        };

        // try-catch
        try { //try1
            try { //try2
                h();
            } 
            catch (char e) {
                std::cout << "try2: " << e << std::endl;
            }

            // 実行されない
            std::cout << "Don't done try2." << std::endl;
        }
        catch (int e) {
            std::cout << "try1: " << e << std::endl;
        }
    }


    // スタックアンワインディングが起こると、通常のプログラムは実行されない。
    // ただし、変数の破棄によりデストラクタは呼ばれる.
    {
        auto f = []() {
            Object obj("f");
            throw 0;
        };

        auto g = [&]() {
            Object obj("g");
            f();
        };

        Object obj("main");

        try {
            g();
        }
        catch (int e) {
            std::cout << "caught." << std::endl;
        }
    }


    // 例外が投げられると通常の実行は飛ばされるので、例外が投げられるかもしれない処理の後に、
    // 例外の有無に関わらず絶対に実行したい処理がある場合、クラスのデストラクタに書くとよい.
    // C++20以降では、標準ライブラリにstd::scope_exitが追加された. std::scope_exitクラスは,
    // 渡した関数オブジェクトをデストラクタで実行してくれる
    {
        auto f = []() {
            // auto ptr = new int;
            // std::scope_exit e( [&]() { delete ptr; } ); // リソース開放

            throw 0;

            // なにかの処理
        };

        try {
            f();
        }
        catch (int e) {
            std::cout << e << std::endl;
        }
    }   
}