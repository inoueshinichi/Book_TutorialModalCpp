#include "../all.hpp"

// 乱数エンジン
template <typename Engine>
void f(Engine &e)
{
    // 最小値
    auto a = e.min();
    // 最大値
    auto b = e.max();
    // 乱数
    auto r1 = e();
    // 次の乱数
    auto r2 = e();
}

// 乱数分布
template <typename Engine, typename Distribution>
void f(Engine &e, Distribution d)
{
    // 乱数
    auto r1 = d(e);
    // 次の乱数
    auto r2 = d(e);
    // 次の乱数
    auto r3 = d(e);
}

int main(int, char **)
{
    // 疑似乱数
    {
        // 線形結合法(Linear congruential generator)
        // x_(n+1) = (a * x_(n) + e) mod m
        {
            // a = 3, e = 5, m = 2^sizeof(std::uint32)*8の場合で、
            // x_0 = 0のとき,
            // ...

            // 中でどのように乱数が生成されているかわからなければ、
            // 外部からは乱数のように見える。これが疑似乱数の考え方
        }
    }


    // 乱数エンジン
    {
        // std::default_random_engine 標準ライブラリのデフォルトの乱数エンジン
        {
            std::cout << "----- std::default_random_engine -----" << std::endl;
            std::default_random_engine e;

            for (int i = 0; i != 10; ++i)
            {
                std::cout << e() << std::endl;
            }
            std::cout << "---------------------------------------" << std::endl;
        }

        // std::mt19937 メルセンヌ・ツイスターエンジン
        {
            std::cout << "----- std::mt19937 -----" << std::endl;
            std::mt19937 e;

            for (int i = 0; i != 10; ++i)
            {
                std::cout << e() << std::endl; // 生の乱数は、uint32 or uint64の範囲
            }
            std::cout << "---------------------------------------" << std::endl;
        }
    }


    // 乱数分布
    {
        std::cout << "----- 乱数分布 -----" << std::endl;

        // 乱数エンジン
        std::mt19937 e;

        // 乱数分布
        // a <= r <= b
        std::uniform_int_distribution<int> d(1, 6);

        for (int i = 0; i < 10; ++i)
        {
            std::cout << d(e) << " "sv;
        }
        std::cout << std::endl;

        auto a = d(e); // 1回目
        auto b = d(e); // 2回目
        int result = a - b; // 結果
        std::cout << result << std::endl;

        std::cout << "---------------------------------------" << std::endl;
    }


    // シード
    {
        {
            std::seed_seq s {123};
            std::mt19937 e(s);
            // std::cout << e() << std::endl;

            // 乱数を生成
            // 内部状態が変わる
            auto r1 = e();
            // シード値を設定
            e.seed(s);
            // 乱数を生成
            auto r2 = e();

            // 同じシード値による乱数は同じ値になる
            std::cout << std::boolalpha << "r1 == r2: " << (r1 == r2);
            std::cout << std::endl;
            

            // std::seed_seqには複数の符号なし32bit整数を指定できる
            // = {n1, n2, n3, ...}; や (first, last)のようにイテレータ形式でもoK
            std::seed_seq s1 = {1,2,3,4,5};

            std::vector<std::uint32_t> v = {1,2,3,4,5};
            std::seed_seq s2(std::begin(v), std::end(v));

            // 乱数エンジンをコピーすると内部状態もコピーされる.
            // つまり、乱数を保存することができる。
            std::mt19937 e1;
            // 2回乱数を生成
            e1(); e1();
            // コピー、内部状態もコピーされる
            std::mt19937 e2 = e1;
            // true
            bool b1 = (e1() == e2());
            // true
            bool b2 = (e1() == e2());
        }


        // 予測不可能な乱数
        {
            std::cout << "----- std::random_device -----" << std::endl;

            // 本当に予測不可能な乱数を生成するには、ハードウェアの支援が必要.
            std::random_device rd;
            for (int i = 0; i != 10; ++i) 
            {
                std::cout << rd() << std::endl;
            }

            // std::random_deviceを使えば、std::seed_seqを予測不可能な値で初期化できる.
            std::seed_seq s = { rd(), rd(), rd() };
            // シード値を指定して初期化
            std::mt19937 e(s);

            std::cout << "---------------------------------------" << std::endl;
        }


        // 十分なシード値の量
        {
            // std::seed_seqの初期化では、32bit符号なし整数をいくつでも指定できる
            std::random_device rd;
            std::seed_seq s = { rd(), rd(), rd(), rd(), rd() /*...*/};

            // 現在、C++標準規格には、乱数エンジンを適切に初期化するかんたんな方法がない。
            // 一つの目安として、乱数エンジンのオブジェクトサイズを使う
            std::cout << "sizeof(std::mt19937): " << sizeof(std::mt19937) << std::endl;

            // 2504 / sizeof(unsigned int) = 624 ぐらいを渡せば、安牌だが。。。多すぎ

            std::cout << "sizeof(std::default_random_engine): " << sizeof(std::default_random_engine) << std::endl;
        }
    }
}