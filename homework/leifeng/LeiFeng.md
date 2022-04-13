``` cpp
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class LeiFeng
{
public:
    virtual void sweep() = 0;
};

class CollegeStudent : public LeiFeng
{
public:
    void sweep()
    {
        cout << "CollegeStudent sweeping" << endl;
    }
};

class Volunteer : public LeiFeng
{
public:
    void sweep()
    {
        cout << "Volunteer sweeping" << endl;
    }
};

class FactoryLeiFengBase
{
public:
    virtual std::shared_ptr<LeiFeng> create() = 0;
};

template <typename T>
class FactoryLeiFeng : public FactoryLeiFengBase
{
public:
    std::shared_ptr<LeiFeng> create()
    {
        return std::make_shared<T>();
    }
};

int main()
{
    std::shared_ptr<FactoryLeiFengBase> factoryLeiFeng{nullptr};
    std::shared_ptr<LeiFeng> leiFeng{nullptr};

    factoryLeiFeng = std::make_shared<FactoryLeiFeng<CollegeStudent>>();
    leiFeng = factoryLeiFeng->create();
    leiFeng->sweep();

    factoryLeiFeng = std::make_shared<FactoryLeiFeng<Volunteer>>();
    leiFeng = factoryLeiFeng->create();
    leiFeng->sweep();

    return 0;
}