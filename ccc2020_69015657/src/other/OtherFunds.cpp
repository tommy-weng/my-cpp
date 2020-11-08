#include "OtherFunds.hpp"
#include "../logger/Logger.hpp"

namespace other
{

OtherFunds::OtherFunds(Cities& cities, Weeks& weeks, Pool& pool)
:cities_(cities),
weeks_(weeks),
pool_(pool)
{
}

OtherFunds::~OtherFunds()
{
}

r32 OtherFunds::calcMaxShareFunds(u32 i, u32 t)
{
    r32 maxR{cities_.at(t).at(i).config().maxR_};
    r32 minR{cities_.at(t).at(i).minFundsData().minR_};
    r32 sharedR_SM{cities_.at(t).at(i).surgMaskData().sharedR_};
    r32 sharedR_Dis{cities_.at(t).at(i).disinData().sharedR_};

    r32 maxSharedR{maxR - minR - sharedR_SM - sharedR_Dis};

    cities_.at(t).at(i).otherData().maxSharedR_ = maxSharedR;

    lg.dbg() << "OtherFunds::calcMaxShareFunds:i=" << i << ",t=" << t << ",maxSharedR=" << maxSharedR << endl;

    return maxSharedR;
}

void OtherFunds::calcOverbookFactor(u32 t)
{
    if (0 == t)
    {
        cities_.at(t).at(0).otherData().overbookFactor_ = pool_.overbookFactorOhter;
        cities_.at(t).at(1).otherData().overbookFactor_ = 1;
        cities_.at(t).at(2).otherData().overbookFactor_ = 1;
        cities_.at(t).at(3).otherData().overbookFactor_ = 1;
        return;
    }
    for (u32 city = 0; city < MAX_CITIES; city++)
    {
        u32 next{MAX_CITIES == 1 + city ? 0 : city + 1};
        if (pool_.overbookFactorOhter == cities_.at(t-1).at(city).otherData().overbookFactor_)
        {
            cities_.at(t).at(next).otherData().overbookFactor_ = pool_.overbookFactorOhter;
        }
        else
        {
            cities_.at(t).at(next).otherData().overbookFactor_ = 1;
        }
    }

    lg.dbg() << "OtherFunds::calcOverbookFactor:t=" << t \
             << ",overbookFactor[0,1,2,3]=" \
             << cities_.at(t).at(0).otherData().overbookFactor_ << "," \
             << cities_.at(t).at(1).otherData().overbookFactor_ << "," \
             << cities_.at(t).at(2).otherData().overbookFactor_ << "," \
             << cities_.at(t).at(3).otherData().overbookFactor_ << endl;
}

void OtherFunds::calcSumOfLoadFactor(u32 t)
{
    for (u32 city = 0; city < MAX_CITIES; city++)
    {
        weeks_.at(t).sumOfLoadFactor() += cities_.at(t).at(city).config().otherLoad_ * 
                                          cities_.at(t).at(city).otherData().overbookFactor_;
    }
}

r32 OtherFunds::calcSharedFunds(u32 i, u32 t)
{
    r32 maxSharedR{cities_.at(t).at(i).otherData().maxSharedR_};
    r32 load{cities_.at(t).at(i).config().otherLoad_};
    r32 overbookFactor{cities_.at(t).at(i).otherData().overbookFactor_};
    r32 sumOfDisSharedR{weeks_.at(t).sumOfDisSharedR()};
    r32 sumOfLoadFactor{weeks_.at(t).sumOfLoadFactor()};
    r32 poolR{weeks_.at(t).disPoolR() - sumOfDisSharedR};

    r32 sharedR{min(maxSharedR, load * overbookFactor * poolR / sumOfLoadFactor)};

    lg.dbg() << "OtherFunds::calcSharedFunds:i=" << i << ",t=" << t << ",sharedR=" << sharedR \
            << ",maxSharedR=" << maxSharedR << ",load=" << load << ", overbookFactor=" << overbookFactor \
            << ",otherPoolR=" << poolR << ",sumOfLoadFactor=" << sumOfLoadFactor << endl;
    cities_.at(t).at(i).otherData().sharedR_ = sharedR;

    return sharedR;
}


void OtherFunds::calcSharedFunds(u32 t)
{
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        calcMaxShareFunds(i, t);
    }
    calcOverbookFactor(t);
    calcSumOfLoadFactor(t);
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        calcSharedFunds(i, t);
    }
}

}