#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void printa(int a)
{
    cout << a << endl;
}

using F = function<void(int)>;
void fun(F f, int a)
{
    cout << "in function" << endl;
    f(a);
}

void fun(decltype(printa) f, int a)
{
    cout << "in decltype" << endl;
    f(a);
}

template <typename F>
void fun(F f, int a)
{
    cout << "in template" << endl;
    f(a); 
}

int main()
{
    fun(printa, 1);
    return 0;
}   

