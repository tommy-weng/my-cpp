#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;

class Hayes;
class Zoom;

// ModemVisitor interface
class ModemVisitor
{
public:
    virtual void visit(Hayes& modem) = 0;
    virtual void visit(Zoom& modem) = 0;
};

// Modem interface
class Modem
{
public:
    virtual void accept(ModemVisitor& visitor) = 0;
};

class Hayes: public Modem
{
public:
    void accept(ModemVisitor& visitor)
    {
        visitor.visit(*this);
    }
};

class Zoom: public Modem
{
public:
    void accept(ModemVisitor& visitor)
    {
        visitor.visit(*this);
    }
};

class ModemVisitorForLinux : public ModemVisitor
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

    ModemVisitorForLinux modemVisitorForLinux{};
    testObject.dispModems(modemVisitorForLinux);
    return 0;
}
