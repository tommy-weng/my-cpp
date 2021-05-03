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

template<typename T>
struct Indexer
{
    T id;

    Indexer(T&& id): id{id}{}
};
template <typename... Ts>
class MyTuple
{
public:
    MyTuple(Ts&&... ts):t{Indexer<Ts>{std::forward<Ts>(ts)}...}
    {
    }
    auto& gettuple()
    {
        return t;
    }
private:
    tuple<Indexer<Ts>...> t;
};

int main()
{
    int a;
    float b;
    string c;

    MyTuple<int, float, string> mt{1,1.2,"tommy"};
    auto& t =  mt.gettuple();
    cout << std::get<Indexer<string>>(t).id << endl;
    //cout << std::get<1>(t).id << endl;

    return 0;
}   

