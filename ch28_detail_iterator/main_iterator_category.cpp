#include "../all.hpp"

#include "iterator_category.hpp"

namespace inference_type_ns
{
    template <class T>
    void f(T) {
        std::cout << "Inference of f func" << std::endl;
    }

    template <class T>
    struct S
    {
        S(T) {
            std::cout << "Inference of S class" << std::endl;
        }
    };
}


int main(int, char**)
{
    // イテレータカテゴリーを調べる
    {
        using namespace iterator_traits_ns;
        using iterator = std::vector<int>::iterator;
        bool b = is_category_of<std::forward_iterator_tag, iterator>();
        std::cout << std::boolalpha << b << std::endl;
    }

    // 出力イテレータ
    {
        std::array<int, 5> a = {1,2,3,4,5};
        std::vector<int> v(a.size());

        // 前方イテレータ以降の派生クラスのイテレータは出力イテレータとみなせる
        std::copy(std::begin(a), std::end(a), std::begin(v));
    }

    // cout_iterator : 出力イテレータの派生
    {
        std::vector<int> v = {1,2,3,4,5};
        using namespace output_iterator_ns;
        cout_iterator out_it;

        std::copy(std::begin(v), std::end(v), out_it);
        std::cout << std::endl;
    }

    // 標準ライブラリのostream_iterator
    // std::ostream_iterator = cout_iterator
    {
        std::vector<int> v = {1,2,3,4,5};
        std::ostream_iterator<int> out(std::cout);
        std::copy(std::begin(v), std::end(v), out);
        std::cout << std::endl;
    }

    // std::back_inserter
    {
        std::vector<int> v = {1,2,3,4,5};
        std::vector<int> temp;
        auto out = std::back_inserter(temp);

        std::copy(std::begin(v), std::end(v), out);
    }
    /**
     * @brief std::back_inserterの実装: テンプレート関数の型推論を使う
     * 
     * // 出力イテレータ
     * template <class Container>
     * struct back_insert_iterator
     * {
     *      back_insert_iterator(Container& c)
     *          : c(&c) {}
     *      Container* c;
     * 
     *      // その他のコード
     * };
     * 
     * // 出力イテレータを返す関数テンプレート
     * template <class Container>
     * back_insert_iterator<Container> back_inserter(Container& c)
     * {
     *      return back_insert_iterator<Container>(c);
     * }
     */

    // C++17以前のC++ではクラスのコンストラクターからテンプレート実引数の推定ができなかった
    {
        using namespace inference_type_ns;
        // f<int>と推定
        f(0);

        // S<int>と推定
        S s(0);
    }

    // 入力イテレータ
    // cin_iterator<T>
    {
        using namespace input_iterator_ns;

        // cin_iterator<int> input, fail(true);
        // std::vector<int> buffer;

        // // 無限入力ではないか？
        // std::copy(input, fail, std::back_inserter(buffer));
        
        // print(std::begin(buffer), std::end(buffer));
        // std::cout << std::endl;

        // cin_iteratorを渡した場合、失敗状態になるまで標準出力する
        //print(input, fail);
    }


    // std::istream_iterator<T>
    // std::cinが失敗状態になるまで、標準入力から読み込み続けるイテレータ
    {
        // std::istream_iterator<int> iter(std::cin), end_iter;
        // std::vector<int> v;

        // std::copy(iter, end_iter, std::back_inserter(v));
        // input_iterator_ns::print(std::begin(v), std::end(v));
    }

    // 前方イテレータ
    // iota_iterator<T>
    // T型の整数を保持して、operator*()でリファレンスを返し、operator++でインクリメントする
    {
        using namespace forward_iterator_ns;
        std::cout << "iota_iterator" << std::endl;

        // // step 1
        // // i(0)
        // iota_iterator<int> i;
        // // iota_iterator<int>
        // iota_iterator first(0), last(10);
        // // lastをiにコピー
        // i = last;

        // // step 2
        // // 非constなオブジェクト
        // iota_iterator non_const(0);
        // // 非const版のoperator*を呼び出す
        // int value = *non_const;
        // // 変更できる
        // *non_const = 1;
        // // constなオブジェクト
        // iota_iterator immutable(0);
        // // const版のoperator*を呼び出す
        // int const_value = *immutable;
        // // 変更はできない

    
        // final step
        iota_iterator iter(0);
        *iter; // 0
        *++iter; // 1
        *++iter; // 2

        iota_iterator first(0), last(10);

        // 0123456789と出力される
        std::for_each(first, last, 
        [](auto i) { std::cout << i; });
        std::cout << std::endl;

        std::vector<int> v;
        std::copy(first, last, std::back_inserter(v));
        // vは{0,1,2,3,4,5,6,7,8,9}
    }

    // 前方リンクリスト
    {
        using namespace forward_iterator_ns;

        forward_link_list<int> list3 {3, nullptr};
        forward_link_list<int> list2 {2, &list3};
        forward_link_list<int> list1 {1, &list2};
        forward_link_list<int> list0 {0, &list1};

        // 次の要素
        *(list0.next); // list1
        // 次の次の要素
        *(list0.next->next); // list2
        // 次の次の次の要素
        *(list0.next->next->next); // list3

    }


    // リバースイテレータ
    {
        // リバースイテレータはとても便利なので、
        // std::vectorのような標準ライブラリのコンテナーには
        // 最初からネストされた型名としてリバースイテレータ::reverse_iteratorがある.
        // リバースイテレータを返すrbegin/rendもある.

        std::vector<int> v = { 1,2,3,4,5};

        // std::vector<int>::reverse_iterator
        auto first = std::rbegin(v);
        auto last = std::rend(v);

        // 54321
        std::for_each(first, last, [](auto x) { std::cout << x; });
        std::cout << std::endl;
    }

    return 0;
}