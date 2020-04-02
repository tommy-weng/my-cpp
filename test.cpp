#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <cmath>
using namespace std;

int main()
{
    ostringstream sstream("hello 12 1.2");

    sstream << "hello 12 1.4" << " " << 200 ;
    string s;
    int a;
    float b = -1;
    cout << abs(b) << endl;
    return 0;
}   

