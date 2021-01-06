#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(test_suite_name, test_name)
{
    EXPECT_EQ(3, add(1, 2));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   

