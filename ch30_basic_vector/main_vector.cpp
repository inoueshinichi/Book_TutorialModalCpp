#include "../all.hpp"
#include "vector.hpp"

int main(int, char**)
{
    // vectorに関するネストされた型名
    {
        using vec = std::vector<int>;
        vec v = {1,2,3};

        vec::value_type val = v[0];
        vec::iterator i = v.begin();
    }

    // vectorの容量確認
    {
        std::vector<int> v;
        // true, 要素数0
        bool a = v.empty();
        v.push_back(0);
        // false, 要素数非ゼロ
        bool b = v.empty();
        // 1, 現在の要素数
        auto s = v.size();
        // 実装依存、追加の動的メモリーを確保せずに格納できる要素の最大数
        auto c = v.capacity();
    }

    // 要素アクセス
    {
        std::vector<int> v = {1,2,3,4,5};
        v[1]; //2
        v[2]; //3

        // at(i)はoperator[](i)と同じだが、範囲外のインデックスを指定した場合、
        // std::out_of_rangeが例外として投げられる
        try {
            // 有効なインデックスはv[0]からv[4]まで
            std::vector<int> v = {1,2,3,4,5};
            v.at(0) = 0; // OK
            v.at(3) = 0; // OK
            v.at(5) = 0; // エラー
        } catch(std::out_of_range e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    // front/back
    {
        std::vector<int> v = {1,2,3,4,5};
        v.front(); // 1
        v.back(); // 5
    }

    // data
    {
        std::vector<int> v = {1,2,3,4,5};
        int* ptr = v.data();
        std::cout << *ptr << std::endl; // 1
    }
}