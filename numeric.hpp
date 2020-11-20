#ifndef __NUMERIC_HPP__
#define __NUMERIC_HPP__
#include "all.hpp"

void test_numeric()
{
    // range
    std::cout << std::numeric_limits<int>::min() << std::endl;
    std::cout << std::numeric_limits<int>::max() << std::endl;
    
    // infinity
    std::cout << std::numeric_limits<float>::infinity() << std::endl;
    std::cout << -std::numeric_limits<float>::infinity() << std::endl;

    // nan
    std::cout << std::numeric_limits<float>::quiet_NaN() << std::endl;

    // 有効桁数
    std::cout << "float: "s << std::numeric_limits<float>::digits10 << std::endl;
    std::cout << "double: "s << std::numeric_limits<double>::digits10 << std::endl;
    std::cout << "long double: "s << std::numeric_limits<long double>::digits10 << std::endl;

    // max_digit
    std::cout << "float: "s << std::numeric_limits<float>::max_digits10 << std::endl;
    std::cout << "double: "s << std::numeric_limits<double>::max_digits10 << std::endl;
    std::cout << "long double: "s << std::numeric_limits<long double>::max_digits10 << std::endl;


    // epsilon
    std::cout << "float: "s << std::numeric_limits<float>::epsilon() << std::endl;
    std::cout << "double: "s << std::numeric_limits<double>::epsilon() << std::endl;
    std::cout << "long double: "s << std::numeric_limits<long double>::epsilon() << std::endl;    
}


#endif
