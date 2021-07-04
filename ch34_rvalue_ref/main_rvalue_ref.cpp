#include "../all.hpp"

// lvalueとは名前付きのオブジェクトや戻り値の型としてのlvalueリファレンス
// アドレスを持つ
int object{};
int& f() { return object; }

// rvalueとは名前なしのオブジェクトや計算結果の一時オブジェクト、戻り値の型としてのrvalueリファレンス
// アドレスを持たない
int&& g() { return 0; }
int h() { return 0; }

struct X { int data_member; };


namespace move_ns
{
    // ----------------------------
    template <class T>
    T && move_test1(T& t) noexcept
    {
        return static_cast<T &&>(t);
    }

    // ----------------------------
    template <class T>
    T && move_test2(T& t) noexcept
    {
        return static_cast<T &&>(t);
    }

    template <class T>
    T && move_test2(T&& t) noexcept
    {
        return static_cast<T &&>(t);
    }

    // ----------------------------
    template <class T>
    void f(T&& t)
    {
        using A = T &;
        using B = T &&;
    }

    // ----------------------------
    // lvalueもrvalueｍ受け取ることができるmove
    template <class T>
    T && move_test3(T && t) noexcept
    {
        return static_cast<T && >(t);
    }
    // 上記のmove_test3()には問題がある.
    // move_test3()にlvalueを渡したとき,
    // lvalueの型をUとすると, テンプレートパラメータTはU &となる.
    // テンプレートパラメータTがリファレンスのとき、Tにリファレンス宣言子&&
    // をつけても単に無視されることを考えると, 上のmove_test3()にint & or int型の
    // lvalueをが実引数として渡されたとき、以下のようにかいたものになる.
    // int & move_test3(int & t) noexcept
    // {
    //     return static_cast<int &>(t);
    // }
    // POINT: 問題箇所はstatic_cast<int &>担ってしまうこと.
    // つまり、実引数がlvalueの場合, xvalueに変換できない.

    // ----------------------------
    // 正しいmove()の実装
    template <class T>
    std::remove_reference_t<T> && move(T && t) noexcept
    {
        return static_cast<std::remove_reference_t<T> &&>(t);
    }
}


namespace forward_ns
{
    // lvalue用
    template <typename T>
    constexpr
    T &&
    forward(std::remove_reference_t<T>& t) noexcept
    {
        return static_cast<T &&>(t);
    }
    // rvalue用
    template <typename T>
    constexpr
    T &&
    forward(std::remove_reference_t<T>&& t) noexcept
    {
        return static_cast<T &&>(t);
    }
}


int main(int, char**)
{
    // rvalueリファレンスの宣言
    {
        int value = 100;

        // T型へのlvalueリファレンス
        int& lvalue_ref = value;

        // T型へのrvalueリファレンス
        int&& rvalue_ref = std::move(value);

        // lvalueリファレンス
        // 式objectや式f()を評価した結果はlvalueとなる.
        int& a = object;
        int& b = f();

        // rvalueリファレンス
        // 式0, 式1+1, 式g()を評価した結果はrvalueとなる.
        int&& c = 0;
        int&& d = 1 + 1;
        int&& e = g();
        int&& f = h();

        // rvalueリファレンスをlvalueで初期化できない.
        // lvalueリファレンスをrvalueで初期化できない.

        // リファレンスを初期化することを、リファレンスはリファレンス先を束縛するという.
        // lvalueリファレンスはlvalueを束縛する.
        // rvalueリファレンスはrvalueを束縛する.
        // ただし, constなlvalueリファレンスはrvalueを束縛できる.

        // OK, constなlvalueリファレンス
        const int& g = 0;
        const int& h = 1 + 1;
        // const int& i = g();


        // rvalueリファレンス自体はlvalueである.
        // 何故ならrvalueリファレンスはオブジェクトに名前をつけて束縛するから.

        // rvalueリファレンス
        int&& j = 0;
        // OK, rvalueリファレンスjはlvalue
        int&k = j;
        // エラー, rvalueリファレンスjはrvalueでない
        // int&&l = j;
    }

    // 値カテゴリー
    {
        // lvalue -> 左辺値(left-hand value)
        // rvalue -> 右辺値(right-hand value)
        // C言語すらなかったはるか昔から存在する用語.
        // lvalue = rvalue;
        // C++では本来の左辺値,右辺値の意味としてlvalueとrvalueを使っていない.

        // 以下, C++の値カテゴリーにおけるlvalueとrvalueの定義.
        // 1. 式(expression)とは、`glvalue`か`rvalue`である.
        // 2. `glvalue`とは`lvalue`か`xvalue`である.
        // 3. `rvalue`とは`prvalue`か`xvalue`である.

        // 値カテゴリー図
        //           expression
        //          /          \
        //      glvalue       rvalue
        //     /         \  /        \
        // lvalue       xvalue      pvalue

        // 1) lvalue -> 名前時オブジェクト
        int object;
        int& ref = object;

        // 2) pvalue -> pure rvalue : 名前無しのオブジェクトや計算結果の一時オブジェクト
        // 殆どのpvalueは式を評価するときに自動生成され、自動的に破棄されるので意識する必要はない.
        0;
        1 + 1;
        h();
        // 関数の戻り値の型がリファレンス出ない場合、一時オブジェクトが生成される
        auto func = []() -> int { return 100; };
        func();
        // 演算子も関数の一種なので
        int x,y,z=0;
        auto result = x + y + z;
        // のような式がある場合、先ず`x + y`が評価され、その結果が一時オブジェクトとして返される。
        // その一時オブジェクトを仮にtempとすると、`temp + z`が評価され、また一時オブジェクトが生成され,
        // 変数resultに代入される.
        // 式文全体を評価し終わったあとに、一時オブジェクトは自動的に破棄される.


        // 3) xvalue -> xvalueとは寿命が付きかけているlvalue(eXpiring lvalue).
        // xvalueはlvalueやprvalueから変換することで発生する.
        // xvalueとなる例.

        // 3-1(重要) 戻り値の型がオブジェクトの型へのrvalueリファレンスである関数の呼び出し結果
        auto func1 = []() -> int&& { return 0; };
        // xvalue
        int&& r = func1(); // rvalueリファレンスというlvalueをrvalueリファレンスで束縛している! -> 関数の戻り値int&&はxvalueになっているのでoK

        // 3-2(重要) オブジェクトの型へのrvalueリファレンスへのキャスト
        int target{};
        // xvalue
        int&& r2 = static_cast<int&&>(target);

        // 3-3 xvalue配列への添字操作
        int a[3] = {1,2,3};
        // xvalue
        int&& r3 = static_cast<int (&&)[3]>(a)[0];

        // 3-4 xvalueなクラスのオブジェクトへのリファレンスでない非staticデータメンバーへのアクセス
        X xx{};
        int&& r4 = static_cast<X&&>(xx).data_member;

        // 3-5 式.*で最初のオペランドがxvalueで次のオペランドがデータメンバーへのポインターの場合
        int&& r5 = static_cast<X&&>(xx).*&X::data_member;


        // 4) rvalue -> rvalue = prvalue or xvalue.
        // rvalueリファレンスはrvalueでしか束縛できない. rvalueはprvalueかxvalue
        // lvalueはxvalueに変換できるので、結果的にrvalueに変換できることになる.

        // lvalueなオブジェクト
        int lvalue{};
        // OK, lvalueリファレンスはlvalueで初期化できる.
        int& l_ref = lvalue;
        // OK, rvalueリファレンスはrvalueで初期化できる
        // rvalueリファレンスにキャストした結果はxvalue->rvalue
        int&& r_ref = static_cast<int&&>(lvalue);

        // POINT: lvalueは、そのままではrvalueではないが、xvalueに変換すればrvalueになる!!!!

    
        //5) glvalue -> generalized lvalue -> lvalue or xvalue
        // lvalueから変換したxvalueは元来lvalueだったのだからglvalueとなるのも自然.
        // xvalueに変換したprvalueはglvalueになれる.
    }


    // rvalueリファレンスのライブラリ
    {
        // std::move(e)は、値eをxvalueに変換するための標準ライブラリ.
        // std::move(e)は値eの型Tへのrvalueリファレンス型にキャストしてくれるので, xvalueになる.
        // そしてxvalueはrvalueである.

        int lvalue{};
        int&& r = std::move(lvalue);
        
        // 上記は, 下記と同じ
        int lvalue2{};
        int&& r2 = static_cast<int&&>(lvalue2);
    }

    // std::moveの実装
    {
        // std::move(e)の実装は少しむずかしい.
        // 根本的には式eのリファレンスでない型Tに対して、
        // static_cast<T &&>(e)をしているだけ。

        // lvalueはxvalueに変換できるが, rvalue(=prvalueとxvalue)をxvalueに変換できない.
        int obj{};
        int&& ref_test1_lvalue = move_ns::move_test1(obj); // コンパイル可能
        // エラー, prvalueを変換できない
        // int&& ref_test1_prvalue = move_ns::move_test1(0);
        // エラー, xvalueをxvalueに変換できない.
        // int&& ref_test1_xvalue = move_ns::move_test1(move_ns::move_test1(obj));

        
        // move_test2()関数を使うとlvaueもrvalue(prvalue, xvalue)もxvalueに変換できる
        int&& ref_test2_lvalue = move_ns::move_test2(obj);
        int&& ref_test2_prvalue = move_ns::move_test2(0);
        int&& ref_test2_xvalue = move_ns::move_test2(move_ns::move_test2(obj));
        // POINT: だが、move_test2は2種類のoverloadで成り立っているのでなんとかして、１つだけのmove_test2()関数にしたい.
    }

    // フォワーディングリファレンス
    {
        // POINT: C++ではテンプレートパラメータへのrvalueリファレンスを関数の
        // 仮引数として取る場合を、フォワーディングリファレンス(forwarding reference)
        // として、特別にlvalueでもrvalueでも受け取れるようにしている.

        // T &&はフォワーディングリファレンス
        // templaet <class T>
        // void f(T && t);

        // フォワーディングリファレンスをもつテンプレート関数の仮引数tに
        // 実引数としてrvalueを渡すと, Tはrvalue型となる. tの型はT &&.
        // Tはint
        // f(0);

        // もし実引数として型Uのlvalueを渡すと、テンプレートパラメータTが
        // U &となる. そして、テンプレートパラメータTに対するリファレンス宣言子(&,&&)
        // は単に無視される.
        // int lvalue{};
        // Tはint&
        // T &&はint &
        // f(lvalue);

        // prvalue
        move_ns::f(0); // T:int, A:int &, B:int &&
        int lvalue{};
        // lvalue
        f(lvalue); // T:int &, A: int &, B:int &


        // std::remove_referenct_t
        // int
        using A = std::remove_reference_t<int>;
        // int
        using B = std::remove_reference_t<int &>;
        // int
        using C = std::remove_reference_t<int &&>;

        // int &&
        using RT = std::remove_reference_t<int &> &&;

        // 型操作 e.g.
        // std::add_pointer_t<T>
        // std::remove_pointer_t<T>
        // std::add_lvalue_referenct_t<T>
        // std::add_rvalue_reference_t<T>
        // std::remove_reference_t<T>

    }

    // std::forward
    {
        // 関数f()から別の関数g()に値を渡したい場合の話.

        // template <class T>
        // void g(T&& t) {}

        // template <class T>
        // void f(T && t)
        // {
        //     g(t); // f()の実引数がlvalue,rvalueであれ、g()への実引数がlvalueになってしまう.
        // }

        // rvalueを渡すのは簡単. std::move()を使えば良い.

        // template <typename T>
        // void f(T && t)
        // {
        //     g(std::move(t)); // これは、tがlvalueのときも問答無用でxvalueにしてしまう。
        // }

        // tがlvalueならばlvalueとして, rvalueならばxvalueとして, 渡さされた
        // 値カテゴリーのまま別の関数に渡したい場合、std::forward<T>(t)が使える.
        // template <typename T>
        // void f(T&& t)
        // {
        //     g(std::forward<T>(t));
        // }


    }
}