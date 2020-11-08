#include "SurgicalMask.hpp"
#include "../logger/Logger.hpp"

namespace surgicalMask
{

SurgicalMask::SurgicalMask(Cities& cities, Weeks& weeks, Pool& pool)
:cities_(cities),
weeks_(weeks),
pool_(pool)
{
}

SurgicalMask::~SurgicalMask()
{
}

r32 SurgicalMask::calcOverbookFactor(u32 i, u32 t)
{
    r32 lastOverbookFactor = t > 0 ? cities_.at(t-1).at(i).surgMaskData().overbookFactor_ : 1;
    r32 lastSumR = t > 0 ? cities_.at(t-1).at(i).sumData().sumR_ : 0;
    r32 lastSmLoad = cities_.at(t).at(i).config().smLoad_;

    r32 overbookFactor = lastSmLoad * lastOverbookFactor < lastSumR ? 1 : pool_.overbookFactorSM;

    cities_.at(t).at(i).surgMaskData().overbookFactor_ = overbookFactor;

    lg.dbg() << "SurgicalMask::calcOverbookFactor:i=" << i << ",t=" << t << ",overbookFactor=" << overbookFactor << endl;

    return overbookFactor;
}

r32 SurgicalMask::calcDedicatedFunds(u32 i, u32 t)
{
    r32 lastSmLoad = cities_.at(t).at(i).config().smLoad_;
    r32 overbookFactor = cities_.at(t).at(i).surgMaskData().overbookFactor_;
    r32 minR = cities_.at(t).at(i).minFundsData().minR_;

    r32 dedicatedR = min(overbookFactor * lastSmLoad, minR);
    cities_.at(t).at(i).surgMaskData().dedicatedR_ = dedicatedR;

    lg.dbg() << "SurgicalMask::calcDedicatedFunds:i=" << i << ",t=" << t << ",dedicatedR=" << dedicatedR << endl;

    return dedicatedR;
}

r32 SurgicalMask::calcIdealSharedFunds(u32 i, u32 t)
{
    r32 overbookFactor{cities_.at(t).at(i).surgMaskData().overbookFactor_};
    r32 lastSmLoad{cities_.at(t).at(i).config().smLoad_};
    r32 dedicatedR{cities_.at(t).at(i).surgMaskData().dedicatedR_};
    r32 maxR{cities_.at(t).at(i).config().maxR_};
    r32 minR{cities_.at(t).at(i).minFundsData().minR_};

    r32 idealSharedR{max(min(overbookFactor * lastSmLoad - dedicatedR, maxR - minR), static_cast<r32>(0))};

    cities_.at(t).at(i).surgMaskData().idealSharedR_ = idealSharedR;
    weeks_.at(t).sumOfSmIdealSharedR() += idealSharedR;

    lg.dbg() << "SurgicalMask::calcIdealSharedFunds:i=" << i << ",t=" << t << ",idealSharedR=" << idealSharedR << endl;

    return idealSharedR;
}

void SurgicalMask::calcPoolR(u32 t)
{
    r32 sumOfMinR{0};
    for (u32 city = 0; city < MAX_CITIES; city++)
    {
        sumOfMinR += cities_.at(t).at(city).minFundsData().minR_;
    }
    weeks_.at(t).smPoolR() = pool_.poolR() - sumOfMinR;

    lg.dbg() << "SurgicalMask::calcPoolR:t=" << t << ",smPoolR=" << weeks_.at(t).smPoolR() << endl; 
}

r32 SurgicalMask::calcSharedFunds(u32 i, u32 t)
{
    r32 idealSharedR{cities_.at(t).at(i).surgMaskData().idealSharedR_};
    r32 poolR{weeks_.at(t).smPoolR()};
    r32 sumOfIdealShareR{weeks_.at(t).sumOfSmIdealSharedR()};
    r32 sharedR{min(idealSharedR, idealSharedR * poolR / sumOfIdealShareR)};
    cities_.at(t).at(i).surgMaskData().sharedR_ = sharedR;

    lg.dbg() << "SurgicalMask::calcSharedFunds:i=" << i << ",t=" << t << ",sharedR=" << sharedR << endl;
    return sharedR;
}

}