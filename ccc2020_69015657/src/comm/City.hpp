#pragma once
#include "../utils/defs.hpp"

namespace comm
{

class City
{

public:
    struct Conf
    {
        r32 maxR_;
        r32 smLoad_;
        r32 disLoad_;
        r32 otherLoad_;
    };
    struct MinFundsData
    {
        r32 minR_;
    };
    struct SurgMaskData
    {
        r32 overbookFactor_;
        r32 dedicatedR_;
        r32 idealSharedR_;
        r32 sharedR_;
    };
    struct DisinData
    {
        r32 overbookFactor_;
        r32 minR_;
        r32 dedicatedR_;
        r32 idealSharedR_;
        r32 sharedR_;
    };

    struct OtherData
    {
        r32 maxSharedR_;
        r32 overbookFactor_;
        r32 sharedR_;
    };

    struct SumData
    {
        r32 sumR_;
    };

    City();
    ~City();
    
    Conf& config(){return config_;}
    const Conf& config() const {return config_;}

    MinFundsData& minFundsData() {return minFundsData_;}
    const MinFundsData& minFundsData() const {return minFundsData_;}

    SurgMaskData& surgMaskData() {return surgMaskData_;}
    const SurgMaskData& surgMaskData() const {return surgMaskData_;}

    DisinData& disinData() {return disinData_;}
    const DisinData& disinData() const {return disinData_;}

    OtherData& otherData() {return otherData_;}
    const OtherData& otherData() const {return otherData_;}

    SumData& sumData() {return sumData_;}
    const SumData& sumData() const {return sumData_;}
private:
    Conf         config_;
    MinFundsData minFundsData_;
    SurgMaskData surgMaskData_;
    DisinData    disinData_;
    OtherData    otherData_;
    SumData      sumData_;
};
    
}
