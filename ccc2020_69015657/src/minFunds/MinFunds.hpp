#pragma once

#include <vector>
#include <array>
#include "../comm/City.hpp"
#include "../comm/Week.hpp"
#include "../comm/Pool.hpp"

using namespace std;

namespace minFunds
{

class MinFunds
{
public:
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    MinFunds(Cities& cities, Weeks& weeks, Pool& pool);
    ~MinFunds();


    void calcMinFunds(u32 t);

private:
    r32 calcMinFunds(u32 i, u32 t);
    void calcSumOfMaxFunds(u32 t);
    Cities& cities_;
    Weeks& weeks_;
    Pool& pool_;
};

}
