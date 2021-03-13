#include "../all.hpp"

// equal

int main(int, char**) 
{
    // equal
    // equal(first1, last1, first2, last2)は[first1, last1)と[first2, last2)が
    // 等しい場合にtrueを返す.
    // 等しいとは、要素の数が同じで、各要素がそれぞれ等しい場合を指す
    {
        std::vector<int> a = {1,2,3,4,5};
        // aと等しい
        std::vector<int> b = {1,2,3,4,5};
        // aと等しくない
        std::vector<int> c = {1,2,3,4,5,6};
        // aと等しくない
        std::vector<int> d = {1,2,2,4,6};

        // true
        bool ab = std::equal(
            std::begin(a), std::end(a),
            std::begin(b), std::end(b)
        );

        // false
        bool ac = std::equal(
            std::begin(a), std::end(a),
            std::begin(c), std::end(c)
        );

        // false
        bool ad = std::equal(
            std::begin(a), std::end(a),
            std::begin(d), std::end(d)
        );
    }

    // 実装は、まず要素数を比較し、等しくなければfalseを返す.
    // 次に各要素を1つずつ比較し、途中で等しくない要素が見つかれば、
    // falseを、最後まで各要素が等しければtrueを返す.
    {
        // イテレータ範囲[first, last)の要素数はlast-firstで取得できる.

        std::vector<int> v = {1,2,3,4,5};

        // 最初の要素
        auto first = std::begin(v);
        // 最後の1つ次の要素
        auto last = std::end(v);

        // 要素数：5
        auto size = last - first;

        // 最初の次の要素
        auto next = first + 1;

        // 4
        auto size_from_next = last - next;
    }

    // last-first = std::distance(first, last)
    auto distance = [](auto first, auto last) {
        return last - first;
    };

    {
        std::vector<int> v = {1,2,3,4,5};

        // 最初の要素
        auto first = std::begin(v);
        // 最後の1つ次の要素
        auto last = std::end(v);

        // 要素数：5
        auto size = std::distance(first, last);

        // 最初の次の要素
        // auto next = first + 1;

        // 4
        auto size_from_next = std::distance(first + 1, last);
    }

    // 効率がよくないequalの実装
    auto equal = [](auto first1, auto last1, auto first2, auto last2)
    {
        // 要素数が等しいことを確認
        auto size1 = std::distance(first1, last1);
        auto size2 = std::distance(first2, last2);

        if (size1 != size2)
        {
            // 要素が等しくなかった
            return false;
        }

        // 各要素が等しいことを確認
        for (auto i = first1, j = first2; i != last1; ++i, ++j)
        {
            if (*i != *j)
            {
                // 等しくない要素があった
                return false;
            }
        }

        // 各要素がすべて等しかった
        return true;
    };

    // equal(first1, last1, first2, last2, pred)
    {
        std::vector<double> v = {1.3, 2.2, 3.0, 4.9, 5.7};
        std::vector<double> w = {1.9, 2.4, 3.8, 4.5, 5.0};

        // 小数点以下は誤差として切り捨てる比較
        auto comp = [](auto a, auto b) {
            return std::floor(a) == std::floor(b);
        };

        bool b = std::equal(
            std::begin(v), std::end(v),
            std::begin(w), std::end(w),
            comp
        );
    }
}