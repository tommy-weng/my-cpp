#include <cmath>
#include "MinFunds.hpp"
#include "../logger/Logger.hpp"

namespace minFunds
{

MinFunds::MinFunds(Cities& cities, Weeks& weeks, Pool& pool)
:cities_(cities),
weeks_(weeks),
pool_(pool)
{
}

MinFunds::~MinFunds()
{
}

void MinFunds:: calcSumOfMaxFunds(u32 t)
{
    for (u32 city = 0; city < MAX_CITIES; city++)
    {
        weeks_.at(t).sumOfMaxR() += cities_[t][city].config().maxR_;
    }
    lg.dbg() << "MinFunds::calcSumOfMaxFunds:t=" << t << ",sumOfMaxR=" << weeks_.at(t).sumOfMaxR() << endl;
}

r32 MinFunds::calcMinFunds(u32 i, u32 t)
{
    r32 sumOfMaxR{weeks_.at(t).sumOfMaxR()};
    r32 maxR{cities_[t][i].config().maxR_};
    r32 minR{min(ceil((pool_.poolR() * pool_.poolMinRate() * maxR) / (100 * sumOfMaxR)), maxR)};

    cities_[t][i].minFundsData().minR_ = minR;
    
    lg.dbg() << "MinFunds::calcMinFunds:i=" << i << ",t=" << t << ",minR=" << minR << endl;
    return minR;
}

void MinFunds::calcMinFunds(u32 t)
{
    calcSumOfMaxFunds(t);
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        calcMinFunds(i, t);
    }
}

}