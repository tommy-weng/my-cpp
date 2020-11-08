#pragma once

#include <vector>
#include <array>
#include "../utils/defs.hpp"
#include "../comm/City.hpp"
#include "../comm/Week.hpp"
#include "../comm/Pool.hpp"
#include "../comm/FundsBase.hpp"
#include "../minFunds/MinFunds.hpp"
#include "../other/OtherFunds.hpp"
#include "../io/Io.hpp"

using namespace std;


namespace total
{
class TotalFunds
{
public:
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;
    using Io = io::Io;

    TotalFunds();
    ~TotalFunds();
    bool calcTotalFunds(const char * inputFile);
    void show();
private:
    void fixTotalFunds(u32 t);
    
    Cities cities;
    Weeks weeks;
    Pool pool;
    Io io;
    minFunds::MinFunds minFunds;
    comm::FundsBase& surgicalMask;
    comm::FundsBase& disinfectant;
    other::OtherFunds otherFunds;
};

} // namespace total