#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

template <typename T, int a, typename... Args>
class Test
{
public:
    void excute()
    {
        data.show(a);
    }

    void parseArgs(Args&&... args)
    {
        auto msg = make_tuple(forward<Args>(args)...);

        int i;
        float f;
        string s;

        tie(i,f,s) = msg;
        auto [x,y,z] = msg;
        cout << i << "," << f << "," << s << endl;
        cout << x << "," << y << "," << z << endl;
    }

    T data;
};

class Data
{
public:
    void show(int i)
    {
        cout << "i=" << i << endl;
    }
};

int main()
{
    Test<Data, 3, int, float, string> t{};
    t.excute();
    t.parseArgs(100, 1.5, "tommy");
    return 0;
}   

