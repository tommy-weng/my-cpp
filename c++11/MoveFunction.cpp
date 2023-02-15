#include <iostream>

using std::cout;
using std::endl;

void fun(int&)
{
    cout << "Ref fun" << endl;
}

void fun(int&&)
{
    cout << "Move fun" << endl;
}

int main()
{
    int&& a = 1;
    fun(1);
    fun(a);
    fun(std::forward<decltype(a)>(a));
    fun(std::move(a));

    return 0;
}

