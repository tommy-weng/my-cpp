#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;


string getTime()
{
    ostringstream osstream;
    time_t now = time(NULL);
    tm*  ltm = localtime(&now);
    osstream << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;

    return osstream.str();
}

void readCsv(const char* file)
{
    ifstream in;
    in.open(file, ios::in);

    string s;
    getline(in, s);
    cout << s << endl;

    in.close();
}

void genHead(const char* file)
{
    ifstream in;
    in.open(file, ios::in);
    if (!in)
    {
        ofstream of;
        of.open(file, ios::out);
        of << "time, gbr, nonGbr, pdcch" << endl;
        of.close();
    }
}

void saveLoad(const char* file, float gbr, float nonGbr, float pdcch)
{
    ofstream of;
    of.open(file, ios::app);
   
    of << getTime() << "," << gbr <<"," << nonGbr << "," << pdcch << endl;

    of.close();
}

int main(int argc, char* argv[])
{
    genHead(argv[1]);
    srand(time(NULL));
    saveLoad(argv[1], rand()/double(RAND_MAX), rand()/double(RAND_MAX), rand()/double(RAND_MAX));
    return 0;
}   

