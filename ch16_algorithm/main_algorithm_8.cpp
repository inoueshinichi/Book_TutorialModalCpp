#include "../all.hpp"

int main(int, char**)
{
    // replace
    // replace(fist, last, old_value, new_value)はイテレータ[first, last)の範囲の
    // イテレータが指す要素の値がold_valueに等しいものをnew_valueに置換する関数.
    {
        std::vector<int> a = {1,2,3,3,4,5,3,4,5};
        
        std::replace(std::begin(a), std::end(a), 3, 0);
        // aは{1,2,0,0,4,5,0,4,5}
    }

    // replace
    auto replace = [](auto first, auto last, auto old_value, auto new_value) {
        for (auto iter = first; first != last; ++iter) {
            if (*iter == old_value) {
                *iter = new_value;
            }
        }
    };


    // fill
    // fill(first, last, value)は、イテレータ[first, last)の範囲の
    // イテレータが参照する要素にvalueを代入する.
    {
        std::vector<int> v = {1,2,3,4,5};
        std::fill(std::begin(v), std::end(v), 0);
        // vは{0,0,0,0,0}
    }

    // fill_n
    // fill_n(first, n, value)は、イテレータ[first, first+n)の範囲のイテレータが参照する
    // 要素にvalueを代入する. (元のサイズを超えてはいけない)
    {
        std::vector<int> v = {1,2,3,4,5};
        std::fill_n(std::begin(v), 3, 0);
        // vは{0,0,0,4,5}
    }

    // fill_n
    auto fill_n = [](auto first, auto last, auto n, auto value) {
        for (auto i = 0; i != n; ++i, ++first) {
            *first = value;
        }
    };


    // generate
    // fillに似ているが、関数genの戻り値を代入する.
    // generate(first, last, gen)は、イテレータ[first, last)の範囲のイテレータが参照する
    // 要素にgen()を代入する.
    {
        std::cout << "RAND_MAX: " << RAND_MAX << std::endl;
        std::vector<int> v = {1,2,3,4,5};
        auto gen_random = []() { return rand(); };
        std::generate(std::begin(v), std::end(v), gen_random);
        for (const auto& elem : v) {
            std::cout << elem << std::endl;
        }
    }

    // generate_n
    // fill_nのgenerate版
    {
        std::cout << "RAND_MAX: " << RAND_MAX << std::endl;
        std::vector<int> v = {1,2,3,4,5};
        auto gen_random = []() { return rand(); };
        std::generate_n(std::begin(v), 2, gen_random);
        for (const auto& elem : v) {
            std::cout << elem << std::endl;
        }
    }

    // generate
    auto generate = [](auto first, auto last, auto gen) {
        for (auto iter = first; iter != last; ++iter) {
            *iter = gen();
        }
    };

    // generate_n
    auto generate_n = [](auto first, auto n, auto gen) {
        for (auto i = 0u; i != n; ++i, ++first) {
            *first = gen();
        }
    };
}