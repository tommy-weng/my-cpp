#pragma once

#include "../utils/defs.hpp"

namespace comm
{

class Pool
{
public:
    Pool();
    ~Pool();

    r32& poolR()
    {
        return poolR_;
    }
    const r32 poolR() const
    {
        return poolR_;
    }

    r32& poolMinRate()
    {
        return poolMinRate_;
    }

    const r32 poolMinRate() const
    {
        return poolMinRate_;
    }

    const r32 overbookFactorSM = 1.5;
    const r32 overbookFactorDis = 1.2;
    const r32 overbookFactorOhter = 1.5;

private:
    r32 poolR_;
    r32 poolMinRate_;
};

}

