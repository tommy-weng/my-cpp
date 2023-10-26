#pragma once

#ifndef arithmetics_orig
    #include "ut/mock/MockArithmetics.hpp"
#else

class Arithmetics
{
public:
    int plus(int a, int b);
    int minus(int a, int b);
};
#endif