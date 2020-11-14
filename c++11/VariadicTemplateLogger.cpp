#include <iostream>
#include <sstream>
#include <string>

#include <bitset>
#include <fstream>

using namespace std;

const char* fileName = "ccc.log";

enum class LogLevel
{
    DBG,
    INF,
    WRN,
    ERR,
    VIP
};

ofstream of(fileName, ios::app);

LogLevel logLevel = LogLevel::DBG;

class Logger
{
public:
    Logger(ostream& os):out(os)
    {
        
    }
    ~Logger()
    {
        
    }

    template <typename... TYPES>
    void dbg(TYPES&... args)
    {
        if (logLevel <= LogLevel::DBG)
        {
            out << "DBG,"; 
            print(args...);
        }
    }
    template <typename... TYPES>
    void err(TYPES&... args)
    {
        if (logLevel <= LogLevel::ERR)
        {
            out << "ERR,";
            print(args...);
        }
    }
    template <typename... TYPES>
    void vip(TYPES&... args)
    {
        if (logLevel <= LogLevel::VIP)
        {
            out << "VIP,"; 
            print(args...);
        }
            
    }
private:
    ostream& out;
    bool flag = false;
    bool first = true;
    void printX(){out << endl;}
    template <typename T, typename... TYPES>
    void printX(T& arg, TYPES&... args)
    {
        if (not flag)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                out << ",";
            }
        }

        out << arg;
        if (not flag)
        {
            out << "=";
            flag = true;
        }
        else
        {
            flag = false;
        }

        printX(args...);
    }

    template <typename... TYPES>
    void print(TYPES&... args)
    {
        printX(args...);
    }
};

int main()
{
    bitset<16> b(377);
    string s{"hellow"};
    int a = 1;
    double d = 2.1;

    Logger lg(of);
    lg.dbg("hello::fafdf:a",a,"b",b,"s",s,"dfdafdf",d,"fdsaf",d);

    return 0;
}   

