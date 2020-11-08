#include "FundsBase.hpp"

namespace comm
{

FundsBase::FundsBase()
{

}

FundsBase::~FundsBase()
{
}

void FundsBase::calcSharedFunds(u32 t)
{
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        calcOverbookFactor(i, t);
    }
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        calcDedicatedFunds(i, t);
    }
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        calcIdealSharedFunds(i, t); 
    }
    calcPoolR(t);
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        calcSharedFunds(i , t);
    }
}

}