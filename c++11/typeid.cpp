#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <typeinfo>

using namespace std;

using myuint = unsigned int;

class A
{

};

void fun(int a)
{

}


int main()
{
    auto& id1 = typeid(myuint);
    auto& id2 = typeid(A);
    auto& id3 = typeid(fun);
    cout << id1.name() << endl;
    cout << id2.name() << endl;
    cout << id3.name() << endl;
    return 0;
}   

