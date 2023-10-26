#include "Transcript.hpp"

int Transcript::compute()
{
    int k = arithmetics.plus(x, y);
    return arithmetics.minus(k, z);
}