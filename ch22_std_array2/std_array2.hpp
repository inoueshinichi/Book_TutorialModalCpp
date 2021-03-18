#pragma once
#include "../all.hpp"

///////////////////////////////////
// 配列std::arrayを段階を追って実装する
///////////////////////////////////

struct array_int_3 {
    int m0;
    int m1;
    int m2;

    int& operator[](std::size_t i) {
        switch(i) {
            case 0:
                return m0;
            case 1:
                return m1;
            case 2:
                return m2;
            default:
                std::abort(); // 矯正終了
        }
    }
};







