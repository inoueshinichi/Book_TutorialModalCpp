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
     * // 出力イテレータを返すテンプレート関数
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

    return 0;
}