#include "../all.hpp"

int main(int, char**)
{
    // remove
    // remove(fist, last, value)は、イテレータ[first,last)の範囲の参照する要素から
    // 値valueに等しいものを取り除く. そして、新しい終端イテレータを返す.

    // 実際には、アルゴリズムremoveが値を取り除くわけでなない.
    //　該当する値valueを後続の値で上書きする.
    // 1,2,3 -> 1,3,?
    // 3番目の値?は、何が入っているかわからない。未保証値
    // auto last2 = remove(first, last, value)
    // [first, last2)
    // 注意) removeを呼び出しても、元のコンテナの要素数が変わることはない.
    // removeは、コンテナの要素の値を変更するだけ.
    {
        std::vector<int> v = {1,2,3};

        auto last = std::remove(std::begin(v), std::end(v), 2);
        // vは{1,3,?}

        // "13?"
        std::for_each(std::begin(v), last, [](auto x) { std::cout << x; });
        std::cout << std::endl;

        std::vector<int> w = {1,2,2,3,2,2,4};
        auto last2 = std::remove(std::begin(w), std::end(w), 2);
        // wは{1,3,4,?,?,?,?}

        // "134????"
        std::for_each(std::begin(w), last2, [](auto x) { std::cout << x; });
        std::cout << std::endl;
    }


    // remove_if
    // remove_if(first, last, pred)は、[first, last)の範囲の要素を指すイテレータiのうち、
    // 関数predに渡した結果、pred(*i)がtrueになる要素を取り除くアルゴリズム.
    {
        // 偶数の場合true, 奇数の場合falseを返す関数
        auto is_even = [](auto x) { return x % 2 == 0; };

        std::vector<int> v = {1,2,3,4,5,6,7,8,9};
        // 偶数を取り除く
        auto last = std::remove_if(std::begin(v), std::end(v), is_even);
        std::for_each(std::begin(v), last, [](auto x) { std::cout << x; });
        std::cout << std::endl;
        // vは{1,3,5,7,9}
    }

    // remove_if
    auto remove_if = [](auto first, auto last, auto pred) {
        // removeする最初の要素
        auto removing = std::find_if(first, last, pred);
        
        // removeする要素がなかった
        if (removing == last) {
            return last;
        }

        // removeする要素の次の要素
        auto remaining = removing;
        ++remaining;

        // removeする要素に上書きする
        for (; remaining != last; ++remaining) {
            if (pred(*remaining) == false) {
                *removing = *remaining;
                ++removing;
            }
        }
        // 新しい終端イテレータ
        return removing;
    };
}