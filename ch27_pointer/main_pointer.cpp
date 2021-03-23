#include "../all.hpp"

// 関数の型用
namespace func_type {
    int f(int x) {
        std::cout << x << std::endl;
        return x;
    }

    using f_ptr = int (*)(int);
    f_ptr g (f_ptr p) {
            p(0);
            return p;
        };
}

int main(int,char**)
{
    // リファレンスと同じ機能
    {
        // int型オブジェクト
        int object = 0;

        // オブジェクトを変更
        object = 123;
        std::cout << object << std::endl;

        // T型へのリファレンス
        // objectを参照する
        int& reference = object;

        // objectが変更される
        reference = 456;
        std::cout << object << std::endl;

        // referenceはobjectを参照している
        object = 789;

        // 参照するobjectの値
        std::cout << reference << std::endl;
    }

    // ポインタとリファレンス
    {
        // リファレンスは宣言と同時に初期化しなければならない
        int x = 0;

        // rはxを参照する
        int& r = x;

        int y = 1;

        // xに1が代入される
        r = y;

        // intへのリファレンス型
        using ref_type = int&;
        // intへのポインター型
        using ptr_type = int*;

        int object {};
        int& reference = object;
        int* pointer = &object;

        // 書き込み
        reference = 0;
        // 読み込み
        int read = reference;

        // 書き込み
        *pointer = 0;
        // 読み込み
        read = *pointer;

        // オブジェクトのポインター値で初期化
        int* p1 = &object;

        // p1のポインター値で代入
        // つまりobjectを参照する
        int* p2 = p1;

        // リファレンスはポインタのシンタックスシュガーであり、ポインタの機能制限版
    }

    // ポインタのリファレンスと異なる機能
    {
        // リファレンスは代入できないが、ポインタは代入ができる
        int x{};
        int y{};

        int& reference = x;
        // xにyの値を代入
        // リファレンスの参照先は変わらない
        reference = y;

        int* pointer = &x;
        // pointerの参照先をyに変更
        pointer = &y;

        // 未定義動作(Segmentation fault: 11)
        // int* p1;
        // std::cout << *p1 << std::endl;

        // 未定義動作のわからない値のポインターは、たままたどこかの妥当なオブジェクト
        // 参照してしまっているかもしれない。
        // コンパイル時にエラーになるかもしれないし、実行時エラーになるかもしれない.
        // 最悪は、エラーにならず、人知れずバグを生み続ける 
    }

    // nullptr
    {
        int* pointer = nullptr;
        double* p1 = nullptr;
        std::string* p2 = nullptr;

        // C言語とC++では歴史的な理由で、nullptrの他にもNULLもnullポインター値(ただし実装依存)
        float* p3 = NULL;

        // C++では更に歴史的な理由で'0'もnullポインター値として扱う.
        long* p4 = 0;

        // ただし、nullポインター値が実際に'0'である保証はない.
    }

    // 無効な参照先の作り方
    {
        auto fp = []() -> int* {
            // 寿命は関数
            int variable {1};
            return &variable;
        };

        int* ptr = fp();
        // エラー(にならないようだ)
        int read = *ptr;
        std::cout << read << std::endl;

        auto fr = []() -> int& {
            // 寿命は関数
            int variable {2};
            return variable;
        };

        int& ref = fr();
        read = ref;
        std::cout << read << std::endl;
    }

    // ポインターとリファレンス 詳細
    {
        // intへのポインター型
        using t1 = int*;

        // doubleへのポインター型
        using t2 = double*;

        // std::stringへのポインター型
        using t3 = std::string*;

        // std::array<int, 5>へのポインター型
        using t4 = std::array<int,5>*;

        // std::array<double, 10>へのポインター型
        using t5 = std::array<double, 10>*;

        // int*型へのリファレンス
        using type = int*&;

        // int&型へのポインターはできない
        // using error = int&*;

        // リファレンスからポインターの値を得るには、参照先のオブジェクトと同じく&を使う
        int data{};
        int& ref = data;
        // &dataと同じ
        int* ptr = &ref;
        // リファレンスは参照先のオブジェクトと全く同じように振る舞う

        // ポインターのリファレンスを得るのは、ポインター以外の値と全く同じ
        int* p = nullptr;
        // pを参照する
        int*& p_ref = p;
        // pの値が&dataになる
        p_ref = &data;
    }

    // ポインターとconst
    {
        // 型Tとconst
        using T = int;
        using const_T = const T;

        // 型Tとポインター
        using T_pointer = T*;

        // どちらともconstなT
        using const_T_1 = const T;
        using const_T_2 = T const;

        // どちらもconstなTへのポインター(ポインタは書き換え可能)
        using const_T_pointer_1 = const T*;
        using const_T_pointer_2 = T const*;

        // Tへのconstなポインター(Tは書き換え可能. ポインタは読み取り専用)
        using T_const_pointer = T* const;

        // どちらもconstなTへのconstなポインター
        using const_T_const_pointer_1 = const T* const;
        using const_T_const_pointer_2 = T const* const;
    }

    // ポインターのポインター
    {
        // 適当なU型
        using U = int;

        // ポインターとしてのT型
        using T = U*;

        // T型へのポインター型 = U型へのポインター型のポインター型
        using type = T*;

        // int
        int x = 123;
        // intへのポインター
        int* p = &x;
        // intへのポインターのポインター
        int** pp = &p;

        // 123
        // ポインターを経由したポインターを経由したxの読み込み
        int value1 = *(*pp); // pp:ポインタのポインタ(=ポインタのアドレス), *pp:ポインタのポインタの中身(=中身のアドレス), **pp: *ppが指す値

        int y = 456;
        // ポインターを経由した変数pの変更(*ppはxへのアドレスが入っていた)
        *pp = &y; // 宛先をyに変更
        std::cout << "y = " << **pp << std::endl; // 456

        // 456
        // yの読み込み　
        int value2 = **pp;
    }

    // intへのポインターへのポインターへのポインター型
    {
        using type = int***;
        using const_type = const int* const* const*;
    }

    // 関数の型
    // int f(int);
    // double g(double, double);
    
    // 関数ポインタ
    {
        using f_type = int (int);  // 関数の型
        using f_pointer = f_type*; // 関数型のポインタ　：　実際は int (*)(int)

        f_pointer ptr = &func_type::f;

        // 関数へのポインターを経由した関数呼び出し
        (*ptr)(123);
        

        // 重大事実：
        // C++では特別に関数へのポインターはそのまま関数呼び出すできるようになっている
        ptr(123);
       
    }

    // 変数ptrの宣言をf_pointerというエイリアス宣言を使わずに、書くと以下のようになる
    {
        // 変数ptrの宣言
        // int (int)へのポインタ
        int (*ptr)(int) = &func_type::f;
        
        (*ptr)(456);
        

        ptr(456);
        

        // 関数型int (int)のポインタ型は
        using f_ptr_type = int (*)(int);
        f_ptr_type f_ptr = &func_type::f;

        f_ptr(789);
        

        f_ptr = nullptr; // ヌルポにできる
    }

    // 関数へのポインターは型であり、値でもある。
    // 値であるということは、関数は引数として関数へのポインタを受け取ったり
    // 関数へのポインターを返したりできる.
    {
        using f_ptr = int (*)(int );
        // 関数へのポインターを引数にとり、
        // 関数へのポインターを戻り値として
        // 返す関数g
        func_type::g(&func_type::f);
        
        // 関数gへのポインタ型
        auto g_ptr_1 = &func_type::g;
        int (*(*ptr)(int (*)(int)))(int) = &func_type::g;

        // 解説
        {
            int (* // 戻り値型前半
                (*p)   // 変数名
                ( // 関数の引数
                    int (*)(int) // 引数としての関数へのポインター
                ) // 関数の引数
            )(int) // 戻り値の型後半
            = &func_type::g;
        }

        // 非常に読みづらいので、戻り値の型を後置する文法を使うといくらかマシ
        auto (*fp)(int (*)(int)) -> int (*)(int) = &func_type::g; // autoはプレースホルダー

        // まだ読みづらいのでエイリアスを使うのが最良
        using func_ptr = int (*) (int);
        auto (*fp2)(func_ptr) -> func_ptr = &func_type::g;
    }
}