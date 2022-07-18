#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;

// ModemVisitor interface
class ModemVisitor
{
public:
    virtual ~ModemVisitor(){};
};

// Modem interface
class Modem
{
public:
    virtual void accept(ModemVisitor& visitor) = 0;
};

// In Hayes.cpp
class Hayes;
class HayesModemVisitor
{
public:
    virtual void visit(Hayes& modem) = 0;
};

class ModemVisitor;
class Hayes: public Modem
{
public:
    void accept(ModemVisitor& visitor)
    {
        auto& hayesVisitor = dynamic_cast<HayesModemVisitor&>(visitor);
        hayesVisitor.visit(*this);
    }
};

// In Zoom.cpp
class Zoom;
class ZoomModemVisitor
{
public:
    virtual void visit(Zoom& modem)=0;
};

class ModemVisitor;
class Zoom: public Modem
{
public:
    void accept(ModemVisitor& visitor)
    {
        auto& zoomVisitor = dynamic_cast<ZoomModemVisitor&>(visitor);
        zoomVisitor.visit(*this);
    }
};

class UnixModemConfigure : public HayesModemVisitor, public ZoomModemVisitor, public ModemVisitor
{
public:
    void visit(Hayes& modem) override
    {
        cout << "Visit Hayes" << endl;
    }
    void visit(Zoom& modem) override
    {
        cout << "Visit Zoom" << endl;
    }
};

class ModemObjectList
{
public:
    void add(std::unique_ptr<Modem>&& modem)
    {
        modemList.emplace_back(std::move(modem));
    }
    void dispModems(ModemVisitor& visitor)
    {
        for (auto& modem: modemList)
        {
            modem->accept(visitor);
        }
    }
private:
    std::vector<std::unique_ptr<Modem>> modemList{};
};

int main()
{
    ModemObjectList testObject{};

    testObject.add(std::make_unique<Hayes>());
    testObject.add(std::make_unique<Zoom>());

    UnixModemConfigure unixModemConfigure{};
    testObject.dispModems(unixModemConfigure);

    return 0;
}
