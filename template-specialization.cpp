//specialization

#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T, typename U>
void add(T a, U b)
{
    cout << "In raw function template" << endl;
}

template <>
void add<int, double>(int a, double b)
{
    cout << "In specialization function template" << endl;
}

class A
{
public:
    template <typename T, typename U>
    static void foo(T k, U val)
    {
        cout << "in class A: " << val << endl;
    }
};

template <>
void A::foo<int, int>(int k, int val)
{
    cout << "out class A: " << val << endl;
}

// partial specialization function is not supported in c++

template <typename T, typename U>
class Test
{
public:
    Test(T x, U y):a(x),b(y)
    {
        cout << "In raw class template" << endl;
    }

private:
    T a;
    U b;
};

template <>
class Test<int, float>
{
public:
    Test(int x, float y):a(x),b(y)
    {
        cout << "In complete specialization class template" << endl;
    }

private:
    int a;
    float b;
};

template <typename T>
class Test<T, float>
{
public:
    Test(T x, float y):a(x),b(y)
    {
        cout << "In partial specialization class template" << endl;
    }

private:
    T a;
    float b;
};




int main()
{
    int x{2};
    double y{2};
    add(x, y);

    Test<float, float>(1,2);
    return 0;
}   

