
#pragma once

#ifndef Transcript_orig
    #include "ut/mock/MockTranscript.hpp"
#else

#include "Arithmetics.hpp"

class Transcript
{
public:
    Transcript(){}
    int compute(int a, int b, int c);

private:
    Arithmetics arithmetics;
};

#endif