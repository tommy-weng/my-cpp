// g++ TestPAdd.cpp main.cpp -lgtest -lpthread

#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

struct Params
{
    int a;
    int b;
    int c;
};

class TestAddSuite: public ::testing::TestWithParam<Params>
{};

std::vector<Params> params{{1,2,3},{2,3,5},{3,4,8}};
INSTANTIATE_TEST_CASE_P(aTest, TestAddSuite, ::testing::ValuesIn(params));

TEST_P(TestAddSuite, testadd)
{
    Params params = GetParam();
    EXPECT_EQ(params.c, add(params.a, params.b));
}
