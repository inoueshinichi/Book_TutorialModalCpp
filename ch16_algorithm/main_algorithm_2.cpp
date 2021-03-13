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
        std::vector<int> v = {1,2,3,4,5};

        // 要素に1つでも3が含まれているか?
        // true
        bool has_3 = std::any_of(std::begin(v), std::end(v),
                            [](auto x) { return x == 3; });
        std::cout << std::boolalpha << "has_3: " << has_3 << std::endl;

        // 要素に１つでも10が含まれているか？
        // false
        bool has_10 = std::any_of(std::begin(v), std::end(v),
                            [](auto x) { return x == 10; });
        std::cout << std::boolalpha << "has_10 : " << has_10 << std::endl;
    }

    // any_of
    auto any_of = [](auto first, auto last, auto pred) {
        for (auto iter = first; iter != last; ++iter) {
            if (pred(*iter))
                return true;
        }
        return false;
    };

    // none_of
    // none_of(first, last, pred).[first, last)の間に対して、pred(*iter)がすべて、
    // falseならtrueを返す.
    {
        std::vector<int> v = {1,2,3,4,5};

        // 値は100か?
        auto is_100 = [](auto x) { return x == 100; };
        bool b = std::none_of(std::begin(v), std::end(v), is_100);
        std::cout << std::boolalpha << "is_100 : " << b << std::endl;
    }

    // none_of
    auto none_of = [](auto first, auto last, auto pred) {
        for (auto iter = first; iter != last; ++iter) {
            if (pred(*iter))
                return false;
        }
        return true;
    };

    
}