#include "../all.hpp"

int main(int, char**)
{
    // vectorの要素を先頭から順番に標準出力に出力するコード
    {
        std::vector<int> v = {1,2,3,4,5};

        for (auto i = std::begin(v), j = std::end(v); i != j; ++i) 
        {
            std::cout << *i << std::endl;
        }
    }

    
    // イテレータ[first, last)を渡すと、イテレータの先頭から末尾まで
    // 順番に処理してくれる関数
    auto print_all = [](auto first, auto last) {
        // ループ
        for (auto iter = first; iter != last; ++iter)
        {
            // 重要な処理
            std::cout << *iter << std::endl;
        }
    };

    {
        std::vector<int> v = {1,2,3,4,5};

        print_all(std::begin(v), std::end(v));
    }

    // print_allは便利だが、重要な処理がハードコードされている
    // 重要な処理ごとにハードコードすると、似た処理が増える。
    {

        // 値が100以下なら出力
        auto print_if_le_100 = [](auto first, auto last) {
            // ループ
            for (auto iter = first; iter != last; ++iter)
            {
                // 重要な処理
                if (*iter <= 100)
                    std::cout << *iter << std::endl;
            }
        };

        // 値を2倍して出力
        auto print_twice = [](auto first, auto last) {
            // ループ
            for (auto iter = first; iter != last; ++iter)
            {
                // 重要な処理
                std::cout << 2 * (*iter) << std::endl;
            }
        };

        // ・・・
    }

    // 関数は変数に代入できる
    {
        // 関数を引数に取り呼び出す関数
        auto call_func = [](auto func) {
            func(1234);
        };

        // 引数を出力する関数
        auto print = [](auto x) { std::cout << x << std::endl; };

        call_func(print);

        // 引数を2倍して出力する関数
        auto print_twice = [](auto x) { std::cout << 2 * x << std::endl; };

        call_func(print_twice);
    }

    // for_each
    // やること：問題を「for文によるループ」と「特別な処理」に分割すること!
    {
        // 要素ごとの特別な処理をする関数を引数で受け取り、
        // 要素ごとに関数を適用する関数
        auto for_each = [](auto first, auto last, auto f) {
            for (auto iter = first; iter != last; ++iter) 
            {
                f(*iter);
            }
        };

        std::vector<int> v = {9, 18, 27, 36, 45};

        // 引数を出力する関数
        auto print = [](auto x) { std::cout << x << std::endl; };

        for_each(std::begin(v), std::end(v), print);

        // 引数を2倍して出力する関数
        auto print_twice = [](auto x) { std::cout << 2 * x << std::endl; };

        for_each(std::begin(v), std::end(v), print_twice);

        // 関数は変数に代入しなくても使えるので、上のコードは以下のようにもかける.
        for_each(std::begin(v), std::end(v), [](auto value) { std::cout << value << std::endl; });
    }

    // std::for_eachは便利
    {
        std::vector<int> v = {1,2,3,4,5};

        std::for_each(std::begin(v), std::end(v), [](auto value) { std::cout << value << std::endl; });
    }

    // C++17の時点までは、まだ使えないがC++20ではイテレータを渡さずに、vectorを直接渡すことができる
    {
        std::vector<int> v = {6,7,8,9,10};

        // std::for_each(v, [](auto value) { std::cout << value << std::endl; });
    }

    // for_eachの関数オブジェクト引数の引数がリファレンスを指定していると元データを書き換えることができる.
    {
        std::vector<int> v = {1,2,3,4,5};

        // 引数をリファレンスでとって、2倍にする関数
        auto twice = [](auto& value) { value = 2 * value; };

        std::for_each(std::begin(v), std::end(v), twice);

        std::for_each(std::begin(v), std::end(v), [](auto& value) { std::cout << value << std::endl; });
    }
}