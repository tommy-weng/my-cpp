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

class Data
{
public:
    Data()
    {
    }
    size_t operator ()(int a, int b)
    {
        return a + b;
    }

    ~Data()
    {
    }
};


int main()
{
    cout << hash<string>()("tomm") << endl;
    cout << hash<double>()(2.1) << endl;
    return 0;
}   

