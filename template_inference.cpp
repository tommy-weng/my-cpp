#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

template <typename T, uint32_t N>
struct Container
{
    std::array<T, N> ids;
};

template <typename T, typename U>
class A;

template <typename Id, uint32_t M, typename U>
class A<Container<Id, M>, U>
{
public:
    Id& getId(Id& id)
    {
        U second = 3;
        cout << second << endl;
        cout << M << endl;
        return id;
    }
};

int main()
{
    uint32_t id = 2;

    A<Container<uint32_t, 8>, float> aa{};

    cout << aa.getId(id) << endl;
    return 0;
}   

