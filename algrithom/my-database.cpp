#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cstring>
#include <cmath>
#include <cstdarg>
#include <cstdio>

#include <cstdlib>
using namespace std;

class DataEngine
{
public:
    DataEngine(){}

    bool create(const char* table, int num, ...)
    {
        in.open(table, ios::in);
        if (in)
        {
            in.close();
            return true;
        }

        va_list args;
        va_start(args, num);
        of.open(table, std::ios::out);
        for (int i = 0; i < num; i++)
        {
            const char* str = va_arg(args, const char*);
            of << str;
            if (i+1 != num)
            {
                of << ',';
            }
            else
            {
                of << endl;
            }
        }
        of.close();
        va_end(args);
        return true;
    }

    bool insert(const char* table, int num, ...)
    {
        va_list args;
        va_start(args, num);
        of.open(table, ios::app);
        for (int i= 0; i < num; i++)
        {
           const char* val = va_arg(args, const char*);
           of << val;
           if (i+1 == num)
           {
                of << endl;
           }
           else
           {
                of << ',';
           }
        }
        of.close();
        va_end(args);

        return true;
    }
    
private:
    ofstream of;
    ifstream in;
};

template <typename T>
string toString(T val)
{
    stringstream sstream;
    sstream << val;
    return sstream.str();
}

int main()
{
    DataEngine de;
    srand(time(NULL));
    int pdcchLoad = rand()%100;
    de.create("tommy.csv", 5, "time", "psgId", "avgLoad_Gbr", "avgLoad_NonGbr", "avgLoad_Pdcch");
    de.insert("tommy.csv", 5, "2020/5/25", "1", "100", "90", toString(pdcchLoad).c_str());
    return 0;
}   

