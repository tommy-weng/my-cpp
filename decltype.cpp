#include <iostream>
 
template<typename T>  
T f();
 
struct S {int a;};
 
int a = 0;
S s;
decltype(auto) g1() {return s.a;}
decltype(auto) g2() {return std::move(a);}
decltype(auto) g3() {return (a);}
decltype(auto) g4() {return (0);}
 
int main()
{
    decltype(auto) i1 = a;
    decltype(auto) i2 = std::move(a);
    decltype(auto) i3 = (s.a);
    decltype(auto) i4 = (0);
    f<decltype(i1)>();
    f<decltype(i2)>();
    f<decltype(i3)>();
    f<decltype(i4)>();
    f<decltype(g1())>();
    f<decltype(g2())>();
    f<decltype(g3())>();
    f<decltype(g4())>();
}
