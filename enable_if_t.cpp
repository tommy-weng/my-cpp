#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

template <size_t n = 1>
typename std::enable_if_t<n == 1, void> fun()
{
    cout << "tommy" << endl;
}

template <size_t n = 1>
typename std::enable_if_t<n == 0, void> fun()
{
    cout << "not tommy" << endl;
}

int main()
{
    fun<0>();
    return 0;
}   

