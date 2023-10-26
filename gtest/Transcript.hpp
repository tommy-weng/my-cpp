
#pragma once

#ifndef Transcript_orig
    #include "ut/mock/MockTranscript.hpp"
#else

#include "Arithmetics.hpp"

class Transcript
{
public:
    Transcript(){}
    int compute();

private:
    int x{100};
    int y{98};
    int z{97};
    Arithmetics arithmetics;
};

#endif