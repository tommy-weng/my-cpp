#include <gtest/gtest.h>
#define private public
#include "../src/disinfectant/Disinfectant.hpp"

TEST(Disinfectant, calcOverbookFactor) {
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

    disin::Disinfectant disinfectant(cities, weeks, pool);
    ASSERT_EQ(1.2, disinfectant.calcOverbookFactor(0, 0)); 
}

TEST(Disinfectant, calcDedicatedFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    city[0].minFundsData().minR_ = 60;
    city[0].surgMaskData().dedicatedR_ = 20;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    disin::Disinfectant disinfectant(cities, weeks, pool);

    ASSERT_EQ(1.2, disinfectant.calcOverbookFactor(0, 0)); 
    ASSERT_EQ(24, disinfectant.calcDedicatedFunds(0, 0)); 
}

TEST(Disinfectant, calcIdealSharedFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 20;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    city[0].minFundsData().minR_ = 40;
    city[0].surgMaskData().dedicatedR_ = 20;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 10;
    week.disPoolR() = 15;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    disin::Disinfectant disinfectant(cities, weeks, pool);

    ASSERT_EQ(1.2, disinfectant.calcOverbookFactor(0, 0)); 
    ASSERT_EQ(20, disinfectant.calcDedicatedFunds(0, 0));
    ASSERT_EQ(4, disinfectant.calcIdealSharedFunds(0, 0)); 
}

TEST(Disinfectant, calcPoolR) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;
    array<comm::City, MAX_CITIES> city;
    city[0].surgMaskData().sharedR_ = 10;
    Cities cities{city};

    comm::Week week;
    week.smPoolR() = 60;
    Weeks weeks{week};
    Pool pool;

    disin::Disinfectant disinfectant(cities, weeks, pool);
    disinfectant.calcPoolR(0);
    ASSERT_EQ(60 - 10,  weeks.at(0).disPoolR());
}

TEST(Disinfectant, calcSharedFunds) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;

    array<comm::City, MAX_CITIES> city;
    city[0].config().maxR_ = 50;
    city[0].config().smLoad_ = 10;
    city[0].config().disLoad_ = 30;
    city[0].config().otherLoad_ = 30;
    city[0].sumData().sumR_ = 20;
    city[0].minFundsData().minR_ = 40;
    city[0].surgMaskData().dedicatedR_ = 20;
    city[0].surgMaskData().sharedR_ = 10;
    Cities cities{city,city};

    comm::Week week;
    week.smPoolR() = 15;
    week.disPoolR() = 5;
    week.sumOfDisIdealSharedR() = 0;
    Weeks weeks{week,week};

    Pool pool;
    pool.poolR() = 100;
    pool.poolMinRate() = 40;

    disin::Disinfectant disinfectant(cities, weeks, pool);

    ASSERT_EQ(1.2, disinfectant.calcOverbookFactor(0, 0)); 
    ASSERT_EQ(20, disinfectant.calcDedicatedFunds(0, 0));
    ASSERT_EQ(10, disinfectant.calcIdealSharedFunds(0, 0));
    ASSERT_EQ(5, disinfectant.calcSharedFunds(0, 0));
    
}