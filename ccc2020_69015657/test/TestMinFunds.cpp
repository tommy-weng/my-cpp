#include <gtest/gtest.h>
#define private public
#include "../src/minFunds/MinFunds.hpp"

class MinFundsTest : public ::testing::Test
{
public:
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;
    void SetUp() override
    {
        array<comm::City, MAX_CITIES> city;
        city[0].config().maxR_ = 50;
        city[0].config().smLoad_ = 10;
        city[0].config().disLoad_ = 20;
        city[0].config().otherLoad_ = 30;
        cities.push_back(move(city));

        comm::Week week;
        week.sumOfMaxR() = 50;
        weeks.push_back(move(week));

        pool.poolR() = 100;
        pool.poolMinRate() = 40;
    }

    void TearDown() override
    {

    }

protected:
    Cities cities{};
    Weeks weeks{};
    Pool pool{};
    minFunds::MinFunds minFunds{cities, weeks, pool};
};


TEST_F(MinFundsTest, calcMinFunds)
{
    ASSERT_EQ(40, minFunds.calcMinFunds(0, 0)); 
}

TEST_F(MinFundsTest, calcMinFunds_with_Decimals_roundUp)
{
    pool.poolR() = 101;
    ASSERT_EQ(41, minFunds.calcMinFunds(0, 0)); 
}

TEST_F(MinFundsTest, calcMinFundsMultiCityes)
{
    minFunds.calcMinFunds(0);
    ASSERT_EQ(20, cities[0][0].minFundsData().minR_); 
}