#pragma once

#include <vector>
#include <array>
#include "../comm/City.hpp"
#include "../comm/Week.hpp"
#include "../comm/Pool.hpp"

using namespace std;

namespace other
{

class OtherFunds
{
public:
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    OtherFunds(Cities& cities, Weeks& weeks, Pool& pool);
    ~OtherFunds();

    void calcSharedFunds(u32 t);

private:
    r32 calcMaxShareFunds(u32 i, u32 t);
    void calcOverbookFactor(u32 t);
    r32 calcSharedFunds(u32 i, u32 t);
    void calcSumOfLoadFactor(u32 t);

    Cities& cities_;
    Weeks& weeks_;
    Pool& pool_;
};

}