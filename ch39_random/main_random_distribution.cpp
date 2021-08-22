#include "../all.hpp"


int main(int, char **)
{
    // 生の乱数の乱数分布へのマッピング
    {
        // 間違った乱数分布の作成方法
        {
            /**
             * @brief n = r mod |b-a| + a 
             * このやり方は、剰余のあまり 0, 1, ... a-1
             * の出現確率がa, a+1, a+2, ..., b より大きくなるので正しくない方法.
             * 1~6 -> 50%の確率で0, 1を出力する3bit整数(0-7)を使う. 
             * (0-7) % 6 だと 6, 7の整数が1, 2に割り当てられてしまう.
             */
            auto wrong_dice = [](auto &e) -> int {
                auto r = e();
                auto n = r % 6 + 1;
                return n;
            };

            int seed = 123;
            std::mt19937 e(seed);

            std::cout << "Wrong dice: " << std::endl;
            for (int i = 0; i < 6; ++i)
            {
                std::cout << wrong_dice(e) << std::endl;
            }
            std::cout << " -------------- " << std::endl;
        }


        // 正しい乱数分布の作成方法
        // この方法以外に同様に確からしい乱数分布を生成する方法はない.
        {
            int seed = 123;
            std::mt19937 e(seed);

            auto correct_dice = [&](auto &) -> int {
                // ループ実行する
                while (true)
                {
                    // 3bitの生の乱数を得る
                    auto r = e() & 0b111;
                    // 0-5なら乱数分布終わり
                    if (r <= 5)
                        return r;
                    // それ以外なら繰り返し(確率的にしか処理時間を見積もることができない)!
                }
            };

            std::cout << "Correct dice: " << std::endl;
            for (int i = 0; i < 6; ++i)
            {
                std::cout << correct_dice(e) << std::endl;
            }
            std::cout << " -------------- " << std::endl;
        }
    }


    // 分布クラス
    {
        // operator()で乱数を分布させる
        auto f = [](auto &e, auto &d) {
            return d(e); // 分布された乱数
        };

        /// 分布クラスのmin,max
        auto f2 = [](auto &d) {
            auto a = d.min();
            auto b = d.max();
        };

        // 分布クラスは、構築時の実引数を同名のメンバ関数で取得できる.
        // e.g. std::uniform_int_distribution(a, b)の場合、
        // d.a(); // 実引数
        // d.b(); // 実引数
        {
            std::uniform_int_distribution d(1, 6);
            std::cout << d.a() << std::endl;
            std::cout << d.b() << std::endl;
            std::cout << "-----" << std::endl;
        }

        // 分布クラスは内部状態のリセットができる.
        // 分布クラスは、内部的に乱数値をキャッシュしている可能性がある.
        // 乱数エンジンの状態は同じでも、分布クラスを通して出力する結果が同じである保証はないが
        // .reset()関数を使って内部状態をリセットすると同じ出力をする保証がある.
        {
            std::uniform_int_distribution a(1, 6);
            std::uniform_int_distribution b(1, 6);

            std::mt19937 x;

            // 乱数を生成
            // aは内部に乱数をキャッシュするかもしれない.
            a(x);

            // yはxと同じ内部状態を持つ
            // つまり生成する生の乱数は同じ.
            std::mt19937 y = x;

            auto r1 = a(x);
            auto r2 = b(x);

            // r1 == r2である保証はない

            // 同じ内部状態になることが保証される.
            {
                // 分布クラスの内部状態をリセット
                a.reset();
                // true
                bool retb = (a(x) == b(y));
            }

            // クラス分布の内部状態を取得/設定
            auto f3 = [](auto &d) { // auto: Distribution型
              // 内部状態の取り出し
              // Distribution::param_type型  
              auto p = d.param();

              // dと同じ内部状態を持つ分布クラス変数
              decltype(d) same_d(p);

              decltype(d) other_d;
              // 既存の変数の内部状態を変更
              other_d.param(p);
            };
        }
    }


    // 一様分布(Uniform Distribution)
    {
        // 整数の一様分布(std::uniform_int_distribution<IntType>)
        {
            // 整数型の乱数i, a<=i<=bを以下の定数離散確率関数に従って生成する.
            // P(i|a,b) = 1 / (b - a + 1)

            auto f = [](auto &engine) {
                std::uniform_int_distribution d(1, 10);
                d.a(); // 1
                d.b(); //10

                // 1から10までの範囲の乱数
                auto r = d(engine);
            };

            // 値は負数にも適用される
            std::uniform_int_distribution d(-3, 3);
            // -3, -2, -1, 0, 1, 2, 3 を1/7の確率でサンプリングする.
        }

        // 浮動小数点数の一様分布(std::uniform_real_distribution<RealType>)
        {
            // 浮動小数点の乱数x, a<=x<=bを以下の定数確率密度関数に従って分布させる.
            // p(x|a,b) = 1 / (b - a)
            // b == a のとき未定義.

            auto f = [](auto &engine) {
                std::uniform_real_distribution d(0.0, 1.0);
                d.a(); // 0.0
                d.b(); // 1.0

                // 0.0から1.0までの範囲の乱数
                auto r = d(engine);
            };

            // 浮動小数点の難しいところは、整数と違って値の範囲の状態が多い.
            // 0.0 ~ 1.0 の間には 0.01, 0.011, 0.2, 0.5 ..., 1.0と多い
            // uniform_real_distributionは指定された値の範囲で浮動小数点が表現できる
            // すべての値のうちから生成する.

        }
    }


    // ベルヌーイ分布(Bernoulli Distribution)
    {
        // ベルヌーイ試行
        {

        }

        // ベルヌーイ分布(std::bernoulli_distribution)
        {

        }
    }


    // 二項分布(std::binominal_distribution<IntType>)
    {

    }


    // 幾何分布(std::geometric_distribution)
    {

    }


    // 負の二項分布(std::negative_binominal_distribution)
    {

    }


    // ポアソン分布(poisson_distribution)
    {

    }


    // 指数分布(std::exponential_distribution<RealTyle>)
    {

    }


    // ガンマ分布(std::gamma_distribution<RealTyle>)
    {

    }


    // ウェイブル分布(std::weibull_distribution<RealType>)
    {

    }


    // 極値分布(std::extreme_value_distribution<RealTyle>)
    {
        
    }


    // 正規分布(std::normal_distribution<RealType>)
    {

    }


    // 対数正規分布(std::lognormal_distribution<RealTyle>)
    {

    }


    // カイ二乗分布(std::chi_squared_distribution<RealTyle>)
    {

    }


    // コーシー分布(std::cauchy_distribution<RealTyle>)
    {

    }


    // フィッシャーのF分布(std::fisher_f_distribution<RealTyle>)
    {

    }


    // スチューデントのt分布(std::student_t_distribution<RealType>)
    {
        
    }


    // サンプリング分布(sampling distribution)
    // サンプリング分布とは、標本から分布の特徴がわかっている場合に、
    // その特徴を指定することにより、望みの分布を作り出す分布のこと.


    // 離散分布(std::discrete_distribution<IntTyle>)
    {

    }


    // 区分定数分布(std::piecewise_constant_distribution<RealTyle>)
    {

    }


    // 区分線形分布(std::piecewise_linear_distribution<RealTyle>)
    {

    }
}