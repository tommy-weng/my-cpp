#pragma once

#include "../utils/defs.hpp"

namespace comm
{
class FundsBase
{

public:
    FundsBase();
    ~FundsBase();

    void calcSharedFunds(u32 t);

private:
    virtual r32 calcOverbookFactor(u32 i, u32 t) = 0;
    virtual r32 calcDedicatedFunds(u32 i, u32 t) = 0;
    virtual r32 calcIdealSharedFunds(u32 i, u32 t) = 0;
    virtual r32 calcSharedFunds(u32 i , u32 t) = 0;
    virtual void calcPoolR(u32 t) = 0;

};

}