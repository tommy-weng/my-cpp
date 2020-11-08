#pragma once

#include <vector>
#include <array>
#include "../comm/FundsBase.hpp"
#include "../comm/City.hpp"
#include "../comm/Week.hpp"
#include "../comm/Pool.hpp"

using namespace std;

namespace surgicalMask
{

class SurgicalMask : public comm::FundsBase
{
public:
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    SurgicalMask(Cities& cities, Weeks& weeks, Pool& pool);
    ~SurgicalMask();
private:
    r32 calcOverbookFactor(u32 i, u32 t);
    r32 calcDedicatedFunds(u32 i, u32 t);
    r32 calcIdealSharedFunds(u32 i, u32 t);
    r32 calcSharedFunds(u32 i , u32 t);
    void calcPoolR(u32 t);

    Cities& cities_;
    Weeks& weeks_;
    Pool& pool_;
};

}