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
#include <optional>

using std::cout;
using std::endl;
using std::optional;
using std::nullopt;

void myReset(optional<int>& i)
{
    if (not i)
    {
        cout << "not initialized." << endl;
    }
    else
    {
        i.reset();
    }
}

int main()
{
    optional<int> a;
    a = 1;
    myReset(a);
    a.emplace(2);
    cout <<  not (nullopt == a) << endl;
    cout << a.value() << endl;

    return 0;
}   

