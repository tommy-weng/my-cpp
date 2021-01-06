#include <iostream>
#include <boost/bind.hpp>

using namespace std;
//using namespace boost;

int add(int x, int y)
{
    return x + y;
}

int main()
{
    int a = 1;
    int b = 2;

    cout << boost::bind(add, _1, _2)(a, b) << endl;

    return 0;
}

