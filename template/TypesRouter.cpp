#include <iostream>
#include <map>

using namespace std;
using std::cout;
using std::endl;

std::map<int, size_t> typeMap{{101, typeid(int).hash_code()},
                              {102, typeid(float).hash_code()},
                              {103, typeid(double).hash_code()}};

template <typename T>
auto tommy()
{
    // Do whatever you want
    return T{};
}

template <typename... Ts>
struct Router
{
    static void test(const int v)
    {
        cout << "default" << endl;
    }
};

template <typename T, typename... Ts>
struct Router<T, Ts...>
{
    static void test(const int v)
    {
        if (typeMap.find(v) == typeMap.end())
        {
            return;
        }
        if (typeMap.at(v) == typeid(T).hash_code())
        {
            cout << typeid(tommy<T>()).name() << endl;
            return;
        }
        Router<Ts...>::test(v);
    }
};

int main()
{
    int v = 103;

    Router<int, float, double>::test(v);

    return 0;
}
