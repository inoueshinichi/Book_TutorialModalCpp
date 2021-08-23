#include "../all.hpp"


int main(int, char**) {

    // 準備
    {
        std::vector<int> v = {1,2,3,4,5};
        int x = v.at(2); // 3
        v.at(2) = 0;
        // vは{1,2,0,4,5}
    }
    
    // イテレータの取得方法
    {
        std::vector<int> v = {1,2,3,4,5};
        auto i = std::begin(v);
    }

    // イテレータの参照する要素に対する読み書き
    {
        std::vector<int> v = {1,2,3,4,5};

        auto i = std::begin(v);

        int x = *i; // 1

        *i = 0;
        // vは{0,2,3,4,5}
    }

    // イテレータの参照する要素を変更
    {
        std::vector<int> v = {1,2,3,4,5};
        
        auto i = std::begin(v);

        *i; // 1
        ++i;
        *i; // 2;
        ++i;
        *i; // 3

        --i;
        *i; // 2
        --i;
        *i; // 1;
        --i;
        std::cout << *i << std::endl; // 範囲を外れたら０が出力される
        --i;
        std::cout << *i << std::endl; // 範囲を外れたら０が出力される
    }
    {
        std::vector<int> v = {1,2,3,4,5};
        
        auto iter = std::begin(v);

        for (std::size_t i = 0; i != std::size(v); ++i, ++iter) {
            std::cout << *iter << "\n"s;
        }
        std::cout << std::endl;
    }

    // イテレータの比較
    {
        // 同じ順番の要素を指すイテレータは等しく、そうでないイテレータは等しくない
        std::vector<int> v = {1,2,3,4,5};

        auto x = std::begin(v);
        auto y = x;

        // x, yは0番目の要素を指す

        bool b1 = (x == y); // true
        bool b2 = (x != y); // false

        ++x; // xは1番目の要素を指す.

        bool b3 = (x == y); // false
        bool b4 = (x != y); // true
    }

    // 最後の次の要素へのイテレータ
    {
        std::vector<int> v = {1,2,3};

        // 最後の次の要素を指し示すイテレータ
        auto i = std::end(v);

        *i; // 未定義動作 or エラー
        std::cout << "last next *i: " << *i << std::endl;

        ++i; // ワーニング 未定義動作
        std::cout << "last last next *i: " << *i << std::endl;

        // 最後の要素の次は比較できる
        auto x = std::begin(v);
        auto y = std::end(v);

        std::cout << std::boolalpha << (x == y) << std::endl; // false
        ++x;
        std::cout << std::boolalpha << (x == y) << std::endl; // false
        ++x;
        std::cout << std::boolalpha << (x == y) << std::endl; // false
        ++x;
        std::cout << std::boolalpha << (x == y) << std::endl; // true
    }
    {
        std::vector<int> v = {1,2,3,4,5};
        for (auto iter = std::begin(v), last = std::end(v); iter != last; ++iter) {
            std::cout << *iter << std::endl;
        }
    }

    // なんでもイテレータ
    {
        // std::vectorにしか使えないコード
        {
            std::vector<int> v = {1,2,3,4,5};
            for (std::size_t i = 0; i != std::size(v); ++i) {
                std::cout << v.at(i) << std::endl;
            }
        }

        // イテレータに書き直したコード
        {
            std::vector<int> v = {1,2,3,4,5};
            for (auto iter = std::begin(v), last = std::end(v); iter != last; ++iter) {
                std::cout << *iter << std::endl;
            }
        }

        // この要素を先頭から出力する処理の関数
        auto output_all = [](auto first, auto last) {
            for (auto iter = first; iter != last; ++iter) {
                std::cout << *iter << std::endl;
            }
        };

        // イテレータに対応しているあらゆるコンテナを出力できる
        {
            std::vector<int> v = {2,4,8,16,32};
            output_all(std::begin(v), std::end(v));

            // 標準入力イテレータ
            // std::istream_iterator<int> first(std::cin), last;
            // output_all(first, last);

            // カレントディレクトリにあるファイル一覧を取得するイテレータ
            // std::filesystem::directory_iterator first("./"), last;
            // output_all(first, last);
        }

        auto output_all_2 = [](auto first, auto last, auto output_iter) {
            for (auto iter = first; iter != last; ++iter, ++output_iter) {
                *output_iter = *iter;
            }
        };

        {
            // 標準出力に出力するイテレータ
            std::vector<int> v = {3,5,9,17,33};
            output_all_2(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout));
            std::cout << std::endl;
        }

        // イテレータと添字の範囲
        {
            // 半閉鎖[i, j)でイテレータi, j (i<=j)でj-iは、i~jの範囲にある個数
            std::vector<int> v = {2,3,4,5,6,7,8,9,10,11,12};
            
            auto i = std::begin(v);
            auto j = std::end(v);

            // 11 
            // イテレータの範囲の要素の個数
            std::cout << j - i << std::endl;

            ++i; // 先頭の要素の次の要素を指す
            std::cout << j - i << std::endl;

            // 半閉鎖[i, j)は、変数ｖが空の場合でも動作できる
            std::vector<int> ev; // 空

            // 空なので何も出力されない
            for (auto i = std::begin(v), j = std::end(v); i != j; ++i) {
                std::cout << *i << std::endl;
            }
        }
    }
}