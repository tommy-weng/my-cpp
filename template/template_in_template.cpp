#include <iostream>

using std::cout;
using std::endl;

template <class T>
struct A
{
    A()
    {
        cout << std::is_same<int, T>::value << endl;  
    }
};


template <typename T, template <typename U> class Containor>
struct Generator
{
    Containor<T> values{};
};

int main()
{
    Generator<int, A>{};
    return 0;
}   
