#include <gtest/gtest.h>
#include "../src/total/TotalFunds.hpp"

TEST(TotalFunds, calcTotalFunds) {
    const char* inputFile = "../testcases/case-1-input.txt";
    total::TotalFunds totolFunds;
    ASSERT_EQ(true, totolFunds.calcTotalFunds(inputFile));
    totolFunds.show();
}