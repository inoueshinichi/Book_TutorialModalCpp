#include "../all.hpp"

#include "pointer_and_iterator.hpp"

int main(int,char**)
{
    // ポインター＝イテレータ
    example::array<float, 10> array;
    for (int i = 0; i < 10; ++i) array.storage[i] = i;

    float* first = array.begin();
    float* last = array.end();
    std::cout << "*first: " << *first << std::endl;
    std::cout << "*last: " << *last << std::endl;

    example::array_iterator<decltype(array)> iter1(array.begin());
    example::array_iterator<decltype(array)> iter2(array.end() - 1);
    std::cout << "iter1: " << *iter1 << std::endl;
    std::cout << "iter2: " << *iter2 << std::endl;

    return 0;
}