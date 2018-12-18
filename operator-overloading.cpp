#include <iostream>
#include <ostream>
#include <typeinfo>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>
#include <memory>
#include <bitset>
#include <algorithm>
#include <assert.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

using namespace std;

enum ECourse
{
    EMathematics,
    EPhilosophy,
    EHistory
};

class Base
{
public:
    Base(u32 n):_n(n){}
    void print()
    {
        cout << "n: "<< _n << endl;
    }
private:
	int _n;
};

class Derived: public Base
{
};
struct Point
{
    u32 x;
    u32 y;
    
};
Point& operator * (u32 n, Point& p)
    {
        p.x *= n;
        p.y *= n;
        return p; 
    }
ostream& operator <<(ostream& stream, Point& name)
{
    stream  << "x = " <<  name.x << ' ' << "y = " << name.y << endl; 
    return stream;
}


void foo(int x)
{
    cout << "::foo " << x << endl;
}
struct A
{
    void foo(double d) const {
        cout << "A::foo " << d << endl; 
    }
    void foo(int i) const
    {
        cout << "int::foo " << i << endl;
    }

    void bar(int x)
    {
        foo(x);
    }
};

int main(void) 
{
    cout << getpid() << endl; 
    return 0; 
} 

