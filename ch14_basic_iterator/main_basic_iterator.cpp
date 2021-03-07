#include "../all.hpp"


int main(int, char**) {

    // 準備
    {
        std::vector<int> v = {1,2,3,4,5};
        int x = v.at(2); // 3
        v.at(2) = 0;
        // vは{1,2,0,4,5}
    }
    
    // イテレータの取得方法
    {
        std::vector<int> v = {1,2,3,4,5};
        auto i = std::begin(v);
    }

    // イテレータの参照する要素に対する読み書き
    {
        std::vector<int> v = {1,2,3,4,5};

        auto i = std::begin(v);

        int x = *i; // 1

        *i = 0;
        // vは{0,2,3,4,5}
    }
}