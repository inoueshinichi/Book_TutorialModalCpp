#include "../all.hpp"

// search

int main(int, char**)
{
    // search
    // search(first1, last1, first2, last2)は、[first2, last2)の範囲で
    // 示された連続した要素の並びがイテレータ[first1, last1)の範囲に存在すれば、true,
    // そうでない場合はfalseを返す.
    {
        std::vector<int> v1 = {1,2,3,4,5,6,7,8,9};
        std::vector<int> v2 = {4,5,6};

        // iter
        auto i = std::search(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2));

        std::vector<int> v3 = {1,3,5};

        // iter last
        auto last = std::search(std::begin(v1), std::end(v1), std::begin(v3), std::end(v3));

    }
}