#include "Disinfectant.hpp"
#include "../logger/Logger.hpp"

namespace disin
{
    
Disinfectant::Disinfectant(Cities& cities, Weeks& weeks, Pool& pool)
:cities_(cities),
weeks_(weeks),
pool_(pool)
{
}

Disinfectant::~Disinfectant()
{
}

r32 Disinfectant::calcOverbookFactor(u32 i, u32 t)
{
    r32 lastOverbookFactor{t > 0 ? cities_.at(t-1).at(i).disinData().overbookFactor_ : 1};
    r32 lastSumR{t > 0 ? cities_.at(t-1).at(i).sumData().sumR_ : 0};
    r32 lastDisinLoad{cities_.at(t).at(i).config().disLoad_};

    r32 overbookFactor{lastDisinLoad * lastOverbookFactor < lastSumR ? 1 : pool_.overbookFactorDis};

    cities_.at(t).at(i).disinData().overbookFactor_ = overbookFactor;

    lg.dbg() << "Disinfectant::calcOverbookFactor:i=" << i << ",t=" << t << ",overbookFactor=" << overbookFactor << endl;

    return overbookFactor;
}

r32 Disinfectant::calcDedicatedFunds(u32 i, u32 t)
{
    r32 minR{cities_.at(t).at(i).minFundsData().minR_ - cities_.at(t).at(i).surgMaskData().dedicatedR_};
    r32 overbookFactor{cities_.at(t).at(i).disinData().overbookFactor_};
    r32 load{cities_.at(t).at(i).config().disLoad_};

    r32 dedicatedR{min(overbookFactor * load, minR)};
    cities_.at(t).at(i).disinData().minR_ = minR;
    cities_.at(t).at(i).disinData().dedicatedR_ = dedicatedR;

    lg.dbg() << "Disinfectant::calcDedicatedFunds:i=" << i << ",t=" << t << ",dedicatedR=" << dedicatedR << endl;

    return dedicatedR;
}

r32 Disinfectant::calcIdealSharedFunds(u32 i, u32 t)
{
    r32 overbookFactor{cities_.at(t).at(i).disinData().overbookFactor_};
    r32 load{cities_.at(t).at(i).config().disLoad_};
    r32 dedicatedR{cities_.at(t).at(i).disinData().dedicatedR_};
    r32 maxR{cities_.at(t).at(i).config().maxR_};
    r32 minR{cities_.at(t).at(i).minFundsData().minR_};

    r32 idealSharedR{max(min(overbookFactor * load - dedicatedR, maxR - minR), static_cast<r32>(0))};

    cities_.at(t).at(i).disinData().idealSharedR_ = idealSharedR;
    weeks_.at(t).sumOfDisIdealSharedR() += idealSharedR;

    lg.dbg() << "Disinfectant::calcIdealSharedFunds:i=" << i << ",t=" << t << ",idealSharedR=" << idealSharedR << endl;

    return idealSharedR;
}
void Disinfectant::calcPoolR(u32 t)
{
    r32 sumOfSharedSM{0};
    for (u32 city = 0; city < MAX_CITIES; city++)
    {
        sumOfSharedSM += cities_.at(t).at(city).surgMaskData().sharedR_;
    }
    weeks_.at(t).disPoolR() = weeks_.at(t).smPoolR() - sumOfSharedSM;

    lg.dbg() << "Disinfectant::calcPoolR:t=" << t << ",disPoolR=" << weeks_.at(t).disPoolR() << endl; 
}

r32 Disinfectant::calcSharedFunds(u32 i, u32 t)
{
    r32 idealSharedR{cities_.at(t).at(i).disinData().idealSharedR_};
    r32 poolR{weeks_.at(t).disPoolR()};
    r32 sumOfIdealShareR{weeks_.at(t).sumOfDisIdealSharedR()};
    r32 sharedR{min(idealSharedR, idealSharedR * poolR / sumOfIdealShareR)};

    cities_.at(t).at(i).disinData().sharedR_ = sharedR;
    weeks_.at(t).sumOfDisSharedR() += sharedR;

    lg.dbg() << "Disinfectant::calcSharedFunds:i=" << i << ",t=" << t << ",sharedR=" << sharedR << endl;
    return sharedR;
}


}