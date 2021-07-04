#include "../all.hpp"


int main(int, char**)
{
    // ムーブ
    {
        std::vector<int> v;

        std::vector<int> w = {1,2,3,4,5};
        // ムーブ
        v = std::move(w);
        // この後wは使えない

        std::for_each(std::begin(v), std::end(v),
            [](auto x)
            {
                std::cout << x;
            }
        );
        std::cout << std::endl;

        // 要素数5
        w.resize(5);
        // 妥当に使える
        w[0] = 1;
    }

    // ムーブの中身
    {
        // 基本型オブジェクトのムーブ＝単なるコピー
        int a = 123;
        // コピー
        int b = a;
        // ムーブ
        int c = std::move(a);
        // aは123
        std::cout << "a=" << a << std::endl;

        // 生のポインターのムーブも単なるコピーとなる
        int object{421};
        int* source = &object;
        int* destination = std::move(source);
        std::cout << "*destination=" << *destination << std::endl;
    }

    return 0;
}