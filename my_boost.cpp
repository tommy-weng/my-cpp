#include <iostream>
#include <boost/bind.hpp>
#include <boost/any.hpp>

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
    cout << boost::bind(add, _1, b)(3) << endl;

    boost::any c;
    c = string("abc");
    cout << boost::any_cast<string>(c) << endl;
    cout << c.type().name() << endl;

    return 0;
}

