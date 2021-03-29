/**
 * @file main_pointer_naive.cpp
 * @author your name (you@domain.com)
 * @brief ポインターの内部実装
 * @version 0.1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../all.hpp"

#define ToStr(T) #T

template <class T>
void print_size()
{
    std::printf("sizeof(%s): %lu\n", ToStr(T), sizeof(T));
}


int main(int, char**)
{
    // ポインターのサイズ
    {
        print_size<int*>();
        print_size<double*>();
        print_size<int**>();
    }
    return 0;
}
