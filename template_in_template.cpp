#include <iostream>

using std::cout;
using std::endl;

template <class C>
struct A
{
    A()
    {
        cout << typeid(C).name() << endl;  
    }
    using type = C;
};


template <template <class> class>
struct B
{
    B()
    {
        cout << "emmmmm" << endl;
    }
};

int main()
{
    //A<int>{};
    B<A>{};
    return 0;
}   
