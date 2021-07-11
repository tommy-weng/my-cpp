#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;

template <typename T>
class Base
{
public:
    Base(T n):value{n}{}
    virtual void print() = 0;
protected:
    T value;
};

template <typename T>
class A: public Base<T>
{
public:
    using Type=T;
    A(T n):Base<T>(n){}
    void print() override
    {
        cout << "A::value=" << Base<T>::value <<endl;
    }
};

template <typename T>
class B: public Base<T>
{
public:
    using Type = T;
    B(T n):Base<T>(n){}
    void print() override
    {
        cout << "B::value=" << Base<T>::value << endl;
    }
};

template <typename T>
class C: public Base<T>
{
public:
    using Type = T;
    C(T n):Base<T>(n){}
    void print() override
    {
        cout << "C::value=" << Base<T>::value << endl;
    }
};

template <class... Cs>
class Factory;

template <int... Vs>
struct Values;

template <class... Cs, int... Vs>
class Factory<Values<Vs...>, Cs...>
{
public:
    Factory& create()
    {
        (v.emplace_back(std::move(std::make_unique<Cs>(Vs))), ...);
        return *this;
    }
    void show()
    {
        for_each(v.begin(), v.end(), [](auto& c){
            c->print();
        });
    }
private:
    std::vector<std::unique_ptr<Base<int>>> v;
};

int main()
{
    Factory<Values<1,2,3>, A<int>, B<int>, C<int>>{}.create().show();
    return 0;
}   
