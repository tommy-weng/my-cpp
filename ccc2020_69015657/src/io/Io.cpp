#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "../utils/Utils.hpp"
#include "Io.hpp"

namespace io
{

const char* inputFile = "../testcases/case-1-input.txt";

Io::Io(Cities& cities, Weeks& weeks, Pool& pool)
:cities_(cities),
weeks_(weeks),
pool_(pool)
{
    init();
}

Io::~Io()
{

}

void Io::init()
{
    if (not cities_.empty())
    {
        cities_.clear();
    }
    if (not weeks_.empty())
    {
        weeks_.clear();
    }
    pool_.poolR() = 0;
    pool_.poolMinRate() = 0;
}

bool Io::input(const char* file)
{
    init();
    if (nullptr == file)
    {
        file = inputFile;
    }

    ifstream fin(file);
    if (not fin.is_open())
    {
        cout << "open file failed" << endl;
        return false;
    }


    string poolConfig;
    if (getline(fin, poolConfig))
    {
        vector<string> str = splitWithStl(poolConfig, ",");
        pool_.poolR() = atoi(str[0].c_str());
        pool_.poolMinRate() = atoi(str[1].c_str());
    }

    array<comm::City, MAX_CITIES> arr;
    u32 i{0};
    for (string cityConfig; getline(fin, cityConfig);)
    {
        if (i < MAX_CITIES)
        {
            vector<string> str{splitWithStl(cityConfig, ",")};
            arr[i].config().maxR_      = atoi(str[0].c_str());
            arr[i].config().smLoad_    = atoi(str[1].c_str());
            arr[i].config().disLoad_   = atoi(str[2].c_str());
            arr[i].config().otherLoad_ = atoi(str[3].c_str());
            i++;
        }
        else
        {
            i = 0;
        }

        if (MAX_CITIES == i)
        {
            cities_.push_back(arr);
            comm::Week week;
            weeks_.push_back(week);
        }
    }

    // while(not fin.eof())
    // {
    //     string cityConfig;
    //     getline(fin, cityConfig);
    //     if (not cityConfig.empty())
    //     {
    //         vector<string> str{splitWithStl(cityConfig, ",")};
    //         arr[i].config().maxR_      = atoi(str[0].c_str());
    //         arr[i].config().smLoad_    = atoi(str[1].c_str());
    //         arr[i].config().disLoad_   = atoi(str[2].c_str());
    //         arr[i].config().otherLoad_ = atoi(str[3].c_str());
    //         i++;
    //     }
    //     else
    //     {
    //         cities_.push_back(arr);
    //         comm::Week week;
    //         weeks_.push_back(week);
    //         i = 0;
    //     }
    // }

    return true;
}

void Io::output()
{
    for (auto t: cities_)
    {
        ostringstream oss;
        for_each(t.begin(),t.end(),[&](auto i){ oss << i.sumData().sumR_ << ","; });
        string aWeek{oss.str()};
        aWeek.erase(aWeek.size()-1);
        cout << aWeek << endl;
    }
}

}