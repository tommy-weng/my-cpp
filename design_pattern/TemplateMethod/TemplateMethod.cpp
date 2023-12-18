#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class EmployeeActivity
{
public:
    void getActivity()
    {
        beOnDuty();
        work();
        beOffDuty();
        if (hook())
        {
            printWorkingOverTimeInfo();
        }
    }
protected:
    virtual void beOnDuty()
    {
        cout << "I am not so happy to be on duty" << endl;
    }

    virtual void beOffDuty()
    {
        cout << "I am so happy to be off duty"  << endl;
    }

private:
    void printWorkingOverTimeInfo()
    {
        cout << "I am not happy to work overtime" << endl;
    }
    virtual void work() = 0;
    virtual bool hook() = 0;
};

class ManagerActivity : public EmployeeActivity
{
public:
    virtual void beOnDuty() override
    {
        cout <<"I am manager, ";
        EmployeeActivity::beOnDuty();

    }
    virtual void work() override
    {
        cout << "I am manager on working" << endl;
    }
    virtual bool hook() override
    {
        return false;
    }
};

class EngineerActivity : public EmployeeActivity
{
private:
    virtual void beOnDuty() override
    {
        cout << "I am engineer, ";
        EmployeeActivity::beOnDuty();
    }
    virtual void work() override
    {
        cout << "I am engineer at working" << endl;
    }
    virtual bool hook() override
    {
        return true;
    }
};

int main()
{
    std::shared_ptr<EmployeeActivity> activity = std::make_shared<EngineerActivity>();
    activity->getActivity();

    activity = std::make_shared<ManagerActivity>();
    activity->getActivity();

    return 0;
}