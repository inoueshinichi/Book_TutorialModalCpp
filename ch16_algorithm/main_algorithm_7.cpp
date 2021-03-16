#include "../all.hpp"

int main(int, char**)
{
    // copy
    // copy(first, last, result)は、[first, last)の範囲の値を先頭から順番に
    // イテレータresultに書き込んでいくアルゴリズム.
    {
        std::vector<int> source = {1,2,3,4,5};
        // 要素数5のvector
        std::vector<int> destination(5);

        std::copy(std::begin(source), std::end(source), std::begin(destination));
        // destinationの中身は{1,2,3,4,5}
    }

    // イテレータresultは、イテレータ[first, last)の範囲の要素数をコピーできるだけの要素数の範囲を
    // 参照していなければならない.
    {
        std::vector<int> source = {1,2,3,4,5};
        // 要素数3のvector
        std::vector<int> destination(3);

        // エラー Segmentation fault
        // std::copy(std::begin(source), std::end(source), std::begin(destination));
    }

    // copy(first, last, result)の戻り値は、[first, last)の要素数だけ進めたイテレータresult
    // result + (last - first)
    {
        std::vector<int> source = {1,2,3,4,5};
        std::vector<int> destination(5);

        auto first = std::begin(source);
        auto last = std::end(source);
        auto result = std::begin(destination);

        auto returned = std::copy(first, last, result);

        // true
        bool b = (returned == (result + (last - first)));
        std::cout << std::boolalpha << b << std::endl;
    }

    // copyには[first, last)の範囲がresultから続く範囲とオーバーラップしてはいけないという
    // 制約がある。 オーバーラップというのは、コピー元とコピー先の範囲がかぶっているということ.
    // オーバーラップが発生していた場合、未定義動作
    {
        std::vector<int> v = {1,2,3};

        // [first, last)とresultがオーバーラップしている
        std::copy(std::begin(v), std::end(v), std::begin(v));
    }

    // 実装例
    auto copy = [](auto first, auto last, auto result) {
        for (auto iter = first; iter != last; ++iter, ++result) {
            *result = *iter;
        }
        return result;
    };


    // transform
    // transform(first, last, result, op)は、copyへのコピーが*result = *iterではなく、
    // *result = op(*iter)になる. opは関数. 動作はcopyとほぼ同じ.
    auto transform = [](auto first, auto last, auto result, auto op) {
        for (auto iter = first; iter != last; ++iter, ++result) {
            *result = op(*iter);
        }
        return result;
    };

    // copyと似ているが、値をコピーする際に関数を適用できる
    {
        std::vector<int> a = {1,2,3,4,5};

        std::vector<int> b(5);
        std::transform(std::begin(a), std::end(a), std::begin(b), [](auto x) { return 2 * x; });
        // bは{2,4,6,8,10}

        std::vector<int> c(5);
        std::transform(std::begin(a), std::end(a), std::begin(c), [](auto x) { return x % 3; });
        // cは{1,2,0,1,2}

        std::vector<bool> d(5);
        std::transform(std::begin(a), std::end(a), std::begin(d), [](auto x) { return x < 3; });
        // dは{true,true,false,false,false}
    }
}