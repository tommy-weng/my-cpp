// g++ TestAdd.cpp main.cpp -lgtest -lpthread

#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(testAdd, testArrayAdd)
{
    int a[] = {1,2,3,4,5};
    int b[] = {5,6,7,8,9};
    int c[] = {6,8,10,13,14};
    for (int i{0}; i < 5; i++)
    {
        EXPECT_EQ(c[i], add(a[i], b[i])) << "i = " << i;
    }
}
