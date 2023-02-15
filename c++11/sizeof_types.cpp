#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

template <class T, class... Args>
inline constexpr auto make_array(Args&&... vals)
{
    cout << sizeof...(vals) << endl;
    return std::array<T, sizeof...(vals)>{vals...};
}


int main()
{
    make_array<int>(1,2,3,4);
}   

