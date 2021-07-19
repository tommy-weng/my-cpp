#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class Base
{
public:
    virtual void print() = 0;
};

template <typename T>
class A: public Base
{
public:
    A(T n):value(n){}
    void print() override
    {
        cout << "A::value=" << value <<endl;
    }
private:
    T value;
};

class Factory
{
public:
    template <class... Vs>
    Factory(Vs&&... vs)
    {
        (v.emplace_back(std::move(std::make_unique<A<Vs>>(vs))), ...);
    }
    void show()
    {
        for_each(v.begin(), v.end(), [](auto& c){
            c->print();
        });
    }
private:
    std::vector<std::unique_ptr<Base>> v;
};

int main()
{
    Factory{1, 1.2, "tommy", 'g', ""}.show();
    return 0;
}   
