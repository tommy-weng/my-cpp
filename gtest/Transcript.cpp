#include "Transcript.hpp"

int Transcript::compute(int a, int b, int c)
{
    int x = arithmetics.plus(a, b);
    return arithmetics.minus(x, c);
}