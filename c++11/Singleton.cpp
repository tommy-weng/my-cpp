#include <iostream>
#include <sstream>
#include <string>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <bitset>
#include <tuple>
#include <algorithm>
#include <memory>

using namespace std;


struct Data
{
    alignas(2) 
    char c;
    int i;
};


class Singleton
{
public:
    using ObjectStorage = typename std::aligned_storage<sizeof(Data), alignof(Data)>::type;
    static Singleton* getInstance()
    {
        if (not instance)
        {
            instance = reinterpret_cast<Singleton *>(new (&obj) Singleton());
        }

       return instance; 
    }

private:
    Singleton(){cout << "Ctor" << endl;}
    ~Singleton(){cout << "Dtor" << endl;}
    static ObjectStorage obj;
    static Singleton* instance;
};

Singleton::ObjectStorage Singleton::obj;
Singleton* Singleton::instance{nullptr};

int main()
{
    auto instance = Singleton::getInstance();
    return 0;
}   

