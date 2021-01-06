// g++ my_gtest.cpp -lgtest -lpthread

#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(test_add, add_1_2_eq_3)
{
    EXPECT_EQ(3, add(1, 2));
}

TEST(test_add, add_2_3_eq_5)
{
    EXPECT_EQ(5, add(2, 3));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   

