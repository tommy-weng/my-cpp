#include <gtest/gtest.h>
#define private public
#include "../src/other/OtherFunds.hpp"

TEST(OtherFunds, calcMaxShareFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 70;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].minFundsData().minR_ = 30;
    city[0].surgMaskData().sharedR_ = 10;
    city[0].disinData().sharedR_ = 20;
    Cities cities{city};
    Weeks weeks;
    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;
    other::OtherFunds otherFunds(cities, weeks, pool);
    ASSERT_EQ(10, otherFunds.calcMaxShareFunds(0, 0)); 
}

TEST(OtherFunds, calcOverbookFactor) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    Cities cities{city,city,city,city,city};
    Weeks weeks;
    Pool pool;
    other::OtherFunds otherFunds(cities, weeks, pool);
    otherFunds.calcOverbookFactor(0);
    otherFunds.calcOverbookFactor(1);
    otherFunds.calcOverbookFactor(2);
    otherFunds.calcOverbookFactor(3);
    otherFunds.calcOverbookFactor(4);
    ASSERT_EQ(1.5, cities.at(0).at(0).otherData().overbookFactor_); 
    ASSERT_EQ(1, cities.at(0).at(1).otherData().overbookFactor_); 
    ASSERT_EQ(1.5, cities.at(1).at(1).otherData().overbookFactor_);
    ASSERT_EQ(1.5, cities.at(2).at(2).otherData().overbookFactor_); 
    ASSERT_EQ(1.5, cities.at(3).at(3).otherData().overbookFactor_);
    ASSERT_EQ(1.5, cities.at(4).at(0).otherData().overbookFactor_); 
}

TEST(OtherFunds, calcSharedFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 80;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].minFundsData().minR_ = 30;
    city[0].surgMaskData().sharedR_ = 10;
    city[0].disinData().sharedR_ = 10;
    Cities cities{city};
    comm::Week week;
    week.disPoolR() = 20;
    week.smPoolR() = 20;
    week.sumOfDisSharedR() = city[0].disinData().sharedR_;
    week.sumOfLoadFactor() = city[0].config().otherLoad_ * 1.5;
    Weeks weeks{week};
    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;
    other::OtherFunds otherFunds(cities, weeks, pool);
    ASSERT_EQ(30, otherFunds.calcMaxShareFunds(0, 0)); 
    otherFunds.calcOverbookFactor(0);
    ASSERT_EQ(10, otherFunds.calcSharedFunds(0, 0));
}