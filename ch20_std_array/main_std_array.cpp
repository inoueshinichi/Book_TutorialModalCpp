#include "../all.hpp"

// 常にゼロを返すクラス
// 何を書き込んでもゼロを返す
struct null_array {
    int dummy;
    // 引数は無視
    int& operator[](std::size_t) {
        dummy = 0;
        return dummy;
    }
};

int main(int,char**)
{
    {
        // int型を10個保持するクラス
        std::array<int, 10> a;

        // 0番目の値に1
        a.at(0) = 1;
        
        auto iter = std::begin(a);
    }
    
    {
        std::array<int, 10> a;

        // どちらも0番目の要素に1を代入
        a.at(0) = 1;
        a[0] = 1;

        // どちらも0番目の要素を標準出力
        std::cout << a.at(0) << "\n";
        std::cout << a[0] << "\n";
    }

    // at(i)と[i]の違いは、要素の範囲外にアクセスしたときの挙動
    {
        // 10個の要素を持つ
        // 0番目から9番目までが妥当な範囲
        std::array<int, 10> a;

        // // エラー処理が行われる
        // // プログラムは終了する
        // a.at(10) = 0; // terminating with uncaught exception of type std::out_of_range: array::at

        // // 未定義動作
        // a[10] = 0;
    }

    // 常にゼロを返すoperator[i]
    {
        null_array na;

        // 0
        std::cout << na[0] << std::endl;

        // 0
        std::cout << na[999] << std::endl;

        na[100] = 0;
        // 0
        std::cout << na[100] << std::endl;
    }
}