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
        
    }


    // 一様分布(Uniform Distribution)
    {
        // 整数の一様分布(std::uniform_int_distribution<IntType>)
        {

        }

        // 浮動小数点数の一様分布(std::uniform_real_distribution<RealType>)
        {

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