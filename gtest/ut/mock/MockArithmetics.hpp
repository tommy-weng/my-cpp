#pragma once
#include <gmock/gmock.h>

class MockArithmetics
{
public:
    MOCK_METHOD2(plus, int(int, int));
    MOCK_METHOD2(minus, int(int, int));
};

class MockArithmeticsConstructor
{
public:
    MOCK_METHOD0(construct, std::shared_ptr<MockArithmetics>());
};

std::unique_ptr<MockArithmeticsConstructor> mockArithmeticsConstructor{nullptr};

class Arithmetics
{
public:
    Arithmetics()
    {
        mockArithmetics = mockArithmeticsConstructor->construct();
    }
    int plus(int a, int b)
    {
        return mockArithmetics->plus(a, b);
    }
    int minus(int a, int b)
    {
        return mockArithmetics->minus(a, b);
    }

private:
    std::shared_ptr<MockArithmetics> mockArithmetics{nullptr};
    
};