#include "../all.hpp"

int main(int, char**)
{
    // all_of
    // all_of(first, last, pred). [first, last)に対して、pred(*iter)がすべて
    // trueならばtrue, それ以外はfalseを返す
    {
        // 要素がすべて偶数か調べる関数
        auto is_all_of_even = [](auto first, auto last) {
            return std::all_of(first, last, [](auto value) { return value % 2 == 0; });
        };

        // 要素がすべて100以下かどうか調べる関数
        auto is_all_of_le_100 = [](auto first, auto last) {
            return std::all_of(first, last, [](auto value) { return value <= 100; });
        };
    }

    auto all_of = [](auto first, auto last, auto pred) -> bool {
        for (auto iter = first; iter != last; ++iter)
        {
            if (pred(*iter) == false)
                return false;
        }
        return true;
    };

    // 要素が空の場合、all_ofはtrueを返す
    {
        std::vector<int> v;
        std::cout << std::boolalpha << all_of(std::begin(v), std::end(v), [](auto x) { return false; }) << std::endl;
    }


    // any_of
    // any_of(first, last, pred). [first, last)に対して、pred(*iter)が一つでも
    // trueならばtrue, すべてfalseならfalseを返す.
    {
        
    }
}