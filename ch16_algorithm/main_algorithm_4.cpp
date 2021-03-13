#include "../all.hpp"

// count/count_if

int main(int, char**)
{
    // count
    // count(first, last, value)は[first, last)の範囲のイテレータiから
    // *i == valueになるイテレータiの数を数える
    {
        std::vector<int> v = {1,2,1,1,3,3};

        // 3
        auto a = std::count(std::begin(v), std::end(v), 1);
        // 1
        auto b = std::count(std::begin(v), std::end(v), 2);
        // 2
        auto c = std::count(std::begin(v), std::end(v), 2);
    }

    // count
    auto count = [](auto first, auto last, auto value) 
    {
        auto counter = 0u;
        for (auto i = first; i != last; ++i) {
            if (*i == value)
                ++counter;
        }
        return counter;
    };

    // count_if
    {
        std::vector<int> v = {1,2,1,1,3,3};
        
        // 奇数の数：5
        auto a = std::count_if(std::begin(v), std::end(v),
            [](auto x) { return x % 2 == 1; });
        
        // 偶数の数:1
        auto b = std::count_if(std::begin(v), std::end(v),
            [](auto x) { return x % 2 == 0; });
        
        // 2以上の数:3
        auto c = std::count_if(std::begin(v), std::end(v),
            [](auto x) { return x >= 2; });
    }

    auto count_if = [](auto first, auto last, auto pred) {
        auto counter = 0u;
        for (auto i = first; i != last; ++i) {
            if (pred(*i) != true)
                ++counter;
        }
        return counter;
    };
}