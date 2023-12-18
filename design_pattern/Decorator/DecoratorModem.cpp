#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class Modem
{
public:
    virtual void dial(const std::string& phoneNumber) = 0;
    virtual std::string& getPhoneNumber() = 0;
    virtual void setDialVolume(int volume) = 0;
    virtual int getDialVolume() = 0;
};

class HayesModem: public Modem
{
public:
    void dial(const std::string& phoneNumber) override
    {
        phoneNumber_ = phoneNumber;
    }
    std::string& getPhoneNumber() override
    {
        return phoneNumber_;
    }
    void setDialVolume(int volume) override
    {
        dialVolume = volume;
    }
    int getDialVolume() override
    {
        return dialVolume;
    }
private:
    std::string phoneNumber_{};
    int dialVolume{0};
};

class LoudDialModem: public Modem
{
public:
    LoudDialModem(Modem& modem):modem_(modem){}
    void dial(const std::string& phoneNumber) override
    {
        modem_.setDialVolume(10);
        modem_.dial(phoneNumber);
    }
    std::string& getPhoneNumber() override
    {
        return modem_.getPhoneNumber();
    }
    void setDialVolume(int volume) override
    {
        modem_.setDialVolume(volume);
    }
    int getDialVolume() override
    {
        return modem_.getDialVolume();
    }
private:
    Modem& modem_;
};

int main()
{
    HayesModem hayesModem;
    Modem& modem = hayesModem;
    modem.dial("+1234#");
    cout << "user1:" << modem.getPhoneNumber() << "; phone volume:" << modem.getDialVolume() << endl;

    std::unique_ptr<Modem> loudDialModem = std::make_unique<LoudDialModem>(modem);
    loudDialModem->dial("+1235#");
    cout << "user2:" << loudDialModem->getPhoneNumber() << "; phone volume" << loudDialModem->getDialVolume() << endl;

    return 0;
}