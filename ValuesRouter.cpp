#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <string>

using std::cout;
using std::endl;

template<int H, int V>
struct Data
{
};

template <typename... Ts>
struct Routes
{
    static void run(const int h, const int v)
    {cout << "not found: h=" << h << ", v=" << v << endl;}
};

template <int H, int... Hs, int V, int... Vs>
struct Routes<Data<H, V>, Data<Hs, Vs>...>
{
    static void run(const int h, const int v)
    {
        if (H == h and V == v)
        {
            cout << "H="<< H << " V=" << V <<  endl;
            return;
        }
        Routes<Data<Hs, Vs>...>::run(h, v);
    }
};

int main()
{
    Routes<Data<8,4>, Data<8,2>, Data<4,4>>::run(8,2);
    Routes<Data<8,4>, Data<8,2>, Data<4,4>>::run(4,2);
    return 0;
}   

