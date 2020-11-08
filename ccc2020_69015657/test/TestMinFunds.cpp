#include <gtest/gtest.h>
#define private public
#include "../src/minFunds/MinFunds.hpp"

TEST(MinFunds, calcMinFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    Cities cities{city};
    comm::Week week;
    week.sumOfMaxR() = 50;
    Weeks weeks{week};
    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;
    minFunds::MinFunds minFunds(cities, weeks, pool);
    ASSERT_EQ(40, minFunds.calcMinFunds(0, 0)); 
}

TEST(MinFunds, calcMinFunds_with_Decimals_roundUp) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    Cities cities{city};
    comm::Week week;
    week.sumOfMaxR() = city[0].config().maxR_;
    Weeks weeks{week};
    Pool pool;
    pool.poolR() = 101;
    pool.poolMinRate() = 40;
    minFunds::MinFunds minFunds(cities, weeks, pool);
    ASSERT_EQ(41, minFunds.calcMinFunds(0, 0)); 
}