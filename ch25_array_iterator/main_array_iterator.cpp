#include "../all.hpp"

#include "array_iterator.hpp"

int main(int,char**)
{
    // イテレータの中身
    {
        std::array<int, 5> a = {1,2,3,4,5};
        auto first = std::begin(a);
        auto last = std::end(a);

        auto iter = a.begin();
        std::cout << *iter << std::endl; // 1
        ++iter;
        std::cout << *iter << std::endl; // 2
    }

    // arrayとarray_iteratorはアルゴリズムに渡せるようになった
    {
        array<int, 5> a = {1,2,3,4,5};

        std::for_each(std::begin(a), std::end(a), [](auto x) { std::cout << x; });
        std::cout << std::endl;
    }
    
    // constなイテレータ
    {
        std::array<int, 5> a = {1,2,3,4,5};

        // iterator
        std::array<int,5>::iterator iter = a.begin();

        // const_iterator
        std::array<int,5>::const_iterator const_iter = a.cbegin();

        // iterator
        // const iterator
        // const_iterator
        // const const_iterator
        using Array = std::array<int,5>;

        // iterator
        Array::iterator i;
        // const iterator
        // const Array::iterator c_i;
        // const_iterator
        Array::const_iterator ci;
        // const const_iterator
        // const Array::const_iterator c_ci;
    }

    // const_iteratorを取得する方法
    {
        // constなarrayのbegin/end
        {
            // constなarray
            const std::array<int, 5> ca = {1,2,3,4,5};
            // const_iterator
            auto i = ca.begin();
        }
        
        // cbegin/cend
        {
            std::array<int,5> a = {1,2,3,4,5};
            // const_iterator
            auto i = a.cbegin();
        }

        // iteratorからconst_iteratorに変換
        {
            using Array = std::array<int,5>;
            Array a = {1,2,3,4,5};

            // iterator
            Array::iterator i = a.begin();
            // iteratorからconst_iteratorに変換
            Array::const_iterator j = i;
        }
    }

    // const iteratorではダメな理由 -> const iteratorは値を変更できないから.
    // イテレータクラス自身は書き換えできて、中身のコンテナは変更できないようにしたい. -> const_iteratorが必要!
    {
        using Array = std::array<int,5>;
        Array a = {1,2,3,4,5};

        // const iterator
        const Array::iterator iter = a.begin();

        // エラー
        // constなオブジェクトは変更できない
        // ++iter;

        // OK
        // iterは変更していない. コピーが作られるだぇ
        auto next_iter = iter + 1;
    }

    // const_iteratorならばイテレータ自体の変更はできる
    {
        using Array = std::array<int,5>;
        Array a = {1,2,3,4,5};

        auto citer = a.begin();

        // OK
        // イテレータ自体の変更
        ++citer;

        // OK
        // 要素を変更しない
        std::cout << *citer << std::endl;

        // エラー
        // 要素を変更している
        // *citer = 0;
    }

    // const const_iteratorはconst_iteratorのconst.
    // const const_iteratorはconst iteratorと同じく、イテレータ自体の変更ができない.
    {
        using Array = std::array<int,5>;
        Array a = {1,2,3,4,5};

        // const const_iterator
        const auto iter = a.begin();

        // エラー
        // constなオブジェクトは変更できない
        // ++iter;

        // OK
        // iterは変更していない
        auto next_iter = iter + 1;
    }

}