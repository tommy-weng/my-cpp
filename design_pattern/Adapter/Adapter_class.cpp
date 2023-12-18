#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class IPlugTarget
{
public:
    virtual void doPlugin() = 0;
};

class TwoPhasePlug : public IPlugTarget
{
public:
    void doPlugin() override
    {
        cout << "Two phase plug" << endl;
    }
};

class ThreePhasePlug
{
public:
    void doThreePhasePlugin()
    {
        cout << "Three phase plug inertion" << endl; 
    }
};

class PlugAdapter: public IPlugTarget, private ThreePhasePlug
{
public:
    void doPlugin() override
    {
        doThreePhasePlugin();
    }
};

int main()
{
    std::unique_ptr<IPlugTarget> twoPhasePlug = std::make_unique<TwoPhasePlug>();
    twoPhasePlug->doPlugin();

    std::unique_ptr<IPlugTarget> adapterTarget = std::make_unique<PlugAdapter>();
    adapterTarget->doPlugin(); 

    return 0;
}