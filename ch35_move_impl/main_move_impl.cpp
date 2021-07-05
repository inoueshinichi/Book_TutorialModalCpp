#include "../all.hpp"

namespace example1
{
    struct X
    {
        // コピーコンストラクタ
        X(const X &);
        // コピー代入演算子
        X &operator=(const X &);

        // ムーブコンストラクタ
        X(X &&);
        // ムーブ代入演算子
        X &operator=(const X &&);

        /**
         * @brief rvalueリファレンスで束縛できる値
         * 1) 無名の一時オブジェクト(prvalue)
         * 2) 明示的にrvalueリファレンスにキャストされたオブジェクト(xvalue)
         */
    };

    void f(const int &)
    {
        std::cout << "lvalue" << std::endl;
    }

    void f(int &&)
    {
        std::cout << "rvalue" << std::endl;
    }

    std::vector<int> f()
    {
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        
        // ムーブされる可能性がある(RVO)
        // たいていのコンパイラで最適化される
        return v;
    }
}

namespace example2
{
    template <typename T>
    class dynamic_array
    {
    private:
        T *first;
        T *last;
    public:
        dynamic_array(std::size_t size = 0)
            : first(new T[size])
            , last(first + size) {}
        
        ~dynamic_array() { delete[] first; }

        // ムーブコンストラクタ
        dynamic_array(dynamic_array &&r)
            // ムーブ先への所有権の移動
            : first(r.first)
            , last(r.last)
        {
            // ムーブ元の所有権の放棄
            r.first = nullptr;
            r.last = nullptr;
        }

        // ムーブ代入演算子
        
    };
}


int main(int, char**) 
{
    // rvalueとlvalueの判断
    {
        using namespace example1;

        int object {};

        f(object); // lvalue
        f(object + object); // rvalue
        // f([](){ return object; }()); // rvalue
        f(std::move(object)); // rvalue
    }

    // ムーブの実装
    {
        using namespace example2;

        dynamic_array<int> source(10);
        // ムーブ
        dynamic_array<int> destination = std::move(source);

        /**
         * @brief ムーブコンストラクタで実装する必要がある処理
         * 1) ムーブ先へ所有権の移動
         * 2) ムーブ元の所有権の破棄
         */

        /**
         * @brief ムーブ代入演算子で実装する必要のある処理
         * 1) ムーブ先の所有権の解放
         * 2) ムーブ先への所有権の移動
         * 3) ムーブ元の所有権の破棄
         */
    }
}