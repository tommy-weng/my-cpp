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

class Point
{
public:
    Point(u32 a, u32 b):x(a),y(b){}
    Point& operator * (u32 n)
    {
        x *= n;
        y *= n;
        return *this; 
    }
    friend Point& operator * (u32 n, Point& p); // if object locate at right of operator, must to use friend function defined out class.
    friend ostream& operator <<(ostream& stream, Point& name); // same as above
private:
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
    stream  << "Point = {" <<  name.x << ", " << name.y << "}"; 
    return stream;
}

int main(void) 
{
    Point point{2, 6};
    cout << 2 * point * 3 << endl; 
    return 0; 
} 

