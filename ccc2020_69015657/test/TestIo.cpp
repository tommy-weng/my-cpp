#include <gtest/gtest.h>
#include "../src/io/Io.hpp"

TEST(Io, input) {
    using Cities = vector<array<comm::City, MAX_CITIES>>;
    using Weeks = vector<comm::Week>;
    using Pool = comm::Pool;
    const char* inputFile = "../testcases/case-1-input.txt";

    Cities cities;
    Weeks weeks;
    Pool pool;
    io::Io io(cities, weeks, pool);
    ASSERT_EQ(true, io.input(inputFile));
    ASSERT_EQ(100, pool.poolR()); 
    ASSERT_EQ(40, pool.poolMinRate()); 
    ASSERT_EQ(50, cities.at(0).at(0).config().maxR_);
    ASSERT_EQ(40, cities.at(0).at(0).config().smLoad_); 
    ASSERT_EQ(0, cities.at(0).at(0).config().disLoad_); 
    ASSERT_EQ(10, cities.at(0).at(0).config().otherLoad_); 
}