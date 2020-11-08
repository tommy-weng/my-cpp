#include <iostream>
#include <cmath>
#include "TotalFunds.hpp"
#include "../logger/Logger.hpp"
#include "../surgicalMask/SurgicalMask.hpp"
#include "../disinfectant/Disinfectant.hpp"

using namespace std;

namespace total
{

TotalFunds::TotalFunds()
:io(cities, weeks, pool),
minFunds(cities, weeks, pool),
surgicalMask(*(new surgicalMask::SurgicalMask{cities, weeks, pool})),
disinfectant(*(new disin::Disinfectant{cities, weeks, pool})),
otherFunds(cities, weeks, pool)
{

}

TotalFunds::~TotalFunds()
{
    delete &surgicalMask;
    delete &disinfectant;
}

bool TotalFunds::calcTotalFunds(const char* inputFile)
{
    io.input(inputFile);
    for (u32 t = 0; t < cities.size(); t++)
    {
        minFunds.calcMinFunds(t);
        surgicalMask.calcSharedFunds(t);
        disinfectant.calcSharedFunds(t);
        otherFunds.calcSharedFunds(t);
        for (u32 i = 0; i < MAX_CITIES; i++)
        {
            r32 minR{cities.at(t).at(i).minFundsData().minR_};
            r32 smSharedR{cities.at(t).at(i).surgMaskData().sharedR_};
            r32 disSharedR{cities.at(t).at(i).disinData().sharedR_};
            r32 otherSharedR{cities.at(t).at(i).otherData().sharedR_};
            r32 sumR{minR + smSharedR + disSharedR + otherSharedR};
            cities.at(t).at(i).sumData().sumR_ = sumR;

            lg.dbg() << "TotalFunds::calcTotalFunds:i=" << i << ",t=" << t << ",sumR=" << sumR << endl;
        }

        fixTotalFunds(t);
    }

    return true;
}

void TotalFunds::fixTotalFunds(u32 t)
{
    r32 intPartOfSumRSum{0};
    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        cities.at(t).at(i).sumData().sumR_ = floor(cities.at(t).at(i).sumData().sumR_);
        intPartOfSumRSum += cities.at(t).at(i).sumData().sumR_;
    }

    r32 remainOfSumR{pool.poolR() - intPartOfSumRSum};

    for (u32 i = 0; i < MAX_CITIES; i++)
    {
        r32 sumR{cities.at(t).at(i).sumData().sumR_};
        r32 maxR{cities.at(t).at(i).config().maxR_};
        sumR = min(maxR, sumR + remainOfSumR);
        r32 comsumptionSumR = sumR - cities.at(t).at(i).sumData().sumR_;
        cities.at(t).at(i).sumData().sumR_ = sumR;

        if (remainOfSumR > 0)
        {
            remainOfSumR -= comsumptionSumR;
        }
        else
        {
            break;
        }

        lg.dbg() << "TotalFunds::fixTotalFunds:i=" << i << ",t=" << t \
                 << ",sumR=" << cities.at(t).at(i).sumData().sumR_ \
                 << ",comsumptionSumR=" << comsumptionSumR \
                 << endl;
    }
}

void TotalFunds::show()
{
    io.output();
}

}