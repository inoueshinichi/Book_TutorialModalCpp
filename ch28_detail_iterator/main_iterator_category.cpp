#include "../all.hpp"

#include "iterator_category.hpp"


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

    return 0;
}