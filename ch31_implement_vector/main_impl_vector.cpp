#include "../all.hpp"

#include "impl_vector.hpp"

int main(int, char**)
{
    // メモリ確保と解放の起こるタイミング
    {
        std::vector<int> v;
        std::cout << std::boolalpha;
        std::cout << v.empty() << std::endl; // true

        std::vector<int> v2(100);
        std::cout << v2.size() << std::endl;

        std::vector<int> v3(100, 123);
        v[0];  // 123
        v[12]; // 123
        v[68]; // 123

        std::vector<int> v4;
        v4.resize(10);
        v4.size(); // 10
        // 減らす
        v4.resize(5);
        v4.size(); // 5

        std::vector<int> v5;
        v5.resize(3, 123); // resizeで要素数が増える場合、増えた要素の初期値も指定できる
        // v5: {123, 123, 123};

        // resizeで要素数が減る場合、末尾が削られる
        std::vector<int> v6 = {1,2,3,4,5};
        v6.resize(3);
        // v6: {1,2,3}

        // reserve(size)は少なくともsize個の要素が追加の動的メモリ確保なしで追加できるように
        // メモリを予約する
        std::vector<int> vv;
        // 少なくとも3個の要素を追加できるように動的メモリ確保
        vv.reserve(3);
        std::cout << vv.size() << std::endl; // 0
        std::cout << vv.capacity() << std::endl; // 3以上

        // 動的メモリ確保は発生しない
        vv.push_back(1);
        vv.push_back(2);
        vv.push_back(3);
        // 動的メモリ確保が発生する可能性がある
        vv.push_back(3);

        // clear()は要素数を0にする
        vv.clear();
        vv.size(); // 0
    }

    
    // デフォルトコンストラクタ
    {
        using namespace example::vector;
        vector<int> v;
        // まだ何もできない
    }

    // アロケータを取るコンストラクタ
    {
        std::allocator<int> alloc;
        // 空
        std::vector<int> v1(alloc);
        // 要素数5
        std::vecotr<int> v2(5, alloc);
        // 要素数5で初期値123
        std::vector<int> v3(5, 123, alloc);
    }

}