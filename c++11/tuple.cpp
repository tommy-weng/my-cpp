#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


int main()
{
    int a;
    float b;
    string c;
    tuple<int, float, string> t(1,2.1,"hellow");
    tie(a,b,c) = t;
    get<2>(t) = "my name";
    cout << c.c_str() << endl;

    return 0;
}   

