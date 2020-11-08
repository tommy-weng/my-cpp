#include <gtest/gtest.h>
#define private public
#include "../src/surgicalMask/SurgicalMask.hpp"

TEST(SurgicalMask, calcOverbookFactor) {
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
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    surgicalMask::SurgicalMask surgMask(cities, weeks, pool);
    ASSERT_EQ(1.5, surgMask.calcOverbookFactor(0, 0)); 
}

TEST(SurgicalMask, calcOverbookFactor_With_TwoWeeks) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 101;
    pool.poolMinRate() = 40;

    surgicalMask::SurgicalMask surgMask(cities, weeks, pool);
    ASSERT_EQ(1.5, surgMask.calcOverbookFactor(0, 0)); 
    ASSERT_EQ(1, surgMask.calcOverbookFactor(0, 1)); 
}

TEST(SurgicalMask, calcDedicatedFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    surgicalMask::SurgicalMask surgMask(cities, weeks, pool);

    ASSERT_EQ(0, surgMask.calcDedicatedFunds(0, 0)); 
}

TEST(SurgicalMask, calcIdealSharedFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 30;
    city[0].config().smLoad_ = 20;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    city[0].minFundsData().minR_ = 20;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    surgicalMask::SurgicalMask surgMask(cities, weeks, pool);
    ASSERT_EQ(1.5, surgMask.calcOverbookFactor(0, 0));
    ASSERT_EQ(20, surgMask.calcDedicatedFunds(0, 0)); 
    ASSERT_EQ(10, surgMask.calcIdealSharedFunds(0, 0)); 
}

TEST(SurgicalMask, calcPoolR) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;
    array<comm::City, MAX_CITIES> city;
    city[0].minFundsData().minR_ = 20;
    Cities cities{city};

    comm::Week week;
    Weeks weeks{week};

    Pool pool;
    pool.poolR() = 100;

    surgicalMask::SurgicalMask surgMask(cities, weeks, pool);
    surgMask.calcPoolR(0);
    ASSERT_EQ(100 - 20,  weeks.at(0).smPoolR());
}

TEST(SurgicalMask, calcSharedFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 20;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    city[0].minFundsData().minR_ = 20;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    surgicalMask::SurgicalMask surgMask(cities, weeks, pool);
    ASSERT_EQ(1.5, surgMask.calcOverbookFactor(0, 0));
    ASSERT_EQ(20, surgMask.calcDedicatedFunds(0, 0)); 
    ASSERT_EQ(10, surgMask.calcIdealSharedFunds(0, 0));
    ASSERT_EQ(10, surgMask.calcSharedFunds(0, 0)); 
}

TEST(SurgicalMask, calcSharedFundsOfBase) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 20;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    city[0].minFundsData().minR_ = 20;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    surgicalMask::SurgicalMask surgMask(cities, weeks, pool);
    surgMask.comm::FundsBase::calcSharedFunds(0);
    ASSERT_EQ(10, cities[0][0].surgMaskData().sharedR_);
}
