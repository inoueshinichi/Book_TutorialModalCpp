#include "../all.hpp"

// find/find_if


int main(int, char**) 
{
    // find/find_if
    // find(fist, last, value)は[first, last)からvalueに等しい値を見つけて、
    // そのイテレータを返す
    {
        std::vector<int> v = {1,2,3,4,5};

        // 3を指すイテレータ
        auto pos = std::find(std::begin(v), std::end(v), 3);
        std::cout << *pos << std::endl;

        // 要素が見つからない場合、lastを返す
        pos = std::find(std::begin(v), std::end(v), 0);
        if (pos != std::end(v))
        {
            std::cout << "Found."s << std::endl;
        } 
        else 
        {
            std::cout << "Not found."s << std::endl;
        }

        // イテレータがlastかどうかは実際にlastと比較すればよい.
    }

    // find
    auto find = [](auto first, auto last, auto const& value) {
        for (auto iter = first; iter != last; ++iter) {
            // 値を発見したらそのイテレータを返す
            if (*iter == value) 
                return iter;
        }
        // 値が見つからなければ、最後のイテレータを返す
        return last;
    };

    // find_if
    // find_if(first, last, pred)は[first, last)から要素を関数predに渡したときに
    // trueを返す要素へのイテレータを探すアルゴリズム.
    {
        std::vector<int> v = {1,3,5,7,9,11,13,14,15,16};

        // 偶数ならばtrueを返す
        auto is_even = [](auto value){
            return value % 2 == 0;
        };

        // 奇数ならばtrueを返す
        auto is_odd = [](auto value) {
            return value % 2 == 1;
        };

        // 最初の偶数の要素
        auto even = std::find_if(std::begin(v), std::end(v), is_even);
        // 最初の奇数の要素
        auto odd = std::find_if(std::begin(v), std::end(v), is_odd);
    }

    // find_if
    auto find_if = [](auto first, auto last, auto pred) {
        for (auto iter = first; iter != last; ++iter) {
            // predがtrueを返した最初のイテレータを返す
            if (pred(*iter))
                return iter;
        }
        return last;
    };

    // find/find_ifを使う
    {
        std::vector<int> v = {1,2,3,4,5};

        // 引数が3の場合にtrueを返す関数
        auto is_3 = [](auto x) { return x == 3; };

        // 最初に関数がtrueを返す要素へのイテレータを探すfind_if
        auto i = find_if(std::begin(v), std::end(v), is_3);

        // 最初に3と等しい要素へのイテレータを返すfind
        auto j = std::find(std::begin(v), std::end(v), 3);

        bool b = (i == j);
        std::cout << "iter i==j: " << std::boolalpha << b << std::endl;
    }

    

    /* ラムダ式のキャプチャ */

    // [=]を使うことで、関数の外側の値をコピーして使うことができる
    {
        int value = 123;

        auto f = [=] { return value; };

        std::cout << "f(): " << f() << std::endl;
    }

    // [&]を使うことで、外側の値をリファレンスで使うことができる.
    {
        int value = 123;

        auto f = [&] { return value; };
        std::cout << "f(): " << f() << std::endl;
    }


    // findはfind_ifで実装できる
    {
        auto find = [](auto first, auto last, auto value) {
            return std::find_if(first, last,
                [&](auto elem) { return value == elem; });
        };
    }
}