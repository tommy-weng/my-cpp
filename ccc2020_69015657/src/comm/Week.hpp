#pragma once

#include "../utils/defs.hpp"

namespace comm
{

class Week
{
public:
    Week();
    ~Week();
    r32& smPoolR() { return smPoolR_; }
    const r32 smPoolR() const { return smPoolR_; }
    r32& disPoolR() { return disPoolR_; }
    const r32 disPoolR() const { return disPoolR_; }
    r32& sumOfMaxR() { return sumOfMaxR_; }
    const r32 sumOfMaxR() const { return sumOfMaxR_; }
    r32& sumOfSmIdealSharedR() { return sumOfSmIdealSharedR_; }
    const r32 sumOfSmIdealSharedR() const { return sumOfSmIdealSharedR_; }
    r32& sumOfDisIdealSharedR() { return sumOfDisIdealSharedR_; }
    const r32 sumOfDisIdealSharedR() const { return sumOfDisIdealSharedR_; }
    r32& sumOfDisSharedR() { return sumOfDisSharedR_; }
    const r32 sumOfDisSharedR() const { return sumOfDisSharedR_; }
    r32& sumOfLoadFactor() { return sumOfLoadFactor_; }
    const r32 sumOfLoadFactor() const { return sumOfLoadFactor_; }
private:
    r32 smPoolR_;
    r32 disPoolR_;
    r32 sumOfMaxR_;
    r32 sumOfSmIdealSharedR_;
    r32 sumOfDisIdealSharedR_;
    r32 sumOfDisSharedR_;
    r32 sumOfLoadFactor_;
};

}