#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <bitset>
#include <tuple>
#include <algorithm>

using namespace std;

void foo(int& a)
{
    cout << "int& a" << endl;
}

void foo(int&& a)
{
    cout << "int&& a" << endl;
}

void forward(int&& a)
{
    cout << "forward(int&&): " << a << endl;
    foo(std::forward<int>(a));
}

int main()
{
    forward(2);
    return 0;
}   

