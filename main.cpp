#include <iostream>
#include "string_internationalization.hpp"

int main()
{
    stdstr::test();
    std::cout << std::endl;

    utf8::test();
    std::cout << std::endl;

    gb2312::test();
    std::cout << std::endl;

    return 0;
}
