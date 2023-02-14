#include <iostream>

using std::cout;
using std::endl;

// https://blog.csdn.net/kh815/article/details/115680799

template <typename T>
class A
{
public:
    template <typename U>
    void fun(U a)
    {
        cout << a << endl;
    }
};

template <typename T>
void foo(T a)
{
    A<T> aa;
    aa.template fun<T>(a); // need a template keyword before fun
}

int main()
{
    foo(1);

    return 0;
}   

