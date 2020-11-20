#ifndef __ITER_HPP__
#define __ITER_HPP__
#include "all.hpp"

void test_iter()
{
    std::vector<int> v = {1, 2, 3, 4, 5};

    
    auto output_all = [](auto first, auto last)
    {
        for (auto iter = first; iter != last; ++iter)
        {
            std::cout << *iter << std::endl;
        }
    };
    output_all(std::begin(v), std::end(v));
}


#endif